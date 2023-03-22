main: autotests.c consigne.c main.c regulation.c simulateur.c test_simulateur.c visualisationC.c visualisationT.c releve.c commande.c test_usb.c ftd2xx.lib
	gcc autotests.c consigne.c main.c regulation.c simulateur.c test_simulateur.c visualisationC.c visualisationT.c releve.c commande.c test_usb.c ftd2xx.lib -o test -Wall -I librairies/ftd2xx
