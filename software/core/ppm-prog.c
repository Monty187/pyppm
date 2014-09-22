
/* ppm-prog.c: source file for passing around pulse programs.
 * Copyright (C) 2014  Bradley Worley  <geekysuavo@gmail.com>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to:
 *
 *   Free Software Foundation, Inc.
 *   51 Franklin Street, Fifth Floor
 *   Boston, MA  02110-1301, USA.
 */

/* include the PPM header. */
#include "ppm.h"

/* define a structure to hold command iteration information.
 */
typedef struct ppm_cmd_t {
  /* the command byte. */
  uint8_t id;

  /* the command argument byte count. */
  unsigned int n_argbytes;
} ppm_cmd;

/* declare an array of command information structures. */
static const ppm_cmd cmds[] = {
  { PPM_PULPROG_DEADTIME, 2 },
  { PPM_PULPROG_DELAY,    2 },
  { PPM_PULPROG_POLARIZE, 1 },
  { PPM_PULPROG_RELAY,    1 },
  { PPM_PULPROG_ACQUIRE,  6 },
  { PPM_PULPROG_TXRISE,   4 },
  { PPM_PULPROG_TXFALL,   4 },
  { PPM_PULPROG_TXPULSE,  9 },
  { PPM_PULPROG_TUNE,     2 },
  { PPM_PULPROG_SHIM_X,   2 },
  { PPM_PULPROG_SHIM_Y,   2 },
  { PPM_PULPROG_SHIM_Z,   2 },
  { PPM_PULPROG_END,      0 }
};

/* ppm_prog_alloc: allocates a pulse program array.
 */
int ppm_prog_alloc (ppm_prog *pp, unsigned int n) {
  /* set the value count. */
  pp->n = n;

  /* allocate memory for the program values. */
  pp->bytes = (uint8_t *) calloc (pp->n, sizeof (uint8_t));

  /* ensure the data was allocated. */
  if (!pp->bytes) {
    /* return failure. */
    return 0;
  }

  /* return success. */
  return 1;
}

/* ppm_prog_empty: frees an allocated pulse program array.
 */
void ppm_prog_empty (ppm_prog *pp) {
  /* free the array. */
  if (pp->n) {
    /* only if it's allocated. */
    free (pp->bytes);
    pp->bytes = NULL;
  }

  /* set the size of the pulse program. */
  pp->n = 0;
}

/* ppm_prog_iterate: iterates over the commands of a pulse program. */
void ppm_prog_iterate (ppm_prog *pp, ppm_prog_iterator fn, void *pdata) {
  /* declare required variables. */
  unsigned int i, j;

  /* loop through the pulse program bytes. */
  for (i = 0; i < pp->n; i++) {
    /* run the callback function. */
    fn (pp->bytes[i], &(pp->bytes[i + 1]), pdata);

    /* loop through the commands array to determine how far to skip. */
    for (j = 0; cmds[j].id != PPM_PULPROG_END; j++) {
      /* check if the indexed command matches our current command. */
      if (cmds[j].id == pp->bytes[i]) {
        /* skip to the next command and break the search. */
        i += cmds[j].n_argbytes;
        break;
      }
    }
  }
}

/* ppm_prog_samples_iter: iterator for ppm_prog_samples(). */
void ppm_prog_samples_iter (uint8_t cmd, uint8_t *args, void *pdata) {
  /* dereference the current sample count. */
  unsigned int n = *((unsigned int *) pdata);

  /* check if the current command is an acquisition. */
  if (cmd == PPM_PULPROG_ACQUIRE) {
    /* yes. add the sample count into the total. */
    n += WORD32 (args[0], args[1], args[2], args[3]);
    *((unsigned int *) pdata) = n;
  }
}

/* ppm_prog_timings_iter: iterator for ppm_prog_timings().
 */
