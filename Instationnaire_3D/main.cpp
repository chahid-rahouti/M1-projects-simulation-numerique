#include <iostream>
#include <math.h>
#include "LU.hpp"
#include "VECT.hpp"
#include "VECTS1.hpp"
#include<sstream>
#include <filesystem>
namespace fs = std::filesystem;







int main()
{ // appeler le constructeur DUCU pour les donnees 
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
// nom du répertoire de sortie 
 std::string outputDirectory = "chahid_vtk";  

    // Vérifiez si le répertoire existe
    if (!fs::is_directory(outputDirectory))
    {
        fs::create_directory(outputDirectory);
    }

  // cette boucle pour chaque instanat enregistre la solution 
  for(int k=0;k<M_s.getN();k++)
  {//enregistrement des solutions
    std::stringstream CHAHID;
    CHAHID << outputDirectory << "/resultats_Temps_" << k << ".vtk";
  std::ofstream fichier_vtk(CHAHID.str());
  if (fichier_vtk.is_open())
  {
    // En-têtes
    // Données
    //fichier_vtk << "x,Sol1\n";
    fichier_vtk << "# vtk DataFile Version 2.0\n";
    fichier_vtk << "vtk output\n";
    fichier_vtk << "ASCII\n";
    fichier_vtk <<"DATASET STRUCTURED_GRID\n";
    fichier_vtk <<"DIMENSIONS "<< (docu.getMx())<<" "<<(docu.getMy())<< " "<<(docu.getMz())<<" "<<"\n";
    fichier_vtk <<"POINTS "<< (docu.getMx())*(docu.getMy())*(docu.getMz())<<" float\n";
    for(int k=0;k<docu.getMz();k++)
    {
      for(int j=0;j<docu.getMy();j++)
      {
        for(int i=0;i<docu.getMx();i++)
        {
         fichier_vtk <<i<<" "<<j<< " "<<k<<" "<<"\n";
        }
      }

    }
    fichier_vtk <<"POINT_DATA "<<(docu.getMx())*(docu.getMy())*(docu.getMz())<<"\n";
    fichier_vtk <<"FIELD FieldData 1\n";
    fichier_vtk <<"sol1 "<<"1"<<" "<< (docu.getMx())*(docu.getMy())*(docu.getMz())<<" float\n";
    for(int k=0;k<docu.getMz();k++)
    {
      for(int j=0;j<docu.getMy();j++)
      {
        for(int i=0;i<docu.getMx();i++)
        {
         fichier_vtk <<vects1.getT_i(i)<<"\n";
        }
      }

    }
    

    fichier_vtk.close();
            std::cout << "Les résultats pour le temps " << k << " ont été enregistrés dans " << CHAHID.str() << ".\n";
  }
  else
  {
    std::cerr << "Erreur lors de l'ouverture du fichier vfichier_vtk.\n";
  }
  }
  
//pour éxuction de ce program il faut ajouter -std=c++17  à cause de cette fonction std::filesystem;
  return 0;
}
