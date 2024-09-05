#ifndef LIRE_HPP
#define LIRE_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

class DOCU {
public:
// constructeur pour lire la variable es sa valeur 
    DOCU(std::string L) : lire(L) {
        std::ifstream ifile(lire);
        if (ifile) {
            while (ifile >> VAr >> VAl) {
                //std::cout << VAr << "=" << VAl << std::endl;
                VARIABLE[VAr] = VAl;
            }
        }
        // chaque varible prend sa valeur 
        Lx = VARIABLE["Lx"];
        Ly = VARIABLE["Ly"];
        Lz = VARIABLE["Lz"];
        hc = VARIABLE["hc"];
        k = VARIABLE["k"];
        M = VARIABLE["M"];
        Phi = VARIABLE["Phi"];
        Te = VARIABLE["Te"];
    }
   // chaque fonctoin get return un variable
    double getLX() const { return Lx; }
    double getLY() const { return Ly; }
    double getLZ() const { return Lz; }
    double gethc() const { return hc; }
    double getk() const { return k; }
    double getPhi() const { return Phi; }
    double getTe() const { return Te; }
    int getM() const { return M; }

private:
    std::string lire;
    std::string VAr;
    int M;
    double VAl, Lx, Ly,Lz,hc,k,Phi,Te;
     //cette fonction pour lire la vriable et sa valeur
    std::unordered_map<std::string, double> VARIABLE;
};
#endif
