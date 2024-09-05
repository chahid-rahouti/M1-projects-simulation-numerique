#ifndef lu_HPP
#define lu_HPP
#include<iostream>
#include <cmath>
#include"Lire.hpp"
#include "Matrice.hpp"

class LU
{
public:
  // constructeur
  LU(const DOCU& n, const DOCU& m,const DOCU& docu) : M_n(n), M_m(m),M_docu(docu),
  L(new double *[n.getM()]),U(new double *[n.getM()])
  {
    // appele de constructeur Matrice qui contient la matrice A 
    Matrice matrice(n, m, docu);
     
    for (int i = 0; i < M_n.getM(); ++i)
    { 
        L[i] = new double[m.getM()];
        U[i] = new double[m.getM()];
      for (int j = 2; j < M_m.getM(); ++j)
      {
        if (i == j)
        { // initialisation des matrices L et U
          L[0][0] = matrice.getMAT(0)[0] ;
          U[0][0] =1;
          U[0][1] = matrice.getMAT(0)[1] /L[0][0];
          L[i-1][j-2] =  matrice.getMAT(i-1)[j-2] ;
          L[i-1][j-1] =  matrice.getMAT(i-1)[j-1] - (L[i-1][j-2] * U[i-2][j-1]);
          U[i-1][j-1]=1;
          U[i-1][i]= matrice.getMAT(i-1)[i]/L[i-1][j-1];
        }
        else
        {
          L[i][j] = 0;
          U[i][j] = 0;
        }
      }
    }
    // Conditions supplémentaires
    L[M_n.getM() - 1][M_n.getM() - 2] = matrice.getMAT(M_n.getM() - 1)[M_n.getM() - 2];
    L[M_n.getM() - 1][M_n.getM() - 1] = matrice.getMAT(M_n.getM() - 1)[M_n.getM() - 1] - (L[M_n.getM() - 1][M_n.getM() - 2] * U[M_n.getM() - 2][M_n.getM() - 1]);
    U[M_n.getM() - 1][M_n.getM() - 1] = 1;
    
  }
    

  
  // destructeur
  ~LU()
  {
    for (int i = 0; i < M_n.getM(); ++i)
    {
      delete[] L[i];
      delete[] U[i];
    }
    delete[] L;
    delete[] U;
  }

  double *getL(int i) const { return L[i]; }
  double *getU(int i) const { return U[i]; }
  //acceceeur
  int n() const { return M_n.getM(); }
  int m() const { return M_m.getM(); }

private:
const DOCU& M_docu;
const DOCU& M_n;
const DOCU& M_m;
  //int M_n;
  //int M_m;
  double **L;
  double **U;
  double h = (M_docu.getLX() / M_n.getM());
  //double k = 164;
  //double hc = 200;
  double p = 2 * ( M_docu.getLY()+ M_docu.getLZ());
  double S = M_docu.getLY() * M_docu.getLZ() ;
};
// surcharge de l'opérateur de flux de sortie
std::ostream &operator<<(std::ostream &o, LU const &v)
{
  o << "L:\n";
  for (int i = 0; i < v.n(); ++i)
  {
    for (int j = 0; j < v.m(); ++j)
      o << v.getL(i)[j] << " ";
    o << "\n";
  }
  return o;
}
#endif
