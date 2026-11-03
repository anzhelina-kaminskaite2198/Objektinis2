#ifndef STRUKTUROS_H
#define STRUKTUROS_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
using namespace std;

class Studentas {
private: 
    string vardas;
    string pavarde;
    vector<double> namuDarbai;
    double egzaminas;
    double galutinisVid;
    double galutinisMed;
public:
    Studentas(string V="", string P="", vector<int>ND={}, int E=0,int GV=0, int GM=0): 
    vardas{V}, pavarde{P}, namuDarbai{ND}, egzaminas{E}, galutinisVid{GV}, galutinisMed{GM}  {cout << "Studentas sukurtas";};
    ~Studentas(){ // destruktorius butent toks, nes jis viks net jei mes pakeisime kinmatuosius.
        vardas.clear();
        pavarde.clear();
        namuDarbai.clear();
        egzaminas = 0;
        galutinisVid = 0;
        galutinisMed = 0;
    }
    string vardas() const {return vardas;}
    string pavarde() const {return pavarde;}

    friend istream& operator >> (istream& in, Studentas& A) {
        in >> A.vardas >> A.pavarde;
        return in;
    }
};

struct NeteisingiDuomenys {
    string vardas;
    string pavarde;
};

struct Laikmatis {
    chrono::high_resolution_clock::time_point pradzia = chrono::high_resolution_clock::now();
    double PraejesLaikas() const {
        return chrono::duration<double>(chrono::high_resolution_clock::now() - pradzia).count();
    }
};

#endif