# Studentų pažymių skaičiavimo programa

Objektinio programavimo kurso darbas. Programa leidžia surinkti studentų namų darbų ir egzamino
pažymius (įvedant ranka, sugeneruojant atsitiktinai arba nuskaitant iš failo) ir apskaičiuoja
galutinį balą dviem būdais – pagal namų darbų **vidurkį** ir pagal jų **medianą**.

- **v0.2** – studentų skirstymas į dvi grupes, rūšiavimas, rašymas į failus, laiko matavimas.
- **v0.3** – visos funkcijos veikia ir su `std::vector`, ir su `std::list`; konteinerių palyginimas.
- **v1.0** – trys studentų dalijimo strategijos (+ papildoma „Mano“), efektyvūs STL algoritmai, `CMakeLists.txt`.
- **v1.1** – struktūra `Studentas` pakeista **klase** (`Studentas.h` / `Studentas.cpp`): privatūs laukai, konstruktoriai,
  destruktorius, getteriai / setteriai; atliktas `struct` ir `class` versijų spartos palyginimas ir optimizavimo flag'ų tyrimas.

Galutinio balo formulės:

```
galutinis (vid.) = 0.4 * namų darbų vidurkis + 0.6 * egzaminas
galutinis (med.) = 0.4 * namų darbų mediana + 0.6 * egzaminas
```

Galutinis balas suapvalinamas iki dviejų skaitmenų po kablelio.

---

## Turinys

