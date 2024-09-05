#ifndef vect_HPP
#define vect_HPP
#include <iostream>
#include <cmath>
#include"Lire.hpp"

class VECT
{
public:
  // constructeur
  VECT(const DOCU& n,const DOCU& docu) : 
  M_n(n), M_b( new double[n.getM()] ),M_pas( new double[n.getM()] ),M_docu(docu)
  {
   // Initialisation des  pas d'espaces
    for (int i = 0; i < M_n.getM(); ++i)
      M_pas[i] = i * h;

    // Initialisation de vecteur de seconde membre
    for (int i = 0; i < M_n.getM(); ++i)
    {
      if (i == 0)
      {
        M_b[0] = docu.getPhi();
      }
      else if (i == M_n.getM() - 1)
      {
        M_b[M_n.getM() - 1] = 0;
      }
      else
      {
        M_b[i] = docu.gethc() * p * docu.getTe() / S;
      }
    }
  }
    
    

  // destructeur
  ~VECT()
  {
    delete[] M_b;
	delete[] M_pas;

  }
  double getM_b(int i) const { return M_b[i]; }
  double getM_pas(int i) const { return M_pas[i]; }

  int n() const { return M_n.getM(); }

private:
  double *M_b;
  double *M_pas;
  const DOCU& M_docu;
  const DOCU& M_n;
  double h = (M_docu.getLX() / M_n.getM());
  double p = 2 * ( M_docu.getLY()+ M_docu.getLZ());
  double S = M_docu.getLY() * M_docu.getLZ() ;
};
// surcharge de l'opérateur de flux de sortie
std::ostream &operator<<(std::ostream &o, VECT const &v)
{
  o << " Vecteur de pas :\n";
  for (int i = 0; i < v.n(); ++i)
  {
    o << v.getM_pas(i) << "\n";
  }
  o << " Vecteur b :\n";
  for (int i = 0; i < v.n(); ++i)
  {
    o << v.getM_b(i) << "\n";
  }
  return o;
}
#endif
