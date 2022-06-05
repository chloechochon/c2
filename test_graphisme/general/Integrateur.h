#pragma once

#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "constantes.h"

//Ce fichier introduit les differents intégrateurs qu'on peut utiliser


class Integrateur {
// Represente un integrateur quelconque
	public:
	// Constructeur
	Integrateur (double t_ = 0.01)	//On met une valeur par défaut arbitraire assez petite au pas de temps dt
	 : dt(t_) {}
	
	//Cette methode correspond aux calculs effectues sur la position et la vitesse de l ObjetMobile pris en argument pour le faire evoluer selon dt
	//elle est virtuelle car chaque integrateur a ses propres calculs plus ou moins precis
	virtual void integre(ObjetMobile& M);
	
	protected:
	double dt; // laps de temps pour integrer
	
	

};



class IntegrateurEulerCromer : public Integrateur {	//IntegrateurEulerCromer est une sous classe d'Integrateur
		public:

	IntegrateurEulerCromer (double t =0.01)
	: Integrateur (t) {}
	
	virtual void integre(ObjetMobile& M) override;
	
	
	
	
};


class IntegrateurNewmark : public Integrateur {	//IntegrateurNewmark est une sous classe d'Integrateur
	public:
	IntegrateurNewmark (double t =0.01)
	: Integrateur (t) {}
	virtual void integre(ObjetMobile& M) override;
	
	};