- [Diegimas ir paleidimas](#diegimas-ir-paleidimas)
- [Projekto failai](#projekto-failai)
- [Klasė Studentas (v1.1)](#klasė-studentas-v11)
- [Naudojimo instrukcija](#naudojimo-instrukcija)
- [Duomenų failo formatas](#duomenų-failo-formatas)
- [Dalijimo strategijos](#dalijimo-strategijos)
- [Tyrimas (v1.1)](#tyrimas-v11)
  - [Metodika](#metodika)
  - [struct (v1.0) ir class (v1.1) palyginimas](#struct-v10-ir-class-v11-palyginimas)
  - [Optimizavimo flag'ų tyrimas](#optimizavimo-flago-tyrimas)
  - [v1.1 rezultatai pagal strategijas ir konteinerius](#v11-rezultatai-pagal-strategijas-ir-konteinerius)
  - [Išvados](#išvados)
- [Versijos (releases)](#versijos-releases)

---

## Diegimas ir paleidimas

**Reikalavimai:** C++17 palaikantis kompiliatorius (`g++`, `clang++` arba MSVC) ir CMake ≥ 3.10.
C++17 reikalingas dėl `if constexpr` ir `is_same_v`, naudojamų šablonuose.

### Su CMake (rekomenduojama)

```
git clone https://github.com/anzhelina-kaminskaite2198/Objektinis2.git
cd Objektinis2

cmake -S . -B build
cmake --build build
```

Paleidimas:

| Aplinka | Komanda |
|---|---|
| Linux / macOS / MinGW | `./build/studentai` |
| Windows (Visual Studio generatorius) | `cmake --build build --config Release`, tada `build\Release\studentai.exe` |

Pagal nutylėjimą kompiliuojama **Release** režimu (su optimizacijomis), nes tik tokiu būdu laiko
matavimai turi prasmę. Jei Windows sistemoje CMake nerodo kompiliatoriaus (`nmake` klaida),
nurodykite generatorių: `cmake -S . -B build -G "MinGW Makefiles"`.

**Kompiliavimas su pasirinktu optimizavimo lygiu** (naudota flag'ų tyrime):

```
cmake -S . -B build_O1 -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE="-O1"
cmake --build build_O1
```

Analogiškai su `-O2` ir `-O3`.

### Be CMake (tik g++)

```
g++ -std=c++17 -O2 main.cpp TestiniaiFailai.cpp Studentas.cpp -o studentai
./studentai
```

> **Pastaba apie spalvas.** Programa klaidoms paryškinti naudoja ANSI spalvų kodus (`\033[31m`).
> Windows `cmd.exe` jie gali būti rodomi kaip nesuprantami simboliai – rekomenduojama naudoti
> Windows Terminal, PowerShell 7 arba Git Bash.
>
> **Pastaba apie kompiliavimą.** Jei pamirštamas `TestiniaiFailai.cpp`, rodoma klaida
> `undefined reference to SukurtiVisusTestavimoFailus()`; jei pamirštamas `Studentas.cpp` – klaidos dėl
> `Studentas` metodų.

---

## Projekto failai

| Failas | Kas jame yra |
|---|---|
| `CMakeLists.txt` | Projekto surinkimo aprašas (C++17, Release pagal nutylėjimą) |
| `Studentas.h` | Klasės `Studentas` deklaracija (privatūs laukai, viešas interfeisas) |
| `Studentas.cpp` | Klasės `Studentas` metodų, konstruktorių, destruktoriaus ir `>>` / `<<` operatorių realizacija |
| `Strukturos.h` | Klasė `NeteisingiDuomenys` ir laiko matavimo struktūra `Laikmatis` |
| `StudentuFunkcijos.h` | Visos studentų funkcijos: įvedimas, skaičiavimas, skaitymas iš failo, dalijimo strategijos, rūšiavimas, įrašymas, testų paleidimas (daugelis – šablonai) |
| `TestiniaiFailai.cpp` | Atsitiktinių testinių failų kūrimas |
| `main.cpp` | Meniu ir programos eiga |

---

## Klasė Studentas (v1.1)

Ankstesnėse versijose `Studentas` buvo `struct` su vieša prieiga prie visų laukų. Versijoje v1.1 tai yra klasė:
laukai paslėpti (`private`), o prieiga – per viešą interfeisą.

```cpp
class Studentas {
private:
    string vardas_;
    string pavarde_;
    vector<double> namuDarbai_;
    double egzaminas_;
    double galutinisVid_;
    double galutinisMed_;

public:
    Studentas(string v = "", string p = "", vector<double> nd = {}, double egz = 0);
    Studentas(const Studentas& o);                       // kopijavimo konstruktorius
    Studentas(Studentas&& o) noexcept;                   // perkėlimo konstruktorius
    Studentas& operator=(const Studentas& o);            // kopijavimo priskyrimas
    Studentas& operator=(Studentas&& o) noexcept;        // perkėlimo priskyrimas
    ~Studentas();                                        // destruktorius

    // getteriai (const) ir setteriai
    const string& vardas() const;   const string& pavarde() const;
    const vector<double>& namuDarbai() const;
    double egzaminas() const;  double galutinisVid() const;  double galutinisMed() const;
    void setVardas(const string&);  void setPavarde(const string&);
    void setNamuDarbai(vector<double>);  void pridetiND(double);
    void setEgzaminas(double);  void setGalutinisVid(double);  void setGalutinisMed(double);

    friend istream& operator>>(istream&, Studentas&);
    friend ostream& operator<<(ostream&, const Studentas&);
};
```

- **Konstruktorius** su numatytosiomis reikšmėmis kartu veikia ir kaip numatytasis (`Studentas s;`).
- **Perkėlimo konstruktorius ir priskyrimas** yra būtini efektyviam dalijimui: strategijos `S2`, `Mano` ir `Optimizuota`
  perkelia studentus tarp konteinerių per `std::move`. Be jų (kai deklaruotas destruktorius) kompiliatorius perkėlimo
  operacijų nesugeneruoja ir studentai būtų kopijuojami. Jos pažymėtos `noexcept`, kad `std::vector` plečiantis perkeltų, o ne kopijuotų elementus.
- **Getteriai** grąžina `const&`, todėl objektų nereikia kopijuoti.
- Klasė `NeteisingiDuomenys` (blogi įrašai skaitant iš failo) taip pat paversta klase su getteriais ir setteriais.

---

## Naudojimo instrukcija

Paleidus programą rodomas meniu:

```
              MENIU
-----------------------------------
1  Ivesti nauja studenta
2  Nuskaityti duomenis is failo
3  Padalinti, surusiuoti ir irasyti studentus i failus
4  Sukurti testavimo failus (5 failai)
5  Paleisti testavimus (5 failai)
6  Iseiti
```

**Rekomenduojama eiga tyrimui:** `4` (sukuria testinius failus vieną kartą) → `5` (paleidžia testus) → `6`.

1. **Įvesti naują studentą** – prašoma vardo ir pavardės, tada pasirenkama, ar namų darbų pažymius
   įvesti ranka (baigiama paspaudus ENTER tuščioje eilutėje), ar sugeneruoti atsitiktinai. Tas pats
   pasirinkimas galioja egzaminui; jei egzaminas įvedamas ranka ir paspaudžiamas tik ENTER, jis laikomas 0.
   Išvedamas ir studento objekto adresas atmintyje (`&studentai.back()`).
2. **Nuskaityti duomenis iš failo** – prašoma failo pavadinimo (pvz. `kursiokai.txt`). Paskutinis
   eilutės skaičius laikomas egzamino pažymiu, visi prieš jį – namų darbais. Parodomas nuskaitymo
   laikas ir, jei buvo blogų įrašų, jų sąrašas.
3. **Padalinti, surūšiuoti ir įrašyti** – pasirenkama, pagal ką rūšiuoti (vardą, pavardę ar galutinį
   balą); studentai padalinami į dvi grupes (naudojama greičiausia strategija – `Optimizuota`),
   kiekviena grupė surūšiuojama ir įrašoma į `vargseliai.txt` / `kietuoliai.txt`.
   **Po šio žingsnio pradinis sąrašas tampa tuščias** – norint kartoti, duomenis reikia nuskaityti iš naujo.
4. **Sukurti testavimo failus** – žr. [Testiniai failai](#testiniai-failai).
5. **Paleisti testavimus** – kiekvienai strategijai, kiekvienam konteineriui (`vector`, `list`) ir
   kiekvienam iš 5 failų atliekamas skaitymas, dalijimas, rūšiavimas ir įrašymas (3 kartai), išvedami laikų vidurkiai.
6. **Išeiti**.

### Testiniai failai

| Failas | Studentų skaičius | ND stulpelių |
|---|---|---|
| `studentai1000.txt` | 1 000 | 3 |
| `studentai10000.txt` | 10 000 | 4 |
| `studentai100000.txt` | 100 000 | 5 |
| `studentai1000000.txt` | 1 000 000 | 6 |
| `studentai10000000.txt` | 10 000 000 | 7 |

Vardai ir pavardės: `Vardas1`, `Pavarde1`, ...; pažymiai – atsitiktiniai sveikieji nuo 0 iki 10.
Failai sukuriami **vieną kartą** ir naudojami visiems testams, kad palyginimas būtų sąžiningas.
Didžiausias failas (10 mln. įrašų) užima daug vietos diske ir daug RAM apdorojant (ypač S1 strategija, kuri
laiko dvi studentų kopijas).

### Įvesties tikrinimas

- Netinkamas meniu pasirinkimas – srautas išvalomas ir meniu rodomas iš naujo (`IvedimoKlaidos()`).
- Pažymys turi būti skaičius intervale **[0; 10]**; tekstas vietoj skaičiaus gaudomas per `std::invalid_argument`.
- Generuojamų namų darbų skaičius negali būti neigiamas.
- Neegzistuojantis failas – parodomas pranešimas, grįžtama į meniu.
- Eilutės su blogais pažymiais į sąrašą nepatenka, o surenkamos į `neteisingi` ir parodomos vartotojui.

---

## Duomenų failo formatas

Pirma eilutė – antraštė (praleidžiama). Toliau kiekviena eilutė – vienas studentas:

```
Vardas        Pavarde        ND1   ND2   ND3   ND4   ND5   Egz.
Vardas1       Pavarde1       8     9     7     3     3     10
```

Namų darbų skaičius iš anksto nežinomas – skaitomi visi eilutės skaičiai, **paskutinis** priskiriamas
egzaminui. Stulpelių skaičius eilutėse gali skirtis, skirtukai – bet koks tarpų kiekis.

---

## Dalijimo strategijos

Studentai skirstomi pagal galutinį balą (pagal vidurkį): **< 5.0 – „vargšeliai“**, **≥ 5.0 – „kietuoliai“**.
Strategijos nesikeitė nuo v1.0.

| Strategija | Aprašymas | `vector` | `list` |
|---|---|---|---|
| **S1** | Bendras konteineris skaidomas į du **naujus** konteinerius, studentai **kopijuojami** (`partition_copy`). Studentas yra dviejuose konteineriuose (bendrame ir naujame) – didžiausias atminties naudojimas. | `partition_copy` | `partition_copy` |
| **S2** | Naudojamas tik vienas naujas konteineris („vargšeliai“); vargšeliai perkeliami į jį ir **ištrinami** iš bendro, kuriame lieka kietuoliai. | Rūšiavimas pagal balą ir `pop_back()` vargšelių | `erase` ciklu |
| **Mano** | Vienas praėjimas, kiekvienas studentas **perkeliamas** (ne kopijuojamas) į vieną iš dviejų naujų konteinerių. | `count_if` + `reserve` + `partition_copy` su `move_iterator` | `splice` į abu konteinerius |
| **Optimizuota (S3)** | Greičiausios strategijos (S1/S2) variantas su efektyviais STL algoritmais. | `copy_if` + `remove_if` (judinami elementai) | `splice` tik vargšelių, likęs konteineris perimamas per `move` |

**Naudoti algoritmai:** `std::partition_copy`, `std::copy_if`, `std::remove_if`, `std::count_if`, `std::sort`
(`vector`), `std::list::sort`, `std::list::splice`, `std::make_move_iterator`.

---

## Tyrimas (v1.1)

### Metodika

- Failai: `studentai1000.txt` ... `studentai10000000.txt`, sugeneruoti vieną kartą ir naudoti visiems testams.
- Kiekvienam failui, konteineriui ir strategijai testas kartojamas **3 kartus**, pateikiamas **vidurkis** (sekundėmis).
- Matuojami etapai: nuskaitymas, dalijimas, rūšiavimas (pagal galutinį balą), vargšelių ir kietuolių įrašymas į failus.
  Bendras laikas – šių etapų suma.
- Kompiliavimas: C++17, Release. `struct` versija (v1.0) matuota su `-O2`; `class` versija (v1.1) – taip pat `-O2`.
- Palyginimas `struct` ir `class`: **vienas fiksuotas konteineris – `std::vector`**, **greičiausia dalijimo strategija – `Optimizuota`**,
  failai su 100 000 ir 1 000 000 studentų. `struct` rezultatai paimti iš v1.0 (`git checkout v1.0`), `class` – iš v1.1.

### struct (v1.0) ir class (v1.1) palyginimas

`std::vector`, strategija `Optimizuota`, laikai sekundėmis (3 testų vidurkis). Paskutiniame stulpelyje – `class` laikas,
padalintas iš `struct` laiko (> 1 reiškia, kad `class` lėtesnė).

| Etapas | struct (v1.0) | class (v1.1) | class / struct |
|---|---|---|---|
| **100 000 studentų** | | | |
| Nuskaitymas | 0.157542 | 0.168596 | 1.07 |
| Dalijimas | 0.005614 | 0.005401 | 0.96 |
| Rūšiavimas | 0.014289 | 0.016959 | 1.19 |
| Vargšelių įrašymas | 0.076373 | 0.080045 | 1.05 |
| Kietuolių įrašymas | 0.072466 | 0.075546 | 1.04 |
| **Bendras** | **0.326282** | **0.346547** | 1.06 |
| **1 000 000 studentų** | | | |
| Nuskaitymas | 1.923079 | 2.018468 | 1.05 |
| Dalijimas | 0.043173 | 0.046886 | 1.09 |
| Rūšiavimas | 0.192033 | 0.225865 | 1.18 |
| Vargšelių įrašymas | 0.590214 | 0.757712 | 1.28 |
| Kietuolių įrašymas | 0.609687 | 0.725917 | 1.19 |
| **Bendras** | **3.358187** | **3.774848** | 1.12 |

Papildomai – santykis `class / struct` kitiems failų dydžiams (tas pats konteineris ir strategija):

| Studentų sk. | Dalijimas (class / struct) | Rūšiavimas (class / struct) | Bendras (class / struct) |
|---|---|---|---|
| 1 000 | 0.93 | 0.96 | 0.80 |
| 10 000 | 1.05 | 1.33 | 0.69 |
| 100 000 | 0.96 | 1.19 | 1.06 |
| 1 000 000 | 1.09 | 1.18 | 1.12 |
| 10 000 000 | 1.16 | 1.17 | 1.22 |

**Pastebėjimai:**

- Su `class` programa veikia apie **6 % lėtesnė** esant 100 000 įrašų ir apie **12 % lėtesnė** esant 1 000 000 įrašų.

### Optimizavimo flag'ų tyrimas

`std::vector`, strategija `Optimizuota`, 3 testų vidurkis.

| Flag | Versija | 1 000 bendras (s) | 10 000 bendras (s) | 100 000 bendras (s) | 1 000 000 bendras (s) | 10 000 000 bendras (s) |
|---|---|---|---|---|---|---|
| -O1 | struct (v1.0) | 0.011142 | 0.038302 | 0.329136 | 3.609054 | 37.879440 |
| -O1 | class (v1.1) | 0.012221 | 0.046800 | 0.422897 | 3.954720 | 48.878690 |
| -O2 | struct (v1.0) | 0.012656 | 0.061272 | 0.538387 | 5.391878 | 56.506400 |
| -O2 | class (v1.1) | 0.011639 | 0.035266 | 0.346547 | 3.774848 | 42.756858 |
| -O3 | struct (v1.0) | 0.020217 | 0.062437 | 0.526834 | 5.240572 | 56.162429 |
| -O3 | class (v1.1) | 0.011012 | 0.062824 | 0.553133 | 5.719030 | 62.990706 |


### v1.1 rezultatai pagal strategijas ir konteinerius

Visi laikai – sekundėmis, 3 testų vidurkis. Greičiausia strategija kiekvienoje eilutėje pažymėta **paryškintai**.

**Dalijimo laikas, `std::vector`**

| Studentų sk. | S1 | S2 | Mano | Optimizuota |
|---|---|---|---|---|
| 1 000 | 0.000147 | 0.000191 | 0.000099 | **0.000041** |
| 10 000 | 0.001749 | 0.002039 | 0.000676 | **0.000496** |
| 100 000 | 0.012416 | 0.023234 | 0.007989 | **0.005401** |
| 1 000 000 | 0.108851 | 0.279057 | 0.065676 | **0.046886** |
| 10 000 000 | 1.663611 | 3.410351 | 0.997732 | **0.593966** |

**Dalijimo laikas, `std::list`**

| Studentų sk. | S1 | S2 | Mano | Optimizuota |
|---|---|---|---|---|
| 1 000 | 0.000145 | 0.000059 | 0.000169 | **0.000046** |
| 10 000 | 0.001301 | 0.000494 | 0.001198 | **0.000303** |
| 100 000 | 0.013621 | 0.005028 | 0.011882 | **0.002552** |
| 1 000 000 | 0.150183 | 0.057492 | 0.130821 | **0.025817** |
| 10 000 000 | 1.929788 | 0.518276 | 2.070263 | **0.240221** |

**Bendras testo laikas, `std::vector`**

| Studentų sk. | S1 | S2 | Mano | Optimizuota |
|---|---|---|---|---|
| 1 000 | 0.014196 | 0.012283 | 0.013361 | **0.011639** |
| 10 000 | 0.039019 | 0.038645 | 0.038164 | **0.035266** |
| 100 000 | 0.344015 | 0.348790 | **0.340309** | 0.346547 |
| 1 000 000 | **3.535742** | 3.884839 | 3.758004 | 3.774848 |
| 10 000 000 | **40.356607** | 42.356384 | 40.691542 | 42.756858 |

**Bendras testo laikas, `std::list`**

| Studentų sk. | S1 | S2 | Mano | Optimizuota |
|---|---|---|---|---|
| 1 000 | 0.012548 | 0.012666 | **0.012431** | 0.012800 |
| 10 000 | 0.038508 | **0.035210** | 0.037152 | 0.038405 |
| 100 000 | 0.399124 | **0.358147** | 0.366849 | 0.399609 |
| 1 000 000 | 4.604206 | 4.127696 | 4.091612 | **4.005150** |
| 10 000 000 | 49.944465 | **47.262218** | 48.655513 | 47.698730 |

**Visų etapų laikai, `std::vector`, strategija `Optimizuota`**

| Studentų sk. | Nuskaitymas | Dalijimas | Rūšiavimas | Vargšelių įrašymas | Kietuolių įrašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 000 | 0.001971 | 0.000041 | 0.000125 | 0.005119 | 0.004384 | 0.011639 |
| 10 000 | 0.015850 | 0.000496 | 0.001628 | 0.009526 | 0.007766 | 0.035266 |
| 100 000 | 0.168596 | 0.005401 | 0.016959 | 0.080045 | 0.075546 | 0.346547 |
| 1 000 000 | 2.018468 | 0.046886 | 0.225865 | 0.757712 | 0.725917 | 3.774848 |
| 10 000 000 | 22.087157 | 0.593966 | 2.685723 | 8.280149 | 9.109864 | 42.756858 |

**Visų etapų laikai, `std::list`, strategija `Optimizuota`**

| Studentų sk. | Nuskaitymas | Dalijimas | Rūšiavimas | Vargšelių įrašymas | Kietuolių įrašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 000 | 0.003953 | 0.000046 | 0.000090 | 0.006244 | 0.002467 | 0.012800 |
| 10 000 | 0.016671 | 0.000303 | 0.000902 | 0.012061 | 0.008469 | 0.038405 |
| 100 000 | 0.192770 | 0.002552 | 0.024646 | 0.092006 | 0.087635 | 0.399609 |
| 1 000 000 | 2.003227 | 0.025817 | 0.556674 | 0.702155 | 0.717278 | 4.005150 |
| 10 000 000 | 22.236332 | 0.240221 | 9.893432 | 7.334838 | 7.993907 | 47.698730 |

### Išvados

- **struct ir class:** `class` versija šiek tiek lėtesnė (~6 % esant 100 000 ir ~12 % esant 1 000 000 įrašų bendram laikui);
  didžiausias skirtumas matomas rūšiavimo etape (~18–19 %). Klasės privalumai (inkapsuliacija, valdomas objekto gyvavimas)
  atsiperka nedideliu spartos nuostoliu.
- **Dalijimas:** tiek `vector`, tiek `list` atveju greičiausia strategija yra **Optimizuota** visuose failų dydžiuose.
  `vector`, 10 mln. įrašų: Optimizuota 0.593966 s, Mano 0.997732 s, S1 1.663611 s, S2 3.410351 s.
  `list`, 10 mln. įrašų: Optimizuota 0.240221 s, S2 0.518276 s, S1 1.929788 s, Mano 2.070263 s.
- **Bendras laikas:** nuskaitymas ir įrašymas sudaro apie 92–94 % laiko, todėl bendro laiko skirtumai tarp strategijų yra maži (kelių procentų)
  ir ne visada atitinka dalijimo laiko eiliškumą – juos lemia disko sparta ir matavimo paklaida.
- **Rūšiavimas:** `list::sort` nuo 100 000 įrašų lėtesnis už `vector` + `std::sort`; 10 mln. įrašų – 9.893432 s prieš 2.685723 s.

---

## Versijos (releases)

| Versija | Šaka | Trumpai |
|---|---|---|
| `v.pradinė` | `v.pradine` | Įvedimas ranka ir generavimas, vidurkis ir mediana, rezultatų lentelė |
| `v0.1` | `v0.1` | Skaitymas iš failo, blogų įrašų atmetimas, dalinė didelių sąrašų išvestis |
| `v0.2` | `v0.2` | Dalijimas į dvi grupes, rūšiavimo pasirinkimas, rašymas į failus, testiniai failai, laiko matavimas |
| `v0.3` | `v0.3` | Šablonai, `vector` ir `list`, objekto adresas, konteinerių spartos palyginimas |
| `v1.0` | `v1.0` | Dalijimo strategijos S1, S2, Mano, Optimizuota; efektyvūs STL algoritmai; `CMakeLists.txt`; pilnas README |
| `v1.1` | `V1.1` | `struct Studentas` pakeista `class`; `struct` / `class` palyginimas; optimizavimo flag'ų tyrimas |

### v.pradinė

Pirmoji veikianti versija: struktūra `Studentas`, `vector<Studentas>`, įvedimas ranka arba
atsitiktinis generavimas (`rand()`), galutinis balas pagal vidurkį ir medianą, lentelės išvedimas (`<iomanip>`),
įvesties klaidų tikrinimas. Failų skaitymo nebuvo, o visas sąrašas visada buvo išvedamas iš karto.

### v0.1

- Skaitymas iš failo (`SkaitytiIsFailo()`), paskutinis skaičius – egzaminas.
- Blogų įrašų atmetimas (`NeteisingiDuomenys`, `neteisingi`).
- Dalinė išvestis, kai studentų daugiau nei 40 (pirmi ir paskutiniai 20); rikiavimas pagal vardą.
- Pridėtas `.gitignore`, testinis failas `kursiokai.txt` su įterptomis klaidomis, ištaisytos įvedimo klaidos.

### v0.2

- Kodas išskaidytas į `Strukturos.h`, `StudentuFunkcijos.h`, `TestiniaiFailai.cpp`, `main.cpp`.
- Dalijimas į „vargšelius“ ir „kietuolius“ (`std::move`), rūšiavimo pasirinkimas, rašymas į `vargseliai.txt` / `kietuoliai.txt`.
- Testinių failų kūrimas (1 tūkst. – 10 mln.), spartos testavimas (3 kartai), `Laikmatis` su `std::chrono`.
- Galutiniai balai skaičiuojami vieną kartą (`galutinisVid`, `galutinisMed`), `mt19937` vietoje `rand()`.
- Pašalinta dalinė išvestis – rezultatai rašomi į failus.

### v0.3

- Funkcijos paverstos šablonais (`template <typename Container>`), veikia su `vector` ir `list`.
- `if constexpr` pasirenka `std::sort` arba `list::sort`; `shrink_to_fit()` tik `vector`.
- Objekto adreso išvedimas, abiejų konteinerių testavimas vienu paleidimu.
- Realizacijos perkeltos į `StudentuFunkcijos.h`, ne šablonų funkcijos ir globalūs kintamieji pažymėti `inline`.
- Konteinerių tyrimas.

### v1.0

- Realizuotos strategijos **S1**, **S2**, **Mano** ir **Optimizuota** abiem konteineriams (žr. [Dalijimo strategijos](#dalijimo-strategijos)).
- Naudojami efektyvūs algoritmai (`partition_copy`, `copy_if`, `remove_if`, `count_if`, `splice`).
- Testų paleidimas lygina visas strategijas su abiem konteineriais, 3 kartų vidurkis, ankstesnis failų generavimas.
- Pridėtas `CMakeLists.txt` (C++17, Release pagal nutylėjimą) ir diegimo instrukcija.
- README papildytas lentelėmis ir išvadomis.

### v1.1

- `struct Studentas` pakeista **klase** `Studentas` (`Studentas.h` / `Studentas.cpp`): privatūs laukai, konstruktorius,
  kopijavimo ir perkėlimo konstruktoriai bei priskyrimo operatoriai, destruktorius, getteriai ir setteriai, `>>` ir `<<` operatoriai.
- `NeteisingiDuomenys` paversta klase; visas kodas (`StudentuFunkcijos.h`) pritaikytas naudoti getterius ir setterius.
- `CMakeLists.txt` papildytas `Studentas.cpp`.
- Atliktas `struct` (v1.0) ir `class` (v1.1) spartos palyginimas ir optimizavimo flag'ų (`-O1`, `-O2`, `-O3`) tyrimas.

**Apribojimai:** po dalijimo pradinis konteineris išvalomas; `RikiotiStudentus` palaiko tik `vector<Studentas>` ir `list<Studentas>`;
10 mln. įrašų testui reikia kelių GB RAM (ypač S1).