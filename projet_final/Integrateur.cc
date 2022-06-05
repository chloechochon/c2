#include "Integrateur.h"
#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "constantes.h"

using namespace std;


void Integrateur::integre(ObjetMobile& M){
	// On ne peut pas directement placer M.setP ( M.getP() + ... etc) car sinon les valeurs auront change pour le calcul suivant de la derivee, ce qu on ne veut pas ici
		Vecteur nouv_P (M.getP() + (dt*M.getPd()));
		cout << "nouvelle position " << nouv_P << endl;
		Vecteur nouv_Pd (M.getPd() + (dt*M.evolution() ));
		cout << "nouvelle vitesse " << nouv_Pd << endl;
		cout << " acceleration " << M.evolution() << endl;
		M.setP (nouv_P);
		M.setPd (nouv_Pd);
}

void IntegrateurEulerCromer::integre(ObjetMobile& M) {
		 Vecteur nouv_Pd ( M.getPd() + (dt*M.evolution()));
    		 M.setPd ( nouv_Pd);
    		 M.setP (M.getP() + (dt*M.getPd()));
}

void IntegrateurNewmark::integre(ObjetMobile& M) {
		Vecteur s;
		Vecteur r;
		Vecteur Pn_1 (M.getP());
		Vecteur Pdn_1 (M.getPd());
		Vecteur q;
		s=M.evolution();
		
		do{
			q=M.getP();
			r=M.evolution();
			M.setPd(Pdn_1+(dt/2)*(r+s));
			M.setP(Pn_1+dt*Pdn_1+dt*dt*(1/3)*((1/2)*r+s));
			
		} while ((M.getP()-q).norme()>=epsilon);

}

