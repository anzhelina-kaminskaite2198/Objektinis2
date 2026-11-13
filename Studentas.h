#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
using namespace std;

class Studentas {
private:
    string vardas_;
    string pavarde_;
    vector<double> namuDarbai_;
    double egzaminas_;
    double galutinisVid_;
    double galutinisMed_;

public:

    Studentas(string v = "", string p = "", vector<double> nd ={}, double egz = 0);
    Studentas(const Studentas& o);
    Studentas(Studentas&& o) noexcept;
    Studentas& operator=(const Studentas& o);
    Studentas& operator=(Studentas&& o) noexcept;
    
    ~Studentas();

    const string& vardas() const;
    const string& pavarde() const;
    const vector<double>& namuDarbai() const;
    double egzaminas() const;
    double galutinisVid() const;
    double galutinisMed() const;

    void setVardas(const string& v);
    void setPavarde(const string& p);
    void setNamuDarbai(vector<double> nd);
    void pridetiND(double nd);
    void setEgzaminas(double e);
    void setGalutinisVid(double g);
    void setGalutinisMed(double g);

    friend istream& operator>>(istream& in, Studentas& a);
    friend ostream& operator<<(ostream& out, const Studentas& a);
};
#endif