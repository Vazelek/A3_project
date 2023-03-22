main: autotests.c consigne.c main.c regulation.c simulateur.c test_simulateur.c visualisationC.c visualisationT.c ftd2xx.lib
	gcc autotests.c consigne.c main.c regulation.c simulateur.c test_simulateur.c visualisationC.c visualisationT.c ftd2xx.lib -o test -Wall
