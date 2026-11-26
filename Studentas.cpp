#include "Studentas.h"
#include <cmath>
#include <algorithm>
#include <iomanip>

Studentas::Studentas(string v, string p, vector<double> nd, double egz):
    vardas_(move(v)), 
    pavarde_(move(p)),
    namuDarbai_(move(nd)), 
    egzaminas_(egz),
    galutinisVid_(Vidurkis(*this)), 
    galutinisMed_(Mediana(*this)) {}
    
Studentas::Studentas(const Studentas& o):
    vardas_(o.vardas_), 
    pavarde_(o.pavarde_),
    namuDarbai_(o.namuDarbai_),
    egzaminas_(o.egzaminas_),
    galutinisVid_(o.galutinisVid_),
    galutinisMed_(o.galutinisMed_) {}

Studentas::Studentas(Studentas&& o) noexcept: 
    vardas_(move(o.vardas_)), 
    pavarde_(move(o.pavarde_)),
    namuDarbai_(move(o.namuDarbai_)), 
    egzaminas_(o.egzaminas_),
    galutinisVid_(o.galutinisVid_), 
    galutinisMed_(o.galutinisMed_) {}

Studentas& Studentas::operator=(const Studentas& o) {
    if (this != &o) {
        vardas_ = o.vardas_;
        pavarde_ = o.pavarde_;
        namuDarbai_ = o.namuDarbai_;
        egzaminas_ = o.egzaminas_;
        galutinisVid_ = o.galutinisVid_;
        galutinisMed_ = o.galutinisMed_;
    }
    return *this;
}

Studentas& Studentas::operator=(Studentas&& o) noexcept {
    if (this != &o) {
        vardas_ = move(o.vardas_);
        pavarde_ = move(o.pavarde_);
        namuDarbai_ = move(o.namuDarbai_);
        egzaminas_ = o.egzaminas_;
        galutinisVid_ = o.galutinisVid_;
        galutinisMed_ = o.galutinisMed_;
    }
    return *this;
}

Studentas::~Studentas(){ 
    vardas_.clear();
    pavarde_.clear();
    namuDarbai_.clear();
    egzaminas_ = 0;
    galutinisVid_ = 0;
    galutinisMed_ = 0;

}

void Studentas::perskaiciuoti() {
    galutinisVid_ = Vidurkis(*this);
    galutinisMed_ = Mediana(*this);
}

const string& Studentas::vardas() const { return vardas_; }
const string& Studentas::pavarde() const { return pavarde_; }
const vector<double>& Studentas::namuDarbai() const { return namuDarbai_; }
double Studentas::egzaminas() const { return egzaminas_; }
double Studentas::galutinisVid() const { return galutinisVid_; }
double Studentas::galutinisMed() const { return galutinisMed_; }

void Studentas::setVardas(const string& v) { vardas_ = v; }
void Studentas::setPavarde(const string& p) { pavarde_ = p; }
void Studentas::setNamuDarbai(vector<double> nd) { namuDarbai_ = move(nd); perskaiciuoti(); }
void Studentas::pridetiND(double nd) { namuDarbai_.push_back(nd); perskaiciuoti(); }
void Studentas::setEgzaminas(double e) { egzaminas_ = e; perskaiciuoti(); }
void Studentas::setGalutinisVid(double g) { galutinisVid_ = g; }
void Studentas::setGalutinisMed(double g) { galutinisMed_ = g; }

istream& operator>>(istream& in, Studentas& a) {
    in >> a.vardas_ >> a.pavarde_;
    return in;
}
ostream& operator<<(ostream& out, const Studentas& a) {
    out << left 
        << setw(15) << a.vardas_ 
        << setw(20) << a.pavarde_ 
        << fixed << setprecision(2)
        << setw(20) << a.galutinisVid_ 
        << setw(20) << a.galutinisMed_ ;
    return out;
}

double Vidurkis(const Studentas& a) {
    double suma = 0;
    for (size_t i = 0; i < a.namuDarbai_.size(); i++) {
        suma += a.namuDarbai_[i];
    }
    double ndVidurkis;
    if (a.namuDarbai_.empty()) { ndVidurkis = 0;} 
    else { ndVidurkis = suma / a.namuDarbai_.size();}

    double galutinis = (ndVidurkis * 0.4) + (a.egzaminas_ * 0.6);
    return  round(galutinis * 100.0) / 100.0;
}

 double Mediana(const Studentas& a) {
    vector <double> nd = a.namuDarbai_;
    sort(nd.begin(), nd.end());
    double mediana;
    int n = nd.size();
    if (n == 0) {
        mediana = 0;
    } else if (n % 2 == 0) {
        mediana = (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
    } else {
        mediana = nd[n / 2];
    }
    double galutinis = (mediana * 0.4) + (a.egzaminas_ * 0.6);
    return round(galutinis * 100.0) / 100.0;
}