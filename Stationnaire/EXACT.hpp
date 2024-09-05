#include <iostream>
#include <cmath>
#include <math.h>
#include"Lire.hpp"

class EXACT
{
public:
  // constructeur
  EXACT(const DOCU& n,const DOCU& docu) : 
  M_n(n), M_exact( new double[n.getM()] ),M_pas( new double[n.getM()] ),M_docu(docu)
  {
   // appele la constructeur VECT qui contient le vecteur de second membre 
    VECT F(n, docu);

    // Initialisation des tableaux des solutions exacte
    for (int i = 0; i < M_n.getM(); ++i)
    {
      M_exact[i]=docu.getTe() + R*(cosh(sqrt(a)*(M_docu.getLX() - F.getM_pas(i))));
    }
  }

  // destructeur
  ~EXACT()
  {
    delete[] M_exact;
	delete[] M_pas;

  }
  //accesseurs
  double getM_exact(int i) const { return M_exact[i]; }
  double getM_pas(int i) const { return M_pas[i]; }
  int n() const { return M_n.getM(); }

private:
  double *M_exact;
  double *M_pas;
  const DOCU& M_docu;
  const DOCU& M_n;
  double h = (M_docu.getLX() / M_n.getM());
  double p = 2 * ( M_docu.getLY()+ M_docu.getLZ());
  double S = M_docu.getLY() * M_docu.getLZ() ;
  double a=((M_docu.gethc()*p)/(M_docu.getk()*S));
  double R=(M_docu.getPhi()/((M_docu.getk()*sqrt(a)*(sinh(sqrt(a)*M_docu.getLX())))));
};
// surcharge de l'opérateur de flux de sortie
std::ostream &operator<<(std::ostream &o, EXACT const &v)
{
  o << " Vecteur de pas :\n";
  for (int i = 0; i < v.n(); ++i)
  {
    o << v.getM_pas(i) << "\n";
  }
  o << " Vecteur exacte :\n";
  for (int i = 0; i < v.n(); ++i)
  {
    o << v.getM_exact(i) << "\n";
  }
  return o;
}
