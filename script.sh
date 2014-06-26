#!/bin/bash

m1="dmelo@wolverine"
m2="dmelo@magneto"
m3="dmelo@t850"
m4="dmelo@xavier"
m5="dmelo@storm"
#m6="dmelo@fabio"
m7="xyxper@penelope"
m8="xyxper@frangolino"

while [ 1 = 1 ]
do
a1="$m1	`ssh $m1 ps aux | grep -i simulator_main | grep -v grep | wc -l` uptime: `ssh $m1 uptime`"
a2="$m2	`ssh $m2 ps aux | grep -i simulator_main | grep -v grep | wc -l` uptime: `ssh $m2 uptime`"
a3="$m3	`ssh $m3 ps aux | grep -i simulator_main | grep -v grep | wc -l` uptime: `ssh $m3 uptime`"
a4="$m4	`ssh $m4 ps aux | grep -i simulator_main | grep -v grep | wc -l` uptime: `ssh $m4 uptime`"
a5="$m5	`ssh $m5 ps aux | grep -i simulator_main | grep -v grep | wc -l` uptime: `ssh $m5 uptime`"
#a6="$m6	`ssh $m6 ps aux | grep -i simulator_main | grep -v grep | wc -l` uptime: `ssh $m6 uptime`"
a7="$m7	`ssh $m7 ps aux | grep -i simulator_main | grep -v grep | wc -l` uptime: `ssh $m7 uptime`"
a8="$m8	`ssh $m8 ps aux | grep -i simulator_main | grep -v grep | wc -l` uptime: `ssh $m8 uptime`"

clear
echo $a1
echo $a2
echo $a3
echo $a4
echo $a5
#echo $a6
echo $a7
echo $a8
echo
lan=`cat history | grep -i "\-\-"| wc -l`
con=`cat history | grep -i "++"| wc -l`
echo "$lan lançados"
echo "$con recebidos"
res=`expr $lan - $con`
echo "$res simuladores executando ou perdidos"
echo
date
done
