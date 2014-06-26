#!/bin/bash

m1="dmelo@wolverine"
m2="dmelo@magneto"
m3="dmelo@t850"
m4="dmelo@xavier"
m5="dmelo@storm"
m6="dmelo@fabio"
m7="dmelo@lindinha"
m8="xyxper@frangolino"

while [ 1 = 1 ]
do
c1=`ssh $m1 ps aux | grep -i simulator_main | grep -v grep | wc -l`
c2=`ssh $m2 ps aux | grep -i simulator_main | grep -v grep | wc -l`
c3=`ssh $m3 ps aux | grep -i simulator_main | grep -v grep | wc -l`
c4=`ssh $m4 ps aux | grep -i simulator_main | grep -v grep | wc -l`
c5=`ssh $m5 ps aux | grep -i simulator_main | grep -v grep | wc -l`
c6=`ssh $m6 ps aux | grep -i simulator_main | grep -v grep | wc -l`
c7=`ssh $m7 ps aux | grep -i simulator_main | grep -v grep | wc -l`
c8=`ssh $m8 ps aux | grep -i simulator_main | grep -v grep | wc -l`
a1="$m1	$c1 uptime: `ssh $m1 uptime`"
a2="$m2	$c2 uptime: `ssh $m2 uptime`"
a3="$m3	$c3 uptime: `ssh $m3 uptime`"
a4="$m4	$c4 uptime: `ssh $m4 uptime`"
a5="$m5	$c5 uptime: `ssh $m5 uptime`"
a6="$m6	$c6 uptime: `ssh $m6 uptime`"
a7="$m7	$c7 uptime: `ssh $m7 uptime`"
a8="$m8	$c8 uptime: `ssh $m8 uptime`"

clear
echo $a1
echo $a2
echo $a3
echo $a4
echo $a5
echo $a6
echo $a7
echo $a8
echo
lan=`cat history | grep -i "\-\-"| wc -l`
con=`cat history | grep -i "++"| wc -l`
echo "$lan lançados"
echo "$con recebidos"
tot=`expr $c1 + $c2 + $c3 + $c4 + $c5 + $c6 + $c7 + $c8`
res=`expr $lan - $con - $tot`
echo "$res simuladores perdidos"
echo "$tot simuladores executando"
echo
echo "Total de simulações executadas por máquina"
echo "$m1 `grep -i ++ history | grep -i $m1 | wc -l`"
echo "$m2 `grep -i ++ history | grep -i $m2 | wc -l`"
echo "$m3 `grep -i ++ history | grep -i $m3 | wc -l`"
echo "$m4 `grep -i ++ history | grep -i $m4 | wc -l`"
echo "$m5 `grep -i ++ history | grep -i $m5 | wc -l`"
echo "$m6 `grep -i ++ history | grep -i $m6 | wc -l`"
echo "$m7 `grep -i ++ history | grep -i $m7 | wc -l`"
echo "$m8 `grep -i ++ history | grep -i $m8 | wc -l`"
echo
date
done
