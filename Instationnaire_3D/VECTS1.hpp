#include <iostream>
#include <cmath>
#include"Lire.hpp"
#include"matrice.hpp"
#include"VECT.hpp"
#include"LU.hpp"

class VECTS1
{
public:
  // constructeur
  VECTS1(const DOCU& n,const DOCU& m,const DOCU& t, const DOCU& docu) : 
  M_n(n),M_m(m),M_docu(docu),M_s(t),
  X(new double[n.getM()]),Y(new double[n.getM()]),T(new double *[n.getM()]),T_i(new double [n.getM()])
  { 
    // appele des matrices L et U 
    LU lu(n, m, docu);
    // appele de seconde membre
    VECT F(n,t, docu);
    // Initialisation des tableaux T_solution

    for (int i = 0; i < M_n.getM(); ++i)
{
    T[i] = new double[t.getN()+1];
    
    
}
  // calcule des T^n+1 à partir de T^n pour chaque pas de temps
    for(int k=0;k<M_s.getN();k++)
    { 
      
      R =  (docu.getPhi());
    
      //T[k] = new double[t.getN()];
      for (int i = 0; i < M_n.getM(); ++i)
      {   
        // Initialisation des tableaux T0
          T[i][0] = docu.getTe();
           // Initialisation des tableaux Y_solution
          Y[0] =  (T[0][k] + R)/lu.getL(0)[0];
          Y[i]= ((M*T[i][k] + F.getM_b(i)) - (lu.getL(i)[i-1] * Y[i-1]))/lu.getL(i)[i];
          Y[M_n.getM()-1]= ((T[M_n.getM()-1][k] + F.getM_b(M_n.getM()-1)) - (lu.getL(i)[M_n.getM()-2] * Y[M_n.getM()-2]))/lu.getL(M_n.getM()-1)[M_n.getM()-1];
      }
    
     // Initialisation des tableaux X_solution
    for (int i = M_n.getM() - 1; i >= 0; --i)
    {
        X[M_n.getM() - 1] = Y[M_n.getM() - 1];
        X[i] = Y[i] - (lu.getU(i)[i+1] * X[i+1]);
        T[i][k+1]=X[i];
    }

// calcule de T_chapeau de 3D mais à chaque pas de tepms 
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


 
}
     
    
  
  

  // destructeur
  ~VECTS1()
  {
    for (int i = 0; i < M_n.getM(); ++i)
    {
      
      //delete[] X[i];
	    //delete[] Y[i];
      delete[] T[i];
    }
    
	delete[] X;
	delete[] Y;
  delete[] T;
  delete[] T_i;

  }
  double getX(int i) const { return X[i]; }
  double getY(int i) const { return Y[i]; }
  double *getT(int i) const { return T[i]; }
  double getT_i(int i) const { return T_i[i]; }

  int n() const { return M_n.getM(); }
  int t() const { return M_s.getN(); }

private:
  double *X;
  double *Y;
  double *T_i;
  double R;
  //double R;
  const DOCU& M_docu;
  const DOCU& M_n;
  const DOCU& M_m;
  const DOCU& M_s;
  double **T;
  double h = (M_docu.getLX() / M_n.getM());
  double hx = (M_docu.getLX() / M_n.getMx());
  double p = 2 * ( M_docu.getLY()+ M_docu.getLZ());
  double S = M_docu.getLY() * M_docu.getLZ() ;
  double dt = (double) M_docu.getTF()/M_docu.getN();
  double M = ((M_docu.getRho()*M_docu.getCp())/dt);
};
// surcharge de l'opérateur de flux de sortie
std::ostream &operator<<(std::ostream &o, VECTS1 const &v)
{
   
 // o << " Vecteur T :\n";
 // for (int j = 0; j < v.t()+1; ++j)
 // { for (int i = 0; i < 1; ++i)
    //  o << v.getT(i)[j] << " ";
    //o << "\n";
//}

  return o;
}
