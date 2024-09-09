#include <iostream>
#include <math.h>
#include "Matrice.hpp"
#include "LU.hpp"
#include "VECT.hpp"
#include "VECTS.hpp"
#include "EXACT.hpp"

int main(int argc, char* argv[])
{ 
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <config_file>\n";
    return 1;
  }

  const char* config_file = argv[1];

  // appeler le constructeur DUCU pour les donnees 
  DOCU docu(config_file);
  // appeler le constructeur DUCU pour M
  DOCU M_n(config_file);
  // appele de la matrice A 
  Matrice MATRICE(M_n, M_n, docu);
  //std::cout << "MATRICE : " << "\n"<<MATRICE << "\n";
  // appele de seconde membre F et le pas de temps et d'espace
  VECT vect(M_n, docu);
  //std::cout << "vecteur : " << "\n"<<vect << "\n";
  // appele des matrices de la décomposition L,U 
  LU lu(M_n, M_n, docu);
  //std::cout << "MATRICE : " << "\n"<<lu << "\n";
  // appele de la solution approcher
  VECTS vects(M_n, M_n, docu);
  //std::cout << "vecteur : " << "\n"<<vects << "\n";
  // appele de la solution exacte
  EXACT exact(M_n, docu);
  //std::cout << "vecteur : " << "\n"<<exact << "\n";
  std::ofstream fichier_csv("resultats2.csv");
  if (fichier_csv.is_open())
  {
    // En-têtes
    fichier_csv << "x,Sol_ap,Sol_exact\n";

    // Données
    for (int i = 0; i < vects.n(); ++i)
    {
      //enregistrement  pas d'espace , la solution approche  et solution exacte
      fichier_csv << vect.getM_pas(i) <<"," << vects.getX(i) << "," << exact.getM_exact(i) << "\n";
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