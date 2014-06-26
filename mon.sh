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
echo
date
done
