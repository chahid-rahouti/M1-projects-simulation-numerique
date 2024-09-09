#include <iostream>
#include <math.h>
#include "LU.hpp"
#include "VECT.hpp"
#include "VECTS.hpp"
//#include "EXACT.hpp"

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
  // appeler le constructeur DUCU pour N
  DOCU M_s(config_file);
  // appele de la matrice A 
  Matrice MATRICEE(M_n, M_n, docu);
  //std::cout << "A : " << "\n"<<MATRICEE << "\n";
  // appele des matrices de la décomposition L,U 
  LU lu(M_n, M_n, docu);
  //std::cout << "L and U : " << "\n"<<lu << "\n";
  // appele de seconde membre F et le pas de temps et d'espace 
  VECT vect(M_n, M_s, docu);
  //std::cout << "CIC : " << "\n"<<vect << "\n";
  // appele de la solution
  VECTS vects(M_n, M_n, M_s, docu);
  std::cout << "CIC : " << "\n"<<vects << "\n";
  //// nom du fichier de sortie 
  std::ofstream fichier_csv("resultats210.csv");
  if (fichier_csv.is_open())
  {
    // En-têtes
    fichier_csv << "x,Sol210\n";
    // Données
    for (int i = 0; i < vects.n(); ++i)
    {
      //enregistrement de solution et pas d'espace 
      fichier_csv << MATRICEE.getM_pas(i) << "," << vects.getX(i) << "\n";
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