#ifndef STUDENTUFUNKCIJOS_H
#define STUDENTUFUNKCIJOS_H

#include "Strukturos.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <limits>
#include <stdexcept>
#include <list>
#include <chrono>

using namespace std;

inline static random_device rd;
inline static mt19937 gen(rd());
inline static uniform_real_distribution<double>dist(0.0, 10.0);

inline vector<NeteisingiDuomenys> neteisingi;

inline bool IvedimoKlaidos (int kintamasis, int pasirinkimuSk) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(100000000, '\n');
        cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
        return false;
    }
    else if (kintamasis >= 1 && kintamasis <= pasirinkimuSk) {
        return true;
    } else {
        cout << "\033[31mKlaida: netinkamas pasirinkimas.\033[0m\n" << endl;
        return false;
    }
}

inline int PasirinktiRusiavimoParametra() {
    int pasirinkimas;
    while (true) {
        cout << "\nPagal ka rusiuoti studentus?\n"
             << "1  Pagal varda\n"
             << "2  Pagal pavarde\n"
             << "3  Pagal galutini bala\n";
        cin >> pasirinkimas;
        if (IvedimoKlaidos(pasirinkimas, 3)) { break; }
    }
    return pasirinkimas;
}

enum Konteineris { NEPASIRINKTA = 0, VEKTORIUS = 1, LISTAS = 2 };

inline int PasirinktiKonteineri() {
    int pasirinkimas;
    while (true) {
        cout << "\nKur saugoti studentus?\n"
             << "1 std::vector\n"
             << "2 std::list\n"
             << "Pasirinkite: ";
        cin >> pasirinkimas;
        if (IvedimoKlaidos(pasirinkimas, 2)) { break; }
    }
    return pasirinkimas;
}

inline void NustatytiKonteineri(int& konteineris, bool tuscia) {
    if (tuscia || konteineris == NEPASIRINKTA) {
        konteineris = PasirinktiKonteineri();
    } else {
        cout << "\nNaudojamas konteineris: "
             << (konteineris == VEKTORIUS ? "std::vector" : "std::list") << endl;
    }
}

inline double Vidurkis(const Studentas& studentas) {
    const vector<double>& nd = studentas.namuDarbai();
    double suma = 0;
    for (size_t i = 0; i < nd.size(); i++) {
        suma += nd[i];
    }
    double ndVidurkis;
    if (nd.empty()) { ndVidurkis = 0;} 
    else { ndVidurkis = suma / nd.size();}

    double galutinis = (ndVidurkis * 0.4) + (studentas.egzaminas() * 0.6);
    return  round(galutinis * 100.0) / 100.0;
}

