SRC=./src
SIMULATOR=${SRC}/simulator
EYESJAVA=${SRC}/eyes_java
RECORDER=${SRC}/recorder
STRATEGY=${SRC}/strategy
STRATEGY_PF2=${SRC}/strategy_pf2
STRATEGY_PF1=${SRC}/strategy_pf1
LIB=${SRC}/lib
EYESOPENGL=${SRC}/eyes_opengl
REVEL=${SRC}/revel
STATISTICS=${SRC}/statistics
CONTROL=${SRC}/control
PERFORMANCE_ANALYSIS=${SRC}/performance_analysis
GENETIC_ALGORITHM=${SRC}/genetic_algorithm
BIN=./bin
DIRECTORY=/usr/bin
PRO=${BIN}/simulator_main ${BIN}/eyes  ${BIN}/Eyes.class ${BIN}/recorder ${BIN}/strategy_pf2 ${BIN}/strategy_pf1 ${BIN}/statistics ${BIN}/pid.o ${BIN}/performance_analysis.o ${BIN}/genetic_algorithm 
PROINSTALED=${DIRECTORY}/simulator_main ${DIRECTORY}/Eyes.class ${DIRECTORY}/eyes  ${DIRECTORY}/Eyes.class ${DIRECTORY}/recorder ${DIRECTORY}/strategy_pf2 ${DIRECTORY}/statistics ${BIN}/pid.o ${BIN}/performance_analysis.o ${BIN}/strategy_pf1 ${BIN}/genetic_algorithm 
DOC=./doc
CC=@CC@
CXX=g++
JC=javac
CFLAGS=-O3 -msse
CPPFLAGS=-O3 -msse

all: ${PRO} ${DOC}/html/index.html

# Performance analysis

${BIN}/performance_analysis.o: ${PERFORMANCE_ANALYSIS}/performance_analysis.h ${PERFORMANCE_ANALYSIS}/performance_analysis.cc
	${CXX} ${CFLAGS} ${PERFORMANCE_ANALYSIS}/performance_analysis.cc -o ${BIN}/performance_analysis.o -fopenmp -lpthread -c


# SIMULADOR
${BIN}/simulator_main: ${BIN}/campo.o ${BIN}/bola.o ${BIN}/robo.o ${BIN}/protocolo.o ${BIN}/history.o ${BIN}/simulator.o ${SIMULATOR}/simulator_main.cc 
	${CXX} ${CFLAGS} ${SIMULATOR}/simulator_main.cc ${BIN}/campo.o ${BIN}/bola.o ${BIN}/robo.o ${BIN}/objeto.o ${BIN}/vetor2d.o ${BIN}/protocolo.o ${BIN}/history.o ${BIN}/simulator.o -o ${BIN}/simulator_main -lpthread

${BIN}/simulator.o: ${BIN}/campo.o ${BIN}/bola.o ${BIN}/robo.o ${BIN}/protocolo.o ${BIN}/history.o ${SIMULATOR}/simulator.cc ${SIMULATOR}/simulator.h
	${CXX} ${CFLAGS} ${SIMULATOR}/simulator.cc ${BIN}/campo.o ${BIN}/bola.o ${BIN}/robo.o ${BIN}/objeto.o ${BIN}/vetor2d.o ${BIN}/protocolo.o ${BIN}/history.o -o ${BIN}/simulator.o -lpthread -c

${BIN}/history.o: ${SIMULATOR}/history.cc ${SIMULATOR}/history.h ${BIN}/objeto.o ${SIMULATOR}/simulator.h
	${CXX} ${CFLAGS} ${SIMULATOR}/history.cc -o ${BIN}/history.o  ${BIN}/objeto.o -c

${BIN}/vetor2d.o: ${LIB}/vetor2d.cc ${LIB}/vetor2d.h
	${CXX} ${CFLAGS} -c ${LIB}/vetor2d.cc -o ${BIN}/vetor2d.o

${BIN}/objeto.o: ${LIB}/objeto.cc ${LIB}/objeto.h ${LIB}/parametros.h ${BIN}/vetor2d.o
	${CXX} ${CFLAGS} -c ${LIB}/objeto.cc -o ${BIN}/objeto.o

${BIN}/campo.o: ${SIMULATOR}/campo.h ${SIMULATOR}/campo.cc ${LIB}/parametros.h ${BIN}/objeto.o ${BIN}/vetor2d.o
	${CXX} ${CFLAGS} -c ${SIMULATOR}/campo.cc -o  ${BIN}/campo.o

${BIN}/robo.o: ${SIMULATOR}/robo.h ${SIMULATOR}/robo.cc ${LIB}/parametros.h ${BIN}/objeto.o ${BIN}/vetor2d.o
	${CXX} ${CFLAGS} -c ${SIMULATOR}/robo.cc -o  ${BIN}/robo.o

${BIN}/bola.o: ${SIMULATOR}/bola.h ${SIMULATOR}/bola.cc ${LIB}/parametros.h ${BIN}/objeto.o ${BIN}/vetor2d.o ${BIN}/robo.o
	${CXX} ${CFLAGS} -c ${SIMULATOR}/bola.cc -o  ${BIN}/bola.o

