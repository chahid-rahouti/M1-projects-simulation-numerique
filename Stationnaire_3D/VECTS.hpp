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
  X(new double[n.getM()]),Y(new double[n.getM()]),T_i(new double[n.getMx()])
  { // appele des matrices L et U 
    LU lu(n, m, docu);
    // appele de vecteur de seconde membre
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
  // calcule de T chapeau pour la solution de 3D
for(int i=0;i<M_n.getMx();i++)
{
  double xi00=i*hx;
  int k=0;
  for(int j=0;j<M_n.getM();j++)
  {
    double xj=j*h;
    if(xi00>=xj && xi00<=xj+h)
    {
      k=j;
      break;
    }
  }
  double a= (X[k+1]-X[k]) / h;
  double b= X[k] - a* k*h;
      T_i[i] = a*xi00 + b;
  
}
}


  // destructeur
  ~VECTS()
  {
    
	delete[] X;
	delete[] Y;
  delete[] T_i;

  }
  double getX(int i) const { return X[i]; }
  double getY(int i) const { return Y[i]; }
  double getT_i(int i) const { return T_i[i]; }

  int n() const { return M_n.getM(); }
  int m() const { return M_n.getMx(); }

private:
  double *X;
  double *Y;
  double *T_i;
  const DOCU& M_docu;
  const DOCU& M_n;
  const DOCU& M_m;
  double h = (M_docu.getLX() / M_n.getM());
  double hx = (M_docu.getLX() / M_n.getMx());
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
  o << " Vecteur solution T_i :\n";
  for (int i = 0; i < v.m(); ++i)
  {
    o << v.getT_i(i) << "\n";
  }

  return o;
}
