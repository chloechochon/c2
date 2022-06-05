CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11


all: testVecteur testBalle testPendule testObstacle testChocs testIntegrateur1 testIntegrateur2  testIntegrateurN  exerciceP9a testChocsballeballe testChocs2pendules testChocsballeplan testChocsbriquependules


constantes.o: constantes.h constantes.cc

ex_vecteur.o: ex_vecteur.cc ex_vecteur.h

testVecteur.o: testVecteur.cc ex_vecteur.h
testVecteur: testVecteur.o ex_vecteur.o


ObjetMobile.o: ObjetMobile.cc ObjetMobile.h ex_vecteur.cc ex_vecteur.h constantes.h Dessinable.cc Dessinable.h SupportADessin.h Systeme.h

ChampsForces.o: ChampsForces.cc ChampsForces.h ObjetMobile.h ex_vecteur.h

testBalle.o: testBalle.cc ex_vecteur.h ObjetMobile.h constantes.h ChampsForces.h 
testBalle: testBalle.o ex_vecteur.o ObjetMobile.o constantes.o ChampsForces.o Systeme.o Integrateur.o


obstacle.o: obstacle.cc obstacle.h ex_vecteur.o ObjetMobile.h Dessinable.h SupportADessin.h constantes.h

testObstacle.o: testObstacle.cc constantes.o ObjetMobile.cc ObjetMobile.h ex_vecteur.o obstacle.cc obstacle.h Systeme.cc Systeme.h ChampsForces.cc ChampsForces.h Integrateur.cc Integrateur.h
testObstacle: testObstacle.o constantes.o ObjetMobile.o ex_vecteur.o obstacle.o Systeme.o Integrateur.o ChampsForces.o

testPendule.o: ex_vecteur.o ObjetMobile.o testPendule.cc constantes.o Integrateur.o Systeme.o ChampsForces.o
testPendule: testPendule.o ObjetMobile.o ex_vecteur.o constantes.o Integrateur.o Systeme.o ChampsForces.o


Integrateur.o: Integrateur.h Integrateur.cc ex_vecteur.o ObjetMobile.o constantes.o

testIntegrateur1.o: Integrateur.o ex_vecteur.o ObjetMobile.o constantes.o Systeme.o ChampsForces.o
testIntegrateur1: testIntegrateur1.o Integrateur.o ex_vecteur.o ObjetMobile.o constantes.o Systeme.o ChampsForces.o

testIntegrateur2.o: Integrateur.o ex_vecteur.o ObjetMobile.o constantes.o ChampsForces.o Systeme.o 
testIntegrateur2: testIntegrateur2.o Integrateur.o ex_vecteur.o ObjetMobile.o constantes.o ChampsForces.o Systeme.o 

testIntegrateurN.o: Integrateur.h ex_vecteur.o ObjetMobile.o constantes.o ChampsForces.o Systeme.o 
testIntegrateurN: testIntegrateurN.o Integrateur.o ex_vecteur.o ObjetMobile.o constantes.o ChampsForces.o Systeme.o 

Dessinable.o: Dessinable.h Dessinable.cc ex_vecteur.o SupportADessin.h

Objetcompose.o: Objetcompose.cc Objetcompose.h ex_vecteur.o ChampsForces.cc ChampsForces.h obstacle.o ObjetMobile.o Dessinable.o

Systeme.o: Systeme.cc Systeme.h Dessinable.o ChampsForces.o Objetcompose.o obstacle.o

exerciceP9a.o: exerciceP9a.cc Integrateur.o ObjetMobile.o ex_vecteur.o Systeme.o obstacle.o constantes.cc constantes.h ChampsForces.o
exerciceP9a: exerciceP9a.o Integrateur.o ObjetMobile.o ex_vecteur.o Systeme.o obstacle.o constantes.o ChampsForces.o

testChocs.o: testChocs.cc ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o
testChocs: testChocs.o ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o


testChocs2pendules.o :testChocs2pendules.cc ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o obstacle.o
testChocs2pendules:testChocs2pendules.o ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o obstacle.o

testChocsballeballe.o :testChocsballeballe.cc ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o obstacle.o
testChocsballeballe :testChocsballeballe.o ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o obstacle.o

testChocsballeplan.o :testChocsballeplan.cc ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o obstacle.o
testChocsballeplan :testChocsballeplan.o ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o obstacle.o

testChocsbriquependules.o :testChocsbriquependules.cc ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o obstacle.o
testChocsbriquependules :testChocsbriquependules.o ObjetMobile.o obstacle.o constantes.o ex_vecteur.o Systeme.o ChampsForces.o Integrateur.o obstacle.o
clean:
	rm *.o
	rm *.gch


