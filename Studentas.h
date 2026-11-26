#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
using namespace std;

class Zmogus{
protected:
    string vardas_;
    string pavarde_;
public:
    Zmogus(string v = "", string p = "");
    Zmogus(const Zmogus& o);
    Zmogus(Zmogus&& o) noexcept;
    Zmogus& operator=(const Zmogus& o);
    Zmogus& operator=(Zmogus&& o) noexcept;

    virtual ~Zmogus();

    const string& vardas() const;
    const string& pavarde() const;
    void setVardas(const string& v);
    void setPavarde(const string& p);

    virtual void spausdinti() const = 0;
};

class Studentas {
private:
    string vardas_;
    string pavarde_;
    vector<double> namuDarbai_;
    double egzaminas_;
    double galutinisVid_;
    double galutinisMed_;

    void perskaiciuoti(); 
    
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
    friend double Vidurkis(const Studentas& a);
    friend double Mediana(const Studentas& a);
};
#endif