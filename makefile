main: autotests.c consigne.c main.c regulation.c simulateur.c test_simulateur.c visualisationC.c visualisationT.c
	gcc autotests.c consigne.c main.c regulation.c simulateur.c test_simulateur.c visualisationC.c visualisationT.c -o test -Wall
