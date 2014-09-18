v 20110115 2
C 40000 40000 0 0 0 title-B.sym
T 50000 40700 14 18 1 0 0 0 1
SCB | Bootstrap +5V Regulator
T 50000 40400 14 10 1 0 0 0 1
04-bootstrap.sch
T 50100 40100 14 14 1 0 0 0 1
4
T 51600 40100 14 14 1 0 0 0 1
10
T 54000 40100 14 10 1 0 0 0 1
Bradley Worley
T 54000 40400 14 10 1 0 0 0 1
1.1
C 41300 47300 1 270 0 battery-3.sym
{
T 42000 47000 5 10 0 0 270 0 1
device=BATTERY
T 41800 46600 5 10 1 1 0 0 1
refdes=B01
T 42250 47000 5 10 0 0 270 0 1
symversion=0.1
T 41800 46400 5 10 1 1 0 0 1
value=7V ~ 10V
T 41300 47300 5 10 0 0 0 0 1
footprint=Power_Jack_PJ037
}
N 41500 47700 41500 47300 4
N 41500 46000 41500 46200 4
C 41400 45700 1 0 0 gnd-1.sym
C 52500 43500 1 0 0 hcpl-0201-1.sym
{
T 53700 45300 5 10 1 1 0 0 1
device=HCPL0201
T 52800 47200 5 10 0 0 0 0 1
footprint=SO8
T 53700 45500 5 10 1 1 0 0 1
refdes=U04
}
C 53400 43000 1 0 0 gnd-1.sym
C 49800 44600 1 0 0 input-2.sym
{
T 49800 44800 5 10 0 0 0 0 1
net=LDO_EN:1
T 50400 45300 5 10 0 0 0 0 1
device=none
T 50300 44700 5 10 1 1 0 7 1
value=LDO_EN
}
N 52300 44700 52500 44700 4
N 52500 44300 52300 44300 4
N 52300 44300 52300 44100 4
N 53500 43500 53500 43300 4
C 45700 45000 1 0 0 lt1761es5-1.sym
{
T 46100 48500 5 10 0 0 0 0 1
device=LT1761
T 48000 48100 5 10 1 1 180 8 1
refdes=U03
T 46100 48700 5 10 0 0 0 0 1
footprint=SOT25
}
C 47000 44500 1 0 0 gnd-1.sym
N 47100 45000 47100 44800 4
N 54500 44500 54700 44500 4
C 52200 43800 1 0 0 gnd-earth-1.sym
C 49200 46400 1 90 0 capacitor-1.sym
{
T 48500 46600 5 10 0 0 90 0 1
device=CAPACITOR
T 49300 46900 5 10 1 1 0 0 1
refdes=C12
T 48300 46600 5 10 0 0 90 0 1
symversion=0.1
T 49300 46700 5 10 1 1 0 0 1
value=10n
T 49200 46400 5 10 0 0 0 0 1
footprint=SMD_SIMPLE 80 50
}
N 48700 47500 53500 47500 4
N 49000 47500 49000 47300 4
N 48700 46000 49000 46000 4
N 49000 46000 49000 46400 4
N 53500 45500 53500 47700 4
C 41300 47700 1 0 0 generic-power.sym
{
T 41500 47950 5 10 0 1 0 3 1
net=B+:1
T 41500 48000 3 9 1 1 0 4 1
value=B+
}
N 45700 46000 45500 46000 4
N 45500 46000 45500 47500 4
N 41500 47500 45700 47500 4
C 50300 47300 1 270 0 capacitor-2.sym
{
T 51000 47100 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 50800 46900 5 10 1 1 0 0 1
refdes=C13
T 51200 47100 5 10 0 0 270 0 1
symversion=0.1
T 50800 46700 5 10 1 1 0 0 1
value=10u
T 50300 47300 5 10 0 0 0 0 1
footprint=SMD_POLAR 120 60
}
C 52200 46400 1 90 0 capacitor-1.sym
{
T 51500 46600 5 10 0 0 90 0 1
device=CAPACITOR
T 52300 46900 5 10 1 1 0 0 1
refdes=C14
T 51300 46600 5 10 0 0 90 0 1
symversion=0.1
T 52300 46700 5 10 1 1 0 0 1
value=100n
T 52200 46400 5 10 0 0 0 0 1
footprint=SMD_SIMPLE 80 50
}
N 50500 47500 50500 47300 4
N 50500 46200 50500 46400 4
N 52000 46200 52000 46400 4
N 52000 47500 52000 47300 4
C 50400 45900 1 0 0 gnd-1.sym
C 51900 45900 1 0 0 gnd-1.sym
C 54700 44400 1 0 0 output-2.sym
{
T 55600 44600 5 10 0 0 0 0 1
net=LDO_EN_ISO:1
T 54900 45100 5 10 0 0 0 0 1
device=none
T 54900 44200 5 10 1 1 0 1 1
value=LDO_EN_ISO
}
C 42800 47300 1 270 0 capacitor-2.sym
{
T 43500 47100 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 43300 46900 5 10 1 1 0 0 1
refdes=C10
T 43700 47100 5 10 0 0 270 0 1
symversion=0.1
T 43300 46700 5 10 1 1 0 0 1
value=10u
T 42800 47300 5 10 0 0 0 0 1
footprint=SMD_POLAR 120 60
}
C 44700 46400 1 90 0 capacitor-1.sym
{
T 44000 46600 5 10 0 0 90 0 1
device=CAPACITOR
T 44800 46900 5 10 1 1 0 0 1
refdes=C11
T 43800 46600 5 10 0 0 90 0 1
symversion=0.1
T 44800 46700 5 10 1 1 0 0 1
value=100n
T 44700 46400 5 10 0 0 0 0 1
footprint=SMD_SIMPLE 80 50
}
N 43000 47500 43000 47300 4
N 43000 46200 43000 46400 4
N 44500 46200 44500 46400 4
N 44500 47500 44500 47300 4
C 42900 45900 1 0 0 gnd-1.sym
C 44400 45900 1 0 0 gnd-1.sym
C 53300 47700 1 0 0 generic-power.sym
{
T 53500 47950 5 10 0 1 0 3 1
net=Vboot:1
T 53500 48000 3 9 1 1 0 4 1
value=Vboot
}
C 52300 44800 1 180 0 resistor-1.sym
{
T 52000 44400 5 10 0 0 180 0 1
device=RESISTOR
T 51600 44900 5 10 1 1 0 0 1
refdes=R07
T 51600 44400 5 10 1 1 0 0 1
value=715
T 52300 44800 5 10 0 0 90 0 1
footprint=SMD_SIMPLE 80 50
}
N 51200 44700 51400 44700 4