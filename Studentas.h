#ifndef STRUKTUROS_H
#define STRUKTUROS_H

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
    Studentas() : egzaminas_(0), galutinisVid_(0), galutinisMed_(0) {}

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
};
#endif