${BIN}/protocolo.o: ${LIB}/protocolo.h ${LIB}/protocolo.cc
	${CXX} ${CFLAGS} -c ${LIB}/protocolo.cc -o  ${BIN}/protocolo.o
${BIN}/recorder: ${LIB}/parametros.h ${RECORDER}/recorder.cc
	${CXX} ${CFLAGS} ${RECORDER}/recorder.cc -o ${BIN}/recorder


# PID

${BIN}/pid.o: ${CONTROL}/pid.cc ${CONTROL}/pid.h ${LIB}/parametros.h
	${CXX} ${CFLAGS} -c ${CONTROL}/pid.cc -o ${BIN}/pid.o


${BIN}/res_sistema.o: ${LIB}/res_sistema.cc ${LIB}/res_sistema.h
	${CXX} ${CFLAGS} -c ${LIB}/res_sistema.cc -o ${BIN}/res_sistema.o

${BIN}/base.o: ${STRATEGY}/base.cc ${STRATEGY}/base.h ${BIN}/objeto.o ${BIN}/vetor2d.o ${BIN}/res_sistema.o
	${CXX} ${CFLAGS} -c -lpthread ${STRATEGY}/base.cc ${BIN}/objeto.o ${BIN}/vetor2d.o ${BIN}/res_sistema.o -o ${BIN}/base.o

#${BIN}/strategy2: ${STRATEGY}/strategy2.cc ${STRATEGY}/strategy2.h ${BIN}/objeto.o ${BIN}/vetor2d.o ${BIN}/res_sistema.o ${BIN}/base.o
#	${CXX} ${CFLAGS} -lpthread ${STRATEGY}/strategy2.cc ${BIN}/objeto.o ${BIN}/vetor2d.o ${BIN}/res_sistema.o ${BIN}/base.o -o ${BIN}/strategy2

# GUI Java
${BIN}/Eyes.class: ${EYESJAVA}/Eyes.java
	${JC} ${EYESJAVA}/Eyes.java -d ${BIN}

# GUI OpenGL
${BIN}/eyes: ${EYESOPENGL}/eyes.cc ${EYESOPENGL}/eyes.h ${BIN}/objeto.o ${BIN}/protocolo.o ${BIN}/vetor2d.o ${BIN}/campo.o ${BIN}/avilib.o ${BIN}/BaseEncoder.o ${BIN}/revelcore.o ${BIN}/XvidEncoder.o
	${CXX} ${CFLAGS} -lpthread ${EYESOPENGL}/eyes.cc ${BIN}/objeto.o ${BIN}/protocolo.o ${BIN}/vetor2d.o ${BIN}/campo.o ${BIN}/avilib.o ${BIN}/BaseEncoder.o ${BIN}/revelcore.o ${BIN}/XvidEncoder.o -o ${BIN}/eyes -lGL -lglut -lpthread -lxvidcore

${BIN}/avilib.o: ${REVEL}/avilib.c ${REVEL}/avilib.h
	${CC} ${CFLAGS} ${REVEL}/avilib.c -o ${BIN}/avilib.o -c

${BIN}/BaseEncoder.o: ${REVEL}/BaseEncoder.cpp ${REVEL}/BaseEncoder.h
	${CXX} ${CFLAGS} ${REVEL}/BaseEncoder.cpp -o ${BIN}/BaseEncoder.o -c

${BIN}/revelcore.o: ${REVEL}/revelcore.cpp ${REVEL}/revel.h
	${CXX} ${CFLAGS} ${REVEL}/revelcore.cpp -o ${BIN}/revelcore.o -c

${BIN}/XvidEncoder.o: ${REVEL}/XvidEncoder.cpp ${REVEL}/XvidEncoder.h
	${CXX} ${CFLAGS} ${REVEL}/XvidEncoder.cpp -o ${BIN}/XvidEncoder.o -c



# Strategy Potential Fields 1.
${BIN}/strategy_pf1: ${STRATEGY_PF1}/basicMove.cpp ${STRATEGY_PF1}/basicMove.h ${STRATEGY_PF1}/futbot.cpp ${STRATEGY_PF1}/futbot.h ${STRATEGY_PF1}/strategy.cpp ${STRATEGY_PF1}/strategy.h ${STRATEGY_PF1}/ForceField.cpp ${STRATEGY_PF1}/ForceField.h ${BIN}/base.o
	${CXX} ${CFLAGS} ${STRATEGY_PF1}/basicMove.cpp ${STRATEGY_PF1}/futbot.cpp ${STRATEGY_PF1}/strategy.cpp ${STRATEGY_PF1}/ForceField.cpp ${BIN}/base.o ${BIN}/objeto.o ${BIN}/vetor2d.o -o ${BIN}/strategy_pf1



