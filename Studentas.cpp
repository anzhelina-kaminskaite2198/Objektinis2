#include "Studentas.h"

Studentas::Studentas(string v, string p, vector<double> nd, double egz):
    vardas_(move(v)), 
    pavarde_(move(p)),
    namuDarbai_(move(nd)), 
    egzaminas_(egz),
    galutinisVid_(0), 
    galutinisMed_(0) {}
    
Studentas::Studentas(const Studentas& o)
    : vardas_(o.vardas_), pavarde_(o.pavarde_), namuDarbai_(o.namuDarbai_),
      egzaminas_(o.egzaminas_), galutinisVid_(o.galutinisVid_),
      galutinisMed_(o.galutinisMed_) {}

Studentas::Studentas(Studentas&& o) noexcept
    : vardas_(move(o.vardas_)), pavarde_(move(o.pavarde_)),
      namuDarbai_(move(o.namuDarbai_)), egzaminas_(o.egzaminas_),
      galutinisVid_(o.galutinisVid_), galutinisMed_(o.galutinisMed_) {}

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

const string& Studentas::vardas() const { return vardas_; }
const string& Studentas::pavarde() const { return pavarde_; }
const vector<double>& Studentas::namuDarbai() const { return namuDarbai_; }
double Studentas::egzaminas() const { return egzaminas_; }
double Studentas::galutinisVid() const { return galutinisVid_; }
double Studentas::galutinisMed() const { return galutinisMed_; }

void Studentas::setVardas(const string& v) { vardas_ = v; }
void Studentas::setPavarde(const string& p) { pavarde_ = p; }
void Studentas::setNamuDarbai(vector<double> nd) { namuDarbai_ = move(nd); }
void Studentas::pridetiND(double nd) { namuDarbai_.push_back(nd); }
void Studentas::setEgzaminas(double e) { egzaminas_ = e; }
void Studentas::setGalutinisVid(double g) { galutinisVid_ = g; }
void Studentas::setGalutinisMed(double g) { galutinisMed_ = g; }

istream& operator>>(istream& in, Studentas& a) {
    in >> a.vardas_ >> a.pavarde_;
    return in;
}
ostream& operator<<(ostream& out, const Studentas& a) {
    out << a.vardas_ << " " << a.pavarde_;
    return out;
}
