#include <iostream>
#include <vector>
#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "constantes.h"
#include "ChampsForces.h"

using namespace std;


int main(){
    Vecteur pos(0.0 , 7.0 , 0.0);
    Vecteur vit(1.0 , 1.0 , 1.0);
    Vecteur F(1.0 , 0.0 , 0.0);
	cout <<"pb" <<endl;
    Balle b(pos, vit, 2.0, vecnull, 1.0, 2.0, 1);
    b.ajoute_force(F);
    b.affiche();
    
    cout << "Vecteur accélération: " << endl;
    cout << b.evolution() << endl;
    
    /// Comment tester copieobjet()? Vu que c est un pointeur
    /// Il manque un agit sur dans balle??
    ///A quoi sert ajoute_a dans ObjetMobile?
    /// tester point plus proche
    
    return 0;
}





