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
sleep 1
echo "iniciando o kernel..."
time ./bin/simulator localhost 4321 &
sleep 1
echo "iniciando a estratégia 1..."
./bin/strategy_pf2 localhost 1 >& /dev/null &
sleep 1
echo "iniciando a estratégia 2..."
./bin/strategy localhost 2 >& /dev/null &
