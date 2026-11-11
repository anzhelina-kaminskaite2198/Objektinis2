#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<double> namuDarbai_;
    double egzaminas_;
    double galutinisVid_;
    double galutinisMed_;

public:

    Studentas(std::string v = "", std::string p = "", std::vector<double> nd ={}, double egz = 0)
        : vardas_(std::move(v)), pavarde_(std::move(p)),
          namuDarbai_(std::move(nd)), egzaminas_(egz),
          galutinisVid_(0), galutinisMed_(0) {}

    Studentas(const Studentas& o)
        : vardas_(o.vardas_), pavarde_(o.pavarde_), namuDarbai_(o.namuDarbai_),
          egzaminas_(o.egzaminas_), galutinisVid_(o.galutinisVid_),
          galutinisMed_(o.galutinisMed_) {}

    Studentas(Studentas&& o) noexcept
        : vardas_(std::move(o.vardas_)), pavarde_(std::move(o.pavarde_)),
          namuDarbai_(std::move(o.namuDarbai_)), egzaminas_(o.egzaminas_),
          galutinisVid_(o.galutinisVid_), galutinisMed_(o.galutinisMed_) {}

    Studentas& operator=(const Studentas& o) {
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

    Studentas& operator=(Studentas&& o) noexcept {
        if (this != &o) {
            vardas_ = std::move(o.vardas_);
            pavarde_ = std::move(o.pavarde_);
            namuDarbai_ = std::move(o.namuDarbai_);
            egzaminas_ = o.egzaminas_;
            galutinisVid_ = o.galutinisVid_;
            galutinisMed_ = o.galutinisMed_;
        }
        return *this;
    }

    ~Studentas() {}

    const std::string& vardas() const { return vardas_; }
    const std::string& pavarde() const { return pavarde_; }
    const std::vector<double>& namuDarbai() const { return namuDarbai_; }
    double egzaminas() const { return egzaminas_; }
    double galutinisVid() const { return galutinisVid_; }
    double galutinisMed() const { return galutinisMed_; }

    void setVardas(const std::string& v) { vardas_ = v; }
    void setPavarde(const std::string& p) { pavarde_ = p; }
    void setNamuDarbai(std::vector<double> nd) { namuDarbai_ = std::move(nd); }
    void pridetiND(double nd) { namuDarbai_.push_back(nd); }
    void setEgzaminas(double e) { egzaminas_ = e; }
    void setGalutinisVid(double g) { galutinisVid_ = g; }
    void setGalutinisMed(double g) { galutinisMed_ = g; }

    friend std::istream& operator>>(std::istream& in, Studentas& a) {
        in >> a.vardas_ >> a.pavarde_;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Studentas& a) {
        out << a.vardas_ << " " << a.pavarde_;
        return out;
    }
};
#endif