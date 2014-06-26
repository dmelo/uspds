#	USPDroidsSimulator
#	(C) 2007  Diogo Oliveira de Melo

#	This program is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 2 of the License, or
#	(at your option) any later version.

#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.

#	You should have received a copy of the GNU General Public License
#	along with this program; if not, write to the Free Software
#	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#	executar.sh

#!/bin/bash

echo "iniciando o kernel..."
echo "new===" >> log.txt
a1=4321
a2=4322
a3=4323
a4=4324
a5=4325
a6=filename
a7=gamefile
a8=1.5
a9=1.6
a10=1.7
nice --adjustment=15 ./bin/simulator_main -set_ports $a1 $a2 $a3 $a4 $a5 $a6 $a7> /dev/null &
sleep 1
echo "iniciando a interface gráfica..."
xterm -e ./bin/eyes localhost 4321 &
sleep 1
echo "iniciando a estratégia 1..."
nice --adjustment=15 ./bin/strategy_pf2 localhost 1 -set_ports $a3 $a2 60 20 > /dev/null &
sleep 1
echo "iniciando a estratégia 2..."
nice --adjustment=15 ./bin/strategy_pf2 localhost 2 -set_ports $a5 $a4 20 5 > /dev/null
sleep 1
