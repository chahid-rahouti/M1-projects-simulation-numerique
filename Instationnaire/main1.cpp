#include <iostream>
#include <math.h>
#include "LU.hpp"
#include "VECT.hpp"
#include "VECTS1.hpp"






int main()
{ 
  // appeler le constructeur DUCU pour les donnees 
  DOCU docu("simu.cfg");
  // appeler le constructeur DUCU pour M
  DOCU M_n("simu.cfg");
  // appeler le constructeur DUCU pour N
  DOCU M_s("simu.cfg");
  // appele de la matrice A 
  Matrice MATRICEE(M_n, M_n,docu);
  //std::cout << "A : " << "\n"<<MATRICEE << "\n";
  // appele des matrices de la décomposition L,U 
  LU lu(M_n, M_n,docu);
  //std::cout << "L and U : " << "\n"<<lu << "\n";
   // appele de seconde membre F et le pas de temps et d'espace
  VECT vect(M_n,M_s,docu);
  //std::cout << "CIC : " << "\n"<<vect << "\n";
   // appele de la solution
  VECTS1 vects1(M_n,M_n,M_s,docu);
  std::cout << "CIC : " << "\n"<<vects1 << "\n";
  //// nom du fichier de sortie 
  std::ofstream fichier_csv("resultats_Temps.csv");
  if (fichier_csv.is_open())
  {
    // En-têtes
    fichier_csv << "x,SolX0,SolXM_2,SolXM\n";
    // Données
    for (int i = 0; i < vects1.t(); ++i)
    {
      //enregistrement pas de temps , solution à X0 ,solution Xm/2   et solution Xm
      fichier_csv << vect.getM_temps(i) << "," << vects1.getT(0)[i] << "," << vects1.getT(vects1.n()/2)[i] <<"," << vects1.getT(vects1.n()-1)[i] << "\n";
    }

    fichier_csv.close();
    std::cout << "Les résultats ont été enregistrés dans resultats.csv.\n";
  }
  else
  {
    std::cerr << "Erreur lors de l'ouverture du fichier CSV.\n";
  }

  return 0;
}
