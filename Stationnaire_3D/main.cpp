#include <iostream>
#include <math.h>
#include "Matrice.hpp"
#include "LU.hpp"
#include "VECT.hpp"
#include "VECTS.hpp"

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
  // appele de la solution
  VECTS vects(M_n, M_n, docu);
  //std::cout << "vecteur : " << "\n"<<vects << "\n";
  // nom du fichier de sortie 
  std::ofstream fichier_csv("resultats1.vtk");
  if (fichier_csv.is_open())
  {
    // En-têtes
    // les étaps de pojet 
    fichier_csv << "# vtk DataFile Version 2.0\n";
    fichier_csv << "vtk output\n";
    fichier_csv << "ASCII\n";
    fichier_csv <<"DATASET STRUCTURED_GRID\n";
    fichier_csv <<"DIMENSIONS "<< (docu.getMx())<<" "<<(docu.getMy())<< " "<<(docu.getMz())<<" "<<"\n";
    fichier_csv <<"POINTS "<< (docu.getMx())*(docu.getMy())*(docu.getMz())<<" float\n";
    for(int k=0; k<docu.getMz(); k++)
    {
      for(int j=0; j<docu.getMy(); j++)
      {
        for(int i=0; i<docu.getMx(); i++)
        {
         fichier_csv <<i<<" "<<j<< " "<<k<<" "<<"\n";
        }
      }
    }
    fichier_csv <<"POINT_DATA "<<(docu.getMx())*(docu.getMy())*(docu.getMz())<<"\n";
    fichier_csv <<"FIELD FieldData 1\n";
    fichier_csv <<"sol1 "<<"1"<<" "<< (docu.getMx())*(docu.getMy())*(docu.getMz())<<" float\n";
    for(int k=0; k<docu.getMz(); k++)
    {
      for(int j=0; j<docu.getMy(); j++)
      {
        for(int i=0; i<docu.getMx(); i++)
        {
          //enregistrement des solutions de T chapeau 
         fichier_csv <<vects.getT_i(i)<<"\n";
        }
      }
    }

    fichier_csv.close();
    std::cout << "Les résultats ont été enregistrés dans resultats1.vtk.\n";
  }
  else
  {
    std::cerr << "Erreur lors de l'ouverture du fichier CSV.\n";
  }

  return 0;
}