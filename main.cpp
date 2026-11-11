#include "Strukturos.h"
#include "StudentuFunkcijos.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>
#include <list>
#include <vector>
using namespace std;


int main() {
    vector<Studentas> studentai;
    list<Studentas> studentaiList;

    int konteineris = NEPASIRINKTA;
    int pasirinkimas;
    
    while (true) {
        cout << "\n              MENIU\n"
             << "-----------------------------------\n"
             << "1  Ivesti nauja studenta\n"
             << "2  Nuskaityti duomenis is failo\n"
             << "3  Padalinti, surusiuoti ir irasyti studentus i failus\n"
             << "4  Sukurti testavimo failus (5 failai)\n"
             << "5  Paleisti testavimus (5 failai)\n"
             << "6  Iseiti\n\n"
             << "Pasirinkite veiksma: ";

        cin >> pasirinkimas;
        
        if (!IvedimoKlaidos(pasirinkimas, 6)) { continue; }
        
        switch (pasirinkimas) {
        
            case 1: {
                NustatytiKonteineri(konteineris, studentai.empty() && studentaiList.empty());
                if (konteineris == VEKTORIUS) {
                    IvestiStudenta(studentai);
                } else {
                    IvestiStudenta(studentaiList);
                }
                continue;
            }
            case 2: {
                NustatytiKonteineri(konteineris, studentai.empty() && studentaiList.empty());

                string failas;
                cout << "Is kokio failo noretumet nuskaityti studentu duomenis?\n"
                     << "pvz: kursiokai.txt\n";
                cin >> failas;
 
                double FailuNuskaitymoLaikas;
                if (konteineris == VEKTORIUS) {
                    FailuNuskaitymoLaikas = SkaitytiIsFailo(failas, studentai);
                } else {
                    FailuNuskaitymoLaikas = SkaitytiIsFailo(failas, studentaiList);
                }

                if (FailuNuskaitymoLaikas >= 0) {
                    cout << "\033[32mFailas sekmingai nuskaitytas!\033[0m\n"
                         << "Nuskaitymo laikas: " << fixed << setprecision(6) << FailuNuskaitymoLaikas << " s\n";
                }
                if (!neteisingi.empty()) {
                    cout << "\n\nDel duomenu ivedimo klaidos i sarasa nebuvo ivesti sie studentai:\n";
                    for (const NeteisingiDuomenys& studentas : neteisingi) {
                        cout << studentas.vardas() << " " << studentas.pavarde() << endl;
                    }
                }
                continue;
            }
            case 3: {
                if (studentai.empty() && studentaiList.empty()) {
                cout << "\n\033[31mSarasas tuscias: pirma iveskite arba nuskaitykite studentus.\033[0m\n";
                continue;
                }
                int parametras = PasirinktiRusiavimoParametra();
 
                if (konteineris == VEKTORIUS) {
                    DalintiRusiuotiIrasyti(studentai, parametras);
                } else {
                    DalintiRusiuotiIrasyti(studentaiList, parametras);
                }
                continue;
            }
            case 4:{
                SukurtiVisusTestavimoFailus();
                continue;
            }
            case 5:{
                int parametras = PasirinktiRusiavimoParametra();
                PaleistiTestus(parametras);
                continue;
            }
            case 6:{
                return 0;
            }
            default:
                cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
                continue;
        }

    }
        return 0;
    
}