
#include <iostream>  
#include <vector>
#include <initializer_list>
#pragma once

class Vecteur {  
    private:
    std::vector<double> vecteur;
    
    
    public:
    // Comme demandé, on a créé un constructeur pour vecteur nul mmais on l'a au final supprimé:
    // le constructeur pour vecteur lambda peut en effet confondre si la dimension du vecteur est de 1 car on l initialiserait comme Vecteur P (1);
    // De plus on n en voyait pas l utilite, ayant deja une constante vecteur nul de trois dimensions (les dimensions ne risquant pas de depasser 3)
    /*
    //constructeur du vecteur nul
    Vecteur (int dim) {
        for(int i(0);i<dim;i++){
            vecteur.push_back(0.0);
        }
    }
    */
    //Constructeur vecteur
    Vecteur(std::initializer_list<double> const& data) : vecteur(data) {};
    
    // On surcharge les constructeurs afin de pouvoir initialiser des vecteurs qui pourront avoir différentes dimensions:  une, deux ou trois dimensions (un vecteur de deux dimentions est un vecteur de 3 dimention avec un 0 dans la dernier composante 
    Vecteur () {}
	Vecteur (double x) {vecteur.push_back(x);}
	Vecteur (double x, double y) { vecteur.push_back(x); vecteur.push_back(y);}
    Vecteur (double x, double y, double z) {vecteur.push_back(x); vecteur.push_back(y); vecteur.push_back(z);}


    //methode
    std::vector<double> getvecteur() const;
    void setvecteur(std::vector<double> vec);
    double getcomposante(size_t i) const;

    size_t taille() const;
    
    

    double norme() const;
    double norme2() const;
    
    void augmente(double aug);
    void set_coord(size_t coord, double valeur);
    void dimension( Vecteur autre); //pour savoir si les vecteurs sont de la meme taille
    
  //Remplacés en opérateurs
///    Vecteur addition (Vecteur autre) const;
///    Vecteur soustraction (Vecteur autre) const;
///    Vecteur oppose () const;
///    Vecteur mult (double a) const;
///    Vecteur prod_vect (Vecteur autre) const;
///    Vecteur unitaire () const;
///    void affiche() const;
///    bool compare(Vecteur v) const;
///  double prod_scal (Vecteur autre) const;
    
    //Opérateurs
    bool operator==(const Vecteur& v) const;
    Vecteur operator+=(const Vecteur& autre);
    Vecteur operator-=(const Vecteur& autre);
    Vecteur operator+(const Vecteur& autre) const;
    Vecteur operator-(const Vecteur& autre) const;
    Vecteur operator-() const; // oppose
    Vecteur operator*=(const Vecteur& autre);
     Vecteur operator*(const double lambda) const;
    Vecteur operator*(const Vecteur& autre) const;
    Vecteur operator^(const Vecteur&  autre)const ; // produit vectoriel
    Vecteur operator!() const; // vecteur unitaire
    double operator|(const Vecteur&  autre) const; // produit scalaire

};

double carre(double a);
 std::ostream& operator<<(std::ostream& sortie, Vecteur const& v);
 Vecteur operator*(double lambda, Vecteur const& V) ;
 double operator|(double lambda, const Vecteur&  autre) ;
 











