#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"
using namespace std;


int main()
{
  TextViewer ecran(cout);

  Systeme le_systeme;

  //On a construit la balle (en 2D selon les instructions de l'exercice de P7)
  Vecteur pos (0, 0,0);
  Vecteur vit (1.5, 2.0,0.0);
  double masse (0.127);
  Balle b (pos,vit,masse,vecnull);

  // on va utiliser la copie polymorphique avec des unique ptr
  le_systeme.ajoute(new Balle (b));

  //construction d'un obstacle (ici un plan)
  Vecteur orig({0.0,0.0,0.0});
  Vecteur di1({0.0,1.0,0.0});
  Vecteur di2({1.0,0.0,0.0});
  Plan P(orig,di1,di2);

  //meme idee qu'avant mais ici on ajoute un systeme
  le_systeme.ajoute(new Plan (P));


  // On souhaite faire une etude du mouvement de la balle avec l integrateur sur n intervalles de dt seconde car on utilise les meme condition que l'exercice P7
  unsigned int n;
  do{
      cout << "Sur combien d'intervalles de temps voulez-vous étudier le mouvement de la balle? ";
      cin >> n;
  } while ( n <=0);

  double dt;
  cout << "quel est le dt ?" <<endl;
  cin >> dt;
  cout << endl;


  cout<< "avant l'evolution : " << endl;
  le_systeme.dessine_sur(ecran);
  cout<< endl;

  cout << endl;

      for (size_t i(0); i <n; i++){
      cout <<" evolution ... "<<endl;
      cout << endl;
      le_systeme.evolue2(dt);
      le_systeme.dessine_sur(ecran);

}


  cout<< endl;




  return 0;
}
