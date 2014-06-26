#!/bin/bash

tot=`wc -l config/hosts | cut -d' ' -f1`
echo $tot

for i in $tot
do
	echo $i
done
