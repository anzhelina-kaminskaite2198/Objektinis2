#ifndef STRUKTUROS_H
#define STRUKTUROS_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include "Studentas.h"
using namespace std;



class NeteisingiDuomenys {
private:
    string vardas_;
    string pavarde_;

public:
    NeteisingiDuomenys(string v = "", string p = ""): vardas_(v), pavarde_(p) {}

    const string& vardas() const { return vardas_; }
    const string& pavarde() const { return pavarde_; }

    ~NeteisingiDuomenys() {
        vardas_.clear();
        pavarde_.clear();
    };

    void setVardas(const string& v) { vardas_ = v; }
    void setPavarde(const string& p) { pavarde_ = p; }
};

struct Laikmatis {
    chrono::high_resolution_clock::time_point pradzia = chrono::high_resolution_clock::now();
    double PraejesLaikas() const {
        return chrono::duration<double>(chrono::high_resolution_clock::now() - pradzia).count();
    }
};

#endif