void ppm_prog_timings_iter (uint8_t cmd, uint8_t *args, void *pdata) {
  /* declare required variables. */
  unsigned int n, ovf, i, i0;

  /* dereference the acquisition data structure. */
  ppm_data *acq = (ppm_data *) pdata;

  /* get the current data point index. */
  i0 = (unsigned int) acq->x[0];

  /* check if the current command is an acquisition. */
  if (cmd == PPM_PULPROG_ACQUIRE) {
    /* yes. get the sample count and overflow for this acquisition. */
    n = WORD32 (args[0], args[1], args[2], args[3]);
    ovf = WORD (args[4], args[5]);

    /* loop through the appropriate indices. */
    for (i = 0; i < n; i++)
      acq->x[i0 + i] = (double) i * (double) ovf * 62.5e-9;

    /* move the index pointer forward. */
    acq->x[0] = (double) (i0 + n);
  }
}

/* ppm_prog_samples: predict the number of acquired data samples that should
 * come out of a given pulse program.
 */
unsigned int ppm_prog_samples (ppm_prog *pp) {
  /* declare required variables. */
  unsigned int n = 0;

  /* iterate over the pulse program array to compute the value. */
  ppm_prog_iterate (pp, ppm_prog_samples_iter, &n);

  /* return the computed value. */
  return n;
}

/* ppm_prog_timings: fills in the time values of an allocated acquisition data
 * structure based on the pulse sequence elements inside a pulse program.
 */
void ppm_prog_timings (ppm_prog *pp, ppm_data *acq) {
  /* declare required variables. */
  unsigned int i;

  /* initialize the acquisition times. */
  for (i = 0; i < acq->n; i++)
    acq->x[i] = 0.0;

  /* simply run the iterator function. */
  ppm_prog_iterate (pp, ppm_prog_timings_iter, acq);

  /* fix the first point. */
  acq->x[0] = 0.0;
}

/* ppm_prog_read: reads the contents of a pulse program structure from a file.
 */
void ppm_prog_read (FILE *fh, ppm_prog *pp) {
  /* declare required variables. */
  char buf[80], *pbuf;
  unsigned int i;
  uint8_t byte;

  /* initialize the byte index. */
  i = 0;

  /* loop while we have data to read from the file. */
  while (!feof (fh)) {
    /* try to read a line from the file. */
    if (fgets (buf, 80, fh)) {
      /* strip the trailing newline. */
      if (strlen (buf) > 1)
        buf[strlen (buf) - 1] = '\0';

      /* only proceed if the string is at least 10 characters long. */
      if (strlen (buf) < 10)
        continue;

      /* search the line for tokens. throw away the first. */
      pbuf = strtok (buf, " ");
      pbuf = strtok (NULL, " ");

      /* loop while we can obtain new tokens. */
      while (pbuf) {
        /* only convert if the string is at least two characters long. */
        if (strlen (pbuf) < 2)
          continue;

        /* check if the current index is greater than the array size. */
        if (i >= pp->n) {
          /* resize. */
          pp->n = i + 1;

          /* resize the arrays. */
          if (pp->n == 1)
            pp->bytes = (uint8_t *) malloc (sizeof (uint8_t));
          else
            pp->bytes = (uint8_t *)
              realloc (pp->bytes, sizeof (uint8_t) * pp->n);
        }

        /* attempt to scan the token. */
        if (sscanf (pbuf, "%02x", (unsigned int *) &byte) == 1) {
          /* store the byte and increment. */
          pp->bytes[i] = byte;
          i++;
        }

        /* get the next token. */
        pbuf = strtok (NULL, " ");
      }
    }
  }
}

/* ppm_prog_write: writes the contents of the pulse program structure.
 */
void ppm_prog_write (FILE *fh, ppm_prog *pp) {
  /* declare required variables. */
  unsigned int i;

  /* loop through the pulse program bytes. */
  for (i = 0; i < pp->n; i++) {
    /* check if a heading needs to be written. */
    if (i % 16 == 0) {
      /* print the current location, with a newline if we've already
       * printed a first batch of values.
       */
      fprintf (fh, "%s%08u", i > 0 ? "\n" : "", i);
    }

    /* print the current byte. */
    fprintf (fh, " %02x", pp->bytes[i]);
  }

  /* print one final newline. */
  fprintf (fh, "\n");
}
