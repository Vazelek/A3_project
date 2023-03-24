# main: autotests.c consigne.c main.c regulation.c simulateur.c test_simulateur.c visualisationC.c visualisationT.c releve.c commande.c test_usb.c ftd2xx.lib
# 	gcc autotests.c consigne.c main.c regulation.c simulateur.c test_simulateur.c visualisationC.c visualisationT.c releve.c commande.c test_usb.c ftd2xx.lib -o test -Wall

autotests: autotests.c consigne.c regulation.c test_autotest.c visualisationC.c visualisationT.c 
	gcc -c autotests.c consigne.c regulation.c test_autotest.c visualisationC.c visualisationT.c 
	gcc autotests.o consigne.o regulation.o test_autotest.o visualisationC.o visualisationT.o -o autotests -Wall
	rm -rf *.o

simu: consigne.c regulation.c test_simulateur.c visualisationC.c visualisationT.c simulateur.c
	gcc -c consigne.c regulation.c test_simulateur.c visualisationC.c visualisationT.c simulateur.c
	gcc consigne.o regulation.o test_simulateur.o visualisationC.o visualisationT.o simulateur.o ftd2xx.dll -o simu -Wall
	rm -rf *.o

clean:
	rm -rf *.o *.exe