# Strategy Potential Fields 2.
${BIN}/strategy_pf2: ${STRATEGY_PF2}/basicMove.cpp ${STRATEGY_PF2}/basicMove.h ${STRATEGY_PF2}/futbot.cpp ${STRATEGY_PF2}/futbot.h ${STRATEGY_PF2}/strategy.cpp ${STRATEGY_PF2}/strategy.h ${STRATEGY_PF2}/ForceField.cpp ${STRATEGY_PF2}/ForceField.h ${BIN}/base.o
	${CXX} ${CFLAGS} ${STRATEGY_PF2}/basicMove.cpp ${STRATEGY_PF2}/futbot.cpp ${STRATEGY_PF2}/strategy.cpp ${STRATEGY_PF2}/ForceField.cpp ${BIN}/base.o ${BIN}/objeto.o ${BIN}/vetor2d.o -o ${BIN}/strategy_pf2


genetic_algorithm: ${BIN}/genetic_algorithm

${BIN}/genetic_algorithm: ${GENETIC_ALGORITHM}/genetic_algorithm.cc ${BIN}/population.o ${BIN}/Random.o ${BIN}/performance_analysis.o
	g++ ${GENETIC_ALGORITHM}/genetic_algorithm.cc ${BIN}/population.o ${BIN}/individuo_data.o ${BIN}/individuo.o ${BIN}/objective.o ${BIN}/cromossomo.o ${BIN}/Random.o ${BIN}/gene.o ${BIN}/performance_analysis.o  -o ${BIN}/genetic_algorithm -fopenmp

${BIN}/population.o: ${GENETIC_ALGORITHM}/population.cc ${GENETIC_ALGORITHM}/population.h ${BIN}/individuo_data.o ${BIN}/individuo.o
	g++ ${GENETIC_ALGORITHM}/population.cc ${BIN}/individuo.o  -c -o ${BIN}/population.o

${BIN}/individuo_data.o: ${GENETIC_ALGORITHM}/individuo_data.cc ${GENETIC_ALGORITHM}/individuo_data.h ${GENETIC_ALGORITHM}/cromossomo.h ${GENETIC_ALGORITHM}/objective.h
	g++ ${GENETIC_ALGORITHM}/individuo_data.cc -c -o ${BIN}/individuo_data.o
 
${BIN}/individuo.o: ${GENETIC_ALGORITHM}/individuo.cc ${GENETIC_ALGORITHM}/individuo.h ${BIN}/objective.o ${BIN}/cromossomo.o
	g++ ${GENETIC_ALGORITHM}/individuo.cc ${BIN}/objective.o ${BIN}/cromossomo.o -c -o ${BIN}/individuo.o

${BIN}/objective.o: ${GENETIC_ALGORITHM}/objective.cc ${GENETIC_ALGORITHM}/objective.h
	g++ ${GENETIC_ALGORITHM}/objective.cc -c -o ${BIN}/objective.o

${BIN}/cromossomo.o: ${GENETIC_ALGORITHM}/cromossomo.cc ${GENETIC_ALGORITHM}/cromossomo.h ${BIN}/gene.o
	g++ ${GENETIC_ALGORITHM}/cromossomo.cc -c -o ${BIN}/cromossomo.o

${BIN}/gene.o: ${GENETIC_ALGORITHM}/gene.cc ${GENETIC_ALGORITHM}/gene.h
	g++ ${GENETIC_ALGORITHM}/gene.cc -c -o ${BIN}/gene.o

${BIN}/Random.o: ${GENETIC_ALGORITHM}/Random.cc
	g++ ${GENETIC_ALGORITHM}/Random.cc -c -o ${BIN}/Random.o




clean:
	rm -rf ${BIN}/* doc/* Makefile

# Documentação

${DOC}/html/index.html: ${EYESOPENGL}/eyes.h ${LIB}/res_sistema.h ${EYESJAVA}/Eyes.java ${STRATEGY}/strategy.h ${LIB}/protocolo.h ${LIB}/parametros.h ${SIMULATOR}/bola.h ${SIMULATOR}/robo.h ${SIMULATOR}/campo.h ${LIB}/objeto.h ${LIB}/vetor2d.h 
	doxygen doxygen.cfg >& doxygen.log

# Statistics

${BIN}/statistics: ${STATISTICS}/statistics.cc ${BIN}/objeto.o ${BIN}/mstring.o ${BIN}/vetor2d.o ${BIN}/mmath.o
	${CXX} ${CFLAGS} ${STATISTICS}/statistics.cc ${BIN}/objeto.o ${BIN}/mstring.o ${BIN}/vetor2d.o ${BIN}/mmath.o -o ${BIN}/statistics

${BIN}/mmath.o: ${LIB}/mmath.cc ${LIB}/mmath.h
	${CXX} ${CFLAGS} ${LIB}/mmath.cc -c -o ${BIN}/mmath.o

${BIN}/mstring.o: ${LIB}/mstring.cc
	${CXX} ${CFLAGS} ${LIB}/mstring.cc -c -o ${BIN}/mstring.o

install:
	cp executar.sh ${PRO} ${BIN}/Eyes.class ${DIRECTORY}
	chmod -c +x ${DIRECTORY}/executar.sh ${PROINSTALED}
