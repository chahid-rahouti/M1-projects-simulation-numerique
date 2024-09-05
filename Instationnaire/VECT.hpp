#ifndef vect_HPP
#define vect_HPP
#include <iostream>
#include <cmath>
#include"Lire.hpp"

class VECT
{
public:
  // constructeur
  VECT(const DOCU& n,const DOCU& t,const DOCU& docu) : 
  M_n(n),M_s(t), M_b( new double[n.getM()] ),M_temps( new double[t.getN()] ),M_docu(docu)
  {
   // Initialisation des pas de temps 
    for (int i = 0; i <= M_s.getN(); ++i)
    {
      M_temps[i] =  i * (docu.getTF()/docu.getN());
    }
    // Initialisation de vecteur de seconde membre
    for (int i = 0; i < M_n.getM(); ++i)
    {
      if (i == 0)
      {
        M_b[0] =  (docu.getPhi());
      }
      else if (i == M_n.getM() - 1)
      {
        M_b[M_n.getM() - 1] = 0;
      }
      else
      {
        M_b[i] =  ((docu.gethc() * p * docu.getTe())/ S) ;
      }
    }
  }
    
    

  // destructeur
  ~VECT()
  {
    delete[] M_b;
	delete[] M_temps;

  }
  double getM_b(int i) const { return M_b[i]; }
  double getM_temps(int i) const { return M_temps[i]; }

  int n() const { return M_n.getM(); }
  int t() const { return M_s.getN(); }

private:
  double *M_b;
  double *M_temps;
  const DOCU& M_docu;
  const DOCU& M_n;
  const DOCU& M_s;
  double h = (M_docu.getLX() / M_n.getM());
  double p = 2 * ( M_docu.getLY()+ M_docu.getLZ());
  double S = M_docu.getLY() * M_docu.getLZ() ;
  double dt = M_docu.getTF()/M_docu.getN();
  double M = ((M_docu.getRho()*M_docu.getCp())/dt);
};
// surcharge de l'opérateur de flux de sortie
std::ostream &operator<<(std::ostream &o, VECT const &v)
{
  o << " Vecteur de pas de temps :\n";
  for (int i = 0; i <= v.t(); ++i)
  {
    o << v.getM_temps(i) << "\n";
  }
  o << " Vecteur b :\n";
  for (int i = 0; i < v.n(); ++i)
  {
    o << v.getM_b(i) << "\n";
  }
  return o;
}
#endif
