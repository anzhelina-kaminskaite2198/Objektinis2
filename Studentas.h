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

    Studentas(string v = "", string p = "", vector<double> nd ={}, double egz = 0):
        vardas_(move(v)), pavarde_(move(p)),
        namuDarbai_(move(nd)), egzaminas_(egz),
        galutinisVid_(0), galutinisMed_(0) {}

    ~Studentas(){ 
        vardas_.clear();
        pavarde_.clear();
        namuDarbai_.clear();
        egzaminas_ = 0;
        galutinisVid_ = 0;
        galutinisMed_ = 0;

    }

    const string& vardas() const { return vardas_; }
    const string& pavarde() const { return pavarde_; }
    const vector<double>& namuDarbai() const { return namuDarbai_; }
    double egzaminas() const { return egzaminas_; }
    double galutinisVid() const { return galutinisVid_; }
    double galutinisMed() const { return galutinisMed_; }

    void setVardas(const string& v) { vardas_ = v; }
    void setPavarde(const string& p) { pavarde_ = p; }
    void setNamuDarbai(vector<double> nd) { namuDarbai_ = move(nd); }
    void pridetiND(double nd) { namuDarbai_.push_back(nd); }
    void setEgzaminas(double e) { egzaminas_ = e; }
    void setGalutinisVid(double g) { galutinisVid_ = g; }
    void setGalutinisMed(double g) { galutinisMed_ = g; }

    friend istream& operator>>(istream& in, Studentas& a) {
        in >> a.vardas_ >> a.pavarde_;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Studentas& a) {
        out << a.vardas_ << " " << a.pavarde_;
        return out;
    }
};
#endif