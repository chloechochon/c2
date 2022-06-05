
#include <iostream>  
#include <vector>
#include <initializer_list>
#pragma once

class Vecteur {  
    private:
    std::vector<double> vecteur;
    
    
    public:
    // Comme demandé, on a créé un constructeur pour vecteur nul mmais on l'a au final supprimé:
    // on n en voyait pas l utilite, ayant deja une constante vecteur nul de trois dimensions (les dimensions ne risquant pas de depasser 3 dans ce projet)
    
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

    size_t taille() const;	//renvoie la taille (la dimension) du Vecteur
    double norme() const;	//renvoie la norme du vecteur
    double norme2() const;	//renvoie le carre de la norme
    
    void augmente(double aug);	//augmente la dimension du vecteur de 1 en placant en push_back la valeur donnee en argument
    void set_coord(size_t coord, double valeur);	//modifie la ième coordonee du Vecteur avec la valeur donnee en argument
    void dimension( Vecteur autre); //pour savoir si les vecteurs sont de la meme taille
    
    //Surcharge d'opérateurs
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

double carre(double a);	//Pour simplifier le calcul de puissances en renvoyant la valeur au carré
 std::ostream& operator<<(std::ostream& sortie, Vecteur const& v);
 Vecteur operator*(double lambda, Vecteur const& V) ;	// pour avoir les deux sens de multiplication entre un scalaire et un vecteur
 double operator|(double lambda, const Vecteur&  autre) ; //pour avoir le produit scalaire avec un scalaire (attention a l ordre)
 











