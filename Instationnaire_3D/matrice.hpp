#ifndef MATRICE_HPP
#define MATRICE_HPP
#include <iostream>
#include <cmath>
#include "Lire.hpp"

class Matrice
{
public:
  // constructeur
  Matrice(const DOCU& n, const DOCU& m,const DOCU& docu) : M_n(n), M_m(m),M_docu(docu),
  M_MAT(new double *[n.getM()]),M_pas(new double[n.getM()])
  {
    // Initialisation des tableaux M_pas
    for (int i = 0; i < M_n.getM(); ++i)
      M_pas[i] = i * h;
    // Initialisation de la matrice M_MAT 
    for (int i = 0; i < M_n.getM(); ++i)
    {
      M_MAT[i] = new double[m.getM()];
      for (int j = 0; j < M_m.getM(); ++j)
      {
        if (i == j)
        {
          M_MAT[i][j] = M + (2 * M_docu.getk() / std::pow(h, 2)) + ( M_docu.gethc()*p /S );
        }
        else if (i == j + 1)
        {
          M_MAT[i][j] = -(( M_docu.getk() / std::pow(h, 2)));
        }
        else if (i == j - 1)
        {
          M_MAT[i][j] = -(( M_docu.getk() / std::pow(h, 2)));
        }
        else
          M_MAT[i][j] = 0;
      }
    }
    // Conditions supplémentaires
    M_MAT[0][0] = ( (M_docu.getk() / h));
    M_MAT[M_n.getM() - 1][M_n.getM() - 1] = (   (M_docu.getk() / h));
    M_MAT[0][1] = - ( M_docu.getk() / h);
    M_MAT[M_n.getM() - 1][M_n.getM() - 2] = -( M_docu.getk() / h);

  }
  // destructeur
  ~Matrice()
  {
    for (int i = 0; i < M_n.getM(); ++i)
    {
      delete[] M_MAT[i];
    }
    delete[] M_MAT;
    delete[] M_pas;
  }

  double *getMAT(int i) const { return M_MAT[i]; }
  double getM_pas(int i) const { return M_pas[i]; }
  //acceceeur
  int n() const { return M_n.getM(); }
  int m() const { return M_m.getM(); }

private:
const DOCU& M_docu;
const DOCU& M_n;
const DOCU& M_m;
  //int M_n;
  //int M_m;
  double **M_MAT;
  double *M_pas;
  double h = (M_docu.getLX() / M_n.getM());
  //double k = 164;
  //double hc = 200;
  double p = 2 * ( M_docu.getLY()+ M_docu.getLZ());
  double S = M_docu.getLY() * M_docu.getLZ() ;
  double dt = (double)M_docu.getTF()/M_docu.getN();
  double M = ((M_docu.getRho()*M_docu.getCp())/dt);
  
};
// surcharge de l'opérateur de flux de sortie
std::ostream &operator<<(std::ostream &o, Matrice const &v)
{
  o << "Matrice:\n";
  for (int i = 0; i < v.n(); ++i)
  {
    for (int j = 0; j < v.m(); ++j)
      o << v.getMAT(i)[j] << " ";
    o << "\n";
  }
  return o;
}
#endif
