#include <iostream>
#include <cmath>
#include"Lire.hpp"
#include"matrice.hpp"
#include"VECT.hpp"
#include"LU.hpp"

class VECTS
{
public:
  // constructeur
  VECTS(const DOCU& n,const DOCU& m,const DOCU& t, const DOCU& docu) : 
  M_n(n),M_m(m),M_docu(docu),M_s(t),
  X(new double[n.getM()]),Y(new double[n.getM()]),T(new double *[n.getM()])
  { 
    // appele les matrices L et U
    LU lu(n, m, docu);
    // le vecteur de seconde membre 
    VECT F(n,t, docu);
    // Initialisation des tableaux U_solution

    for (int i = 0; i < M_n.getM(); ++i)
{
  // initialisation  de tableau de solution  
    T[i] = new double[t.getN()+1];
}
   
    for(int k=0;k<M_s.getN();k++)
    { 
      
      for (int i = 0; i < M_n.getM(); ++i)
      {   
        // Initialisation des tableaux Y_solution
          T[i][0] = docu.getTe();
          Y[0] =  (T[0][k] + F.getM_b(0))/lu.getL(0)[0];
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
    
    }
     
    
  }
  

  // destructeur
  ~VECTS()
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

  }
  double getX(int i) const { return X[i]; }
  double getY(int i) const { return Y[i]; }
  double *getT(int i) const { return T[i]; }

  int n() const { return M_n.getM(); }
  int t() const { return M_s.getN(); }

private:
  double *X;
  double *Y;
  const DOCU& M_docu;
  const DOCU& M_n;
  const DOCU& M_m;
  const DOCU& M_s;
  double **T;
  double h = (M_docu.getLX() / M_n.getM());
  double p = 2 * ( M_docu.getLY()+ M_docu.getLZ());
  double S = M_docu.getLY() * M_docu.getLZ() ;
  double dt = (double) M_docu.getTF()/M_docu.getN();
  double M = ((M_docu.getRho()*M_docu.getCp())/dt);
};
// surcharge de l'opérateur de flux de sortie
std::ostream &operator<<(std::ostream &o, VECTS const &v)
{
   //o << " Vecteur Y :\n";
  //for (int i = 0; i < v.n(); ++i)
  //{ //for (int j = v.t()-1; j <v.t(); ++j)
      //o << v.getY(i) << " ";
    //o << "\n";
 // }


  
  //o << " Vecteur X :\n";
  //for (int i = 0; i < v.n(); ++i)
  //{ //for (int j = v.t()-1; j < v.t(); ++j)
     // o << v.getX(i) << " ";
   // o << "\n";
  //}

  //o << " Vecteur T :\n";
  //for (int i = 0; i < v.n(); ++i)
  //{ for (int j = v.t(); j < v.t()+1; ++j)
     // o << v.getT(i)[j] << " ";
   // o << "\n";
//}

  return o;
}