inline double Mediana(const Studentas& studentas) {
    vector<double> ndPazymiai = studentas.namuDarbai();
    sort(ndPazymiai.begin(), ndPazymiai.end());
    double mediana;
    int n = ndPazymiai.size();
    if (n == 0) {
        mediana = 0;
    } else if (n % 2 == 0) {
        mediana = (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
    } else {
        mediana = ndPazymiai[n / 2];
    }
    double galutinis = (mediana * 0.4) + (studentas.egzaminas() * 0.6);
    return round(galutinis * 100.0) / 100.0;
}

template <typename Container>
int IvestiStudenta(Container& studentai) {

    Studentas studentas;

    cout << "Iveskite studento varda ir pavarde\n" << "pvz: Vardenis Pavardenis\n";
    cin >> studentas;
    cin.ignore();

    int pasirinkimas_nd;
    while (true) {
        cout << "1  Ivesti namu darbu pazymius\n" 
             << "2  Sugeneruoti namu daru pazymius\n";
        cin >> pasirinkimas_nd;

        if (IvedimoKlaidos(pasirinkimas_nd, 2)) { break; }
        
    }
    cin.ignore();

    switch (pasirinkimas_nd) {
        case 1: {

            string ivertinimas;
            cout << "\nKad baigti namu darbu ivedima paskauskite ENTER 2 kartus\n ";

            while (true) {

                cout  << "Iveskite namu darbu pazymi:";
                getline(cin, ivertinimas);

                if ( ivertinimas.empty() ) {
                    break;
                }

                try {
                    double pazymys = stod(ivertinimas);

                    if (pazymys < 0 || pazymys > 10) {
                    cout << "\033[31mKlaida: ivestas pazymys turi buti nuo 0 iki 10, bandykite dar karta.\033[0m" << endl;
                    continue;
                    }
                    studentas.pridetiND(pazymys);

                } catch (const invalid_argument& e) {
                    cout << "\033[31mKlaida: ivestas ne skaicius, bandykite dar karta.\033[0m" << endl;
                    }
            }
            break;
        }
        case 2: {
            int ndSkaicius;
            while (true){
                cout << "Iveskite kiek namu darbu pazymiu norite sugeneruoti:";
                cin >> ndSkaicius;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(100000000, '\n');
                    cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
                    continue;
                }else if (ndSkaicius < 0) {
                    cout << "\033[31mKlaida: skaicius negali buti neigiamas.\033[0m" << endl;
                    continue;
                } else {
                    break;
                }
            }
            
            for (int i=0; i < ndSkaicius; i++) {
                double ndPazymys = dist(gen);
                studentas.pridetiND(ndPazymys);
            }
            cout << "Sugeneruoti namu darbu pazymiai: [";

            for (int i = 0; i < studentas.namuDarbai().size(); i++) {
                cout << fixed << setprecision(2) << studentas.namuDarbai()[i];
                if (i < studentas.namuDarbai().size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
            break;
        }
    } 


    int pasirinkimas_egz;
    while (true) {
        cout << "1  Ivesti egzamino pazymi\n" 
             << "2  Sugeneruoti egzamino pazymi\n";
        cin >> pasirinkimas_egz;

        if (IvedimoKlaidos( pasirinkimas_egz, 2)) { break; }
    }
    cin.ignore(); 

    switch (pasirinkimas_egz) {
        case 1: {
            string exam;
    
            while (true) {
                cout << "Egzamino pazymys: ";
                getline(cin, exam);

                if (exam.empty()) {
                    exam = "0";
                }

                try {
                    double egzoPazymys = stod(exam);

                    if (egzoPazymys < 0 || egzoPazymys > 10) {
                        cout << "\033[31mKlaida: pazymys turi buti nuo 0 iki 10.\033[0m" << endl;
                        continue;
                    }

                    studentas.setEgzaminas(egzoPazymys);
                    break;
                } catch (const invalid_argument& e) {
                    cout << "\033[31mKlaida: ivestas ne skaicius. Bandykite dar karta.\033[0m" << endl;
                    }
            }
            break;
        }
        case 2: {
            double egzPazymys = dist(gen);
            studentas.setEgzaminas(egzPazymys);
            cout << "Sugeneruotas egzamino pazymys: " << fixed << setprecision(2) << egzPazymys << endl;
            break;
        }
    }
    
    studentas.setGalutinisVid(Vidurkis(studentas));
    studentas.setGalutinisMed(Mediana(studentas));
    studentai.push_back(studentas);
 
    cout << "\n \033[32m Studentas sekmingai ivestas! \033[0m\n\n"
         << left
         << setw(15) << "Vardas"
         << setw(20) << "Pavarde"
         << setw(20) << "Galutinis (vid.)"
         << setw(20) << "Galutinis (med.)" 
         << setw(20) << "Adresas" << '\n'
         << "-----------------------------------------------------------------------" << '\n'; 

    cout << left 
         << setw(15) << studentas.vardas()
         << setw(20) << studentas.pavarde()
         << setw(20) << studentas.galutinisVid()
         << setw(20) << studentas.galutinisMed()
         << setw(20) << static_cast<const void*>(&studentai.back()) << '\n';
    return 0;
}

template <typename Container>
double IrasytiStudentus(const Container& vektorius, const string& failoVardas) {
    Laikmatis t;

    ofstream failas (failoVardas);    
    failas  << left
            << setw(15) << "Vardas"
            << setw(20) << "Pavarde"
            << setw(20) << "Galutinis (vid.)"
            << setw(20) << "Galutinis (med.)" << '\n'
            << "-----------------------------------------------------------------------" << '\n';

    failas << fixed << setprecision(2);
    for (const auto& studentas : vektorius) {
        failas  << left 
                << setw(15) << studentas.vardas()
                << setw(20) << studentas.pavarde() 
                << setw(20) << studentas.galutinisVid()
                << setw(20) << studentas.galutinisMed() << '\n';
    }
    failas.close();
    return t.PraejesLaikas();
}

template <typename Container>
double SkaitytiIsFailo(const string& failoVardas, Container& studentai) {
   
    ifstream failas (failoVardas);

    if (!failas) {
        cout << "\033[31mNepavyko atidaryti failo.\033[0m" << endl;
        return -1;
    }

    neteisingi.clear();

    Laikmatis t;

    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        string vardas;
        string pavarde;
        ss >> vardas >> pavarde;

        vector<double> nd;
        string strPazymys;
        bool neteisingasPazymys = false;

        while (ss >> strPazymys) {
            try
            {
                double pazymys = stod(strPazymys);

                if ( pazymys >= 0 && pazymys <= 10) {
                    nd.push_back(pazymys);
                } else {
                    neteisingasPazymys = true; 
                    break;
                }
            }
            catch(const invalid_argument& e){
                neteisingasPazymys = true;
                break;
            }
        }
        if (neteisingasPazymys||nd.empty()) {
            NeteisingiDuomenys blogasStudentas;
            blogasStudentas.setVardas(vardas);
            blogasStudentas.setPavarde(pavarde);
            neteisingi.push_back(blogasStudentas);
            continue;
        }
        double egz = nd.back();
        nd.pop_back();

        Studentas studentas(move(vardas), move(pavarde), move(nd), egz);
        studentas.setGalutinisVid(Vidurkis(studentas));
        studentas.setGalutinisMed(Mediana(studentas));
        studentai.push_back(move(studentas));

    }
    
    failas.close();
    return t.PraejesLaikas();
}



enum Strategija {S1, S2, Mano, Optimizuota};
template <typename Container>
double DalytiStudentus_S1(Container& studentai, Container& vargseliai, Container& kietuoliai) {
    Laikmatis t;
 
    for (const auto& studentas : studentai) {
        if (studentas.galutinisVid() < 5.0) {
            vargseliai.push_back(studentas);
        } else {
            kietuoliai.push_back(studentas);
        }
    }

    return t.PraejesLaikas();
}

template <typename Container>
double DalytiStudentus_S2(Container& studentai, Container& vargseliai, Container& kietuoliai) {
    Laikmatis t;

    if constexpr (is_same_v<Container, vector<Studentas>>) {

        RikiotiStudentus (studentai, [](const Studentas& a, const Studentas& b) { return a.galutinisVid() > b.galutinisVid(); });
        while (!studentai.empty() && studentai.back().galutinisVid() < 5.0) {
            vargseliai.push_back(std::move(studentai.back()));
            studentai.pop_back();
        }
        studentai.shrink_to_fit();
    } else {

        for (auto it = studentai.begin(); it != studentai.end(); ) { 
        if (it->galutinisVid() < 5.0) {
            vargseliai.push_back(move(*it));
            it = studentai.erase(it);
            } else {
                ++it;
            }
        }
    }
    kietuoliai = move(studentai); 
    return t.PraejesLaikas();
}

template <typename Container>
double DalytiStudentus_Mano(Container& studentai, Container& vargseliai, Container& kietuoliai) {
    Laikmatis t;
 
    for (auto& studentas : studentai) {
        if (studentas.galutinisVid() < 5.0) {
            vargseliai.push_back(move(studentas));
        } else {
            kietuoliai.push_back(move(studentas));
        }
    }
    studentai.clear();
    if constexpr (is_same_v<Container, vector<Studentas>>){
        studentai.shrink_to_fit();
    }

    return t.PraejesLaikas();
}

template <typename Container>
double DalytiStudentus_Optimizuota( Container& studentai, Container& vargseliai, Container& kietuoliai) {
    Laikmatis t;

    if constexpr (is_same_v<Container, vector<Studentas>>) {
        auto yraVargselis = [](const Studentas& s) { return s.galutinisVid() < 5.0; };

        copy_if(make_move_iterator(studentai.begin()), make_move_iterator(studentai.end()),
                back_inserter(vargseliai), yraVargselis);
        studentai.erase(remove_if(studentai.begin(), studentai.end(), yraVargselis), studentai.end());
        kietuoliai = move(studentai);
    } else {
        for (auto it = studentai.begin(); it != studentai.end();) {
            auto kitas = next(it);
            if (it->galutinisVid() < 5.0)
                vargseliai.splice(vargseliai.end(), studentai, it);
            it = kitas;
        }
        kietuoliai = move(studentai);
    }

    return t.PraejesLaikas();
}

template <typename Container>
double Dalyti(Strategija strategija, Container& studentai, Container& vargseliai, Container& kietuoliai) {
    switch (strategija) {
        case S1:
            return DalytiStudentus_S1(studentai, vargseliai, kietuoliai);
        case S2: 
            return DalytiStudentus_S2(studentai, vargseliai, kietuoliai);
        case Mano:
            return DalytiStudentus_Mano(studentai, vargseliai, kietuoliai);
        case Optimizuota:
            return DalytiStudentus_Optimizuota(studentai, vargseliai, kietuoliai);;
    }
    return 0.0;
}



template <typename Container, typename Lambda>
void RikiotiStudentus(Container& v, Lambda kriterijus){
    if constexpr(is_same_v<Container, vector<Studentas>>){
        sort(v.begin(), v.end(), kriterijus);
    } else if constexpr (is_same_v<Container, list<Studentas>>){
        v.sort(kriterijus);
    }
}

template <typename Container>
double RusiuotiStudentus(Container& v, int pagal) {
    Laikmatis t;
 
    switch (pagal) {
        case 1:
            RikiotiStudentus (v, [](const Studentas& a, const Studentas& b) { return a.vardas() < b.vardas(); });
            break;
        case 2:
            RikiotiStudentus (v, [](const Studentas& a, const Studentas& b) { return a.pavarde() < b.pavarde(); });
            break;
        case 3:
            RikiotiStudentus (v, [](const Studentas& a, const Studentas& b) { return a.galutinisVid() < b.galutinisVid(); });
            break;
    }
 
    return t.PraejesLaikas();
}



template <typename Container>
void DalintiRusiuotiIrasyti(Container& studentai, int parametras) {
    Container vargseliai;
    Container kietuoliai;

    double DalyjimoLaikas = Dalyti(Optimizuota, studentai, vargseliai, kietuoliai);
    double RusiavimoLaikas = RusiuotiStudentus(vargseliai, parametras)
                           + RusiuotiStudentus(kietuoliai, parametras);
    double VargIrasymoLaikas = IrasytiStudentus(vargseliai, "vargseliai.txt");
    double KietIrasymoLaikas = IrasytiStudentus(kietuoliai, "kietuoliai.txt");

    cout << fixed << setprecision(6)
         << "\nDalijimo i dvi grupes laikas: " << DalyjimoLaikas << " s\n"
         << "Rusiavimo laikas: " << RusiavimoLaikas << " s\n"
         << "Vargseliu irasymo i faila laikas: " << VargIrasymoLaikas << " s\n"
         << "Kietuoliu irasymo i faila laikas: " << KietIrasymoLaikas << " s\n"
         << "Rezultatai irasyti i vargseliai.txt ir kietuoliai.txt\n";
}

template <typename Container>
void TestuotiKonteinerius(int rusiavimoPasirinkimas, string pavadinimas) {
    const int dydziai[] = {1000, 10000, 100000, 1000000, 10000000};
    const Strategija strategijos[] = {S1, S2, Mano, Optimizuota};
    const string pavadinimai[]     = {"S1", "S2", "Mano", "Optimizuota"};
    const int kartai = 3;

    cout << fixed << setprecision(6);
    cout << "----------" << pavadinimas << "-----------";

    for (Strategija s : strategijos) {
        const string& sp = pavadinimai[s];

        for (int n : dydziai) {

            string failas = "studentai" + to_string(n) + ".txt";
            
            vector<double> Nuskaitymas;
            vector<double> Dalyjimas;
            vector<double> Rusiavimas;
            vector<double> VargseliuIrasymas;
            vector<double> KietuoliuIrasymas;
            vector<double> Bendras;

            for (int k = 0; k < kartai; k++) {
                Container studentai;
                Container vargseliai;
                Container kietuoliai;

                double NuskaitymoLaikas = SkaitytiIsFailo(failas, studentai);
                if (NuskaitymoLaikas < 0) { break; }
                double DalyjimoLaikas = Dalyti(s, studentai, vargseliai, kietuoliai);
                double RusiavimoLaikas = RusiuotiStudentus(vargseliai, rusiavimoPasirinkimas)
                    + RusiuotiStudentus(kietuoliai, rusiavimoPasirinkimas);
                double VargIrasymoLaikas;
                double KietIrasymoLaikas;

                if (n == 1000) {
                    VargIrasymoLaikas = IrasytiStudentus(vargseliai, "vargseliai" + to_string(n) + pavadinimas + "_" + sp + ".txt");
                    KietIrasymoLaikas = IrasytiStudentus(kietuoliai, "kietuoliai" + to_string(n) + pavadinimas + "_" + sp + ".txt");
                } else {
                    VargIrasymoLaikas = IrasytiStudentus(vargseliai, "vargseliai" + to_string(n) + ".txt");
                    KietIrasymoLaikas = IrasytiStudentus(kietuoliai, "kietuoliai" + to_string(n) + ".txt");
                }
                
            
                double BendrasLaikas = NuskaitymoLaikas + DalyjimoLaikas + RusiavimoLaikas + VargIrasymoLaikas + KietIrasymoLaikas;

                Nuskaitymas.push_back(NuskaitymoLaikas);
                Dalyjimas.push_back(DalyjimoLaikas);
                Rusiavimas.push_back(RusiavimoLaikas);
                VargseliuIrasymas.push_back(VargIrasymoLaikas);
                KietuoliuIrasymas.push_back(KietIrasymoLaikas);
                Bendras.push_back(BendrasLaikas);
            }
            
            if (Bendras.empty()) {
                cout << "\033[31mFailas " << failas << " nerastas.\033[0m\n\n";
                continue;
            }

            auto VidurkisLaiku = [](const vector<double>& laikai) {
                double suma = 0;
                for (double laikas : laikai) {
                    suma += laikas;
                }
                return suma / laikai.size();
            };
            
            cout << "\n      "<< n << " STUDENTU, strategija " << sp << "\n"
                << "-------------------------------------------------" << endl;

            cout << "Nuskaitymo laiku vidurkis: " << VidurkisLaiku(Nuskaitymas)<< " s\n"
                << "Dalijimo laiku vidurkis: " << VidurkisLaiku(Dalyjimas) << " s\n"
                << "Rusiuavimo laiku vidurkis: " << VidurkisLaiku(Rusiavimas) << " s\n"
                << "Vargsheliu irasymo laiku vidurkis: " << VidurkisLaiku(VargseliuIrasymas) << " s\n"
                << "Kietuoliu irasymo laiku vidurkis: " << VidurkisLaiku(KietuoliuIrasymas) << " s\n\n"
                << "Bendras tetso laikas: " << VidurkisLaiku(Bendras) << " s\n\n";

            Nuskaitymas.clear();
            Dalyjimas.clear();
            Rusiavimas.clear();
            VargseliuIrasymas.clear();
            KietuoliuIrasymas.clear();
            Bendras.clear();
        }
    }
}

 inline void PaleistiTestus(int rusiavimoPasirinkimas){
    TestuotiKonteinerius<vector<Studentas>>(rusiavimoPasirinkimas, "VEKTORIUS");
    TestuotiKonteinerius<list<Studentas>>(rusiavimoPasirinkimas, "LIST");

}

double SukurtiTestavimoFailus(int studentuSk, int ndSk);
void SukurtiVisusTestavimoFailus();
 
#endif