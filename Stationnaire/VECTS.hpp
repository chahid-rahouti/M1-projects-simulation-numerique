#include <iostream>
#include <cmath>
#include"Lire.hpp"
#include"Matrice.hpp"
#include"VECT.hpp"
#include"LU.hpp"

class VECTS
{
public:
  // constructeur
  VECTS(const DOCU& n,const DOCU& m, const DOCU& docu) : 
  M_n(n),M_m(m),M_docu(docu),
  X(new double[n.getM()]),Y(new double[n.getM()])
  { // appele de construteur LU qui contient les matrices L et U
    LU lu(n, m, docu);
    // appele de construteur VECT qui contient le vecteur de seconde membre pour calculer les solutions
    VECT F(n, docu);
   // Initialisation des tableaux Y_solution
    for (int i = 1; i < M_n.getM(); ++i)
    {   
        Y[0] = F.getM_b(0)/lu.getL(0)[0];
        Y[i]= (F.getM_b(i) - (lu.getL(i)[i-1] * Y[i-1]))/lu.getL(i)[i];
    }
     // Initialisation des tableaux X_solution
    for (int i = M_n.getM() - 1; i >= 0; --i)
    {
        X[M_n.getM() - 1] = Y[M_n.getM() - 1];
        X[i] = Y[i] - (lu.getU(i)[i+1] * X[i+1]);
    }
  }

  // destructeur
  ~VECTS()
  {
    
	delete[] X;
	delete[] Y;

  }
  double getX(int i) const { return X[i]; }
  double getY(int i) const { return Y[i]; }

  int n() const { return M_n.getM(); }
  int m() const { return M_n.getM(); }

private:
  double *X;
  double *Y;
  const DOCU& M_docu;
  const DOCU& M_n;
  const DOCU& M_m;
  double h = (M_docu.getLX() / M_n.getM());
  double p = 2 * ( M_docu.getLY()+ M_docu.getLZ());
  double S = M_docu.getLY() * M_docu.getLZ() ;
};
// surcharge de l'opérateur de flux de sortie
std::ostream &operator<<(std::ostream &o, VECTS const &v)
{


  
  o << " Vecteur Y :\n";
  for (int i = 0; i < v.n(); ++i)
  {
    o << v.getY(i) << "\n";
  }
  o << " Vecteur solution X :\n";
  for (int i = 0; i < v.n(); ++i)
  {
    o << v.getX(i) << "\n";
  }

  return o;
}
