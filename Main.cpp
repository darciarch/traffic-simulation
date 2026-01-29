#include "Fahrrad.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include "SimuClient.h"
#include "Weg.h"
#include "vertagt_liste.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
using namespace std;

void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6a();
void vAufgabe_6();
void vAufgabe_7();

double dGlobaleZeit = 0.0;
double dZeitTakt = 0.5;
double dSimulationsEnde = 5.0;

int main() {

  // vAufgabe_4();
  // vAufgabe_5();
  // vAufgabe_6();
  vAufgabe_7();
  // vAufgabe_6a();
  // vAufgabe_2();
  // vAufgabe_3();

  return 0;
}

void vAufgabe_1() {

  Fahrzeug a;
  Fahrzeug b("Ahmet");
  Fahrzeug *c = new Fahrzeug("BMW");

  vector<unique_ptr<Fahrzeug>> v1;
  vector<shared_ptr<Fahrzeug>> v2;

  unique_ptr<Fahrzeug> d = make_unique<Fahrzeug>("aso");
  unique_ptr<Fahrzeug> qaq = make_unique<Fahrzeug>("apopo");
  v1.push_back(std::move(d));
  v1.push_back(std::move(qaq));

  shared_ptr<Fahrzeug> f = make_shared<Fahrzeug>("shrd");
  shared_ptr<Fahrzeug> q = f;
  v2.push_back(f);
  v2.push_back(q);

  // cout << v2.size() << endl;
  // cout << q.use_count() << endl;

  delete c;
  v1.clear();
  v2.clear();
}

void vAufgabe_1a() {

  vector<unique_ptr<Fahrzeug>> vv1;

  unique_ptr<Fahrzeug> paa = make_unique<Fahrzeug>("Ahmet", 31);
  auto pa2 = make_unique<Fahrzeug>("Ahmetbaba", 31.5);
  auto pa3 = make_unique<Fahrzeug>("AhmetcanBaba", 32.5);

  vv1.push_back(std::move(paa));
  vv1.push_back(std::move(pa2));
  vv1.push_back(std::move(pa3));

  cout << endl;
  // & yaninda tip varsa referance yoksa cismin bellekteki adresini verir.
  // Boslugun önemi yok
  while (dGlobaleZeit <= dSimulationsEnde) {
    cout << "Aktuellen Zeit: " << dGlobaleZeit << endl;
    Fahrzeug::vKopf();
    for (unique_ptr<Fahrzeug> &i : vv1) {
      i->vSimulieren();
    };
    for (unique_ptr<Fahrzeug> &i : vv1) {
      i->vAusgeben(cout);
    };
    dGlobaleZeit += dZeitTakt;
    cout << endl;
  }
}

void vAufgabe_2() {

  int pkw_anzahl;
  int fahrrad_anzahl;

  vector<unique_ptr<Fahrzeug>> v2;

  cout << "Wie viele PKW?" << endl << "- ";
  cin >> pkw_anzahl;
  cout << "Wie viele Fahrräder?" << endl << "- ";
  cin >> fahrrad_anzahl;
  cin.ignore(10, '\n');
  cout << endl;

  for (int i = 1; i <= pkw_anzahl; i++) {
    string sName;
    double dGeschwindigkeit;
    double dVerbrauch;
    double dTankvolumen;
    cout << "Name für PKW " << i << "/" << pkw_anzahl << " : ";
    getline(cin, sName);
    cout << "Geschwindigkeit für PKW " << i << "/" << pkw_anzahl << " : ";
    cin >> dGeschwindigkeit;
    cout << "dVerbrauch für PKW " << i << "/" << pkw_anzahl << " : ";
    cin >> dVerbrauch;
    cout << "dTankvolumen für PKW " << i << "/" << pkw_anzahl << " : ";
    cin >> dTankvolumen;
    cin.ignore(); // only 1 time getline
    v2.push_back(
        make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch, dTankvolumen));
  }

  for (int i = 1; i <= fahrrad_anzahl; i++) {
    string sName;
    double dGeschwindigkeit;
    cout << "Name für Fahrrad " << i << "/" << fahrrad_anzahl << " : ";
    getline(cin, sName);
    cout << "Geschwindigkeit für Fahrrad " << i << "/" << fahrrad_anzahl
         << " : ";
    cin >> dGeschwindigkeit;
    cin.ignore();
    v2.push_back(make_unique<Fahrrad>(sName, dGeschwindigkeit));
  }

  /*
  unique_ptr<PKW> a = make_unique<PKW>("ALI", 40,5,100);
  unique_ptr<PKW> a2 = make_unique<PKW>("tot", 37,7,180);
  unique_ptr<Fahrrad> b = make_unique<Fahrrad>("Ahmeettt",40);
  unique_ptr<Fahrrad> b3 = make_unique<Fahrrad>("ahmetbaba",18);

  v2.push_back(std::move(a));
  v2.push_back(std::move(a2));
  v2.push_back(std::move(b));
  v2.push_back(std::move(b3));
  */

  cout << endl;
  double epsulon = 0.000001;
  while (dGlobaleZeit < 5.0) {
    if (dGlobaleZeit < dSimulationsEnde) {
      if (fabs(dGlobaleZeit - 3.0) < epsulon) {
        for (unique_ptr<Fahrzeug> &q : v2) {
          q->dTanken();
        }
      }
      cout << "Aktuellen Zeit: " << dGlobaleZeit << endl;
      Fahrzeug::vKopf();

      for (unique_ptr<Fahrzeug> &qw : v2) {
        qw->vSimulieren();
        qw->vAusgeben(cout);
      }

      dGlobaleZeit += dZeitTakt;
      cout << endl;
    }
  }
}

void vAufgabe_3() {

  vector<Fahrzeug *> v1;

  Fahrzeug a("all", 43.5);
  Fahrzeug b("s", 31);
  Fahrrad c("s", 25);
  PKW d("sasdas", 180, 12);

  v1.push_back(&a);
  v1.push_back(&b);
  v1.push_back(&c);
  v1.push_back(&d);

  // cout << a << b << c << d;
  double epsulon = 0.000001;
  while ((dGlobaleZeit - (dSimulationsEnde - 0.5)) < epsulon) {

    for (Fahrzeug *i : v1) {
      i->vSimulieren();
    }
    dGlobaleZeit += dZeitTakt;
  }

  cout << endl << "Aktueller Zeit: " << dGlobaleZeit << endl;
  if (dGlobaleZeit == 5.0) {
    Fahrzeug::vKopf();
    for (Fahrzeug *i : v1) {
      i->vAusgeben(cout);
      cout << endl;
    }
    cout << endl;
    cout << "False = 0 , True = 1" << endl;
    cout << (a < b) << endl << endl;
  }

  // Fahrzeug ahmet = a; bu copy initialization
  Fahrzeug ahmet("baba", 49);
  ahmet = a;
  cout << "BABA 49" << endl << ahmet << endl;
}

void vAufgabe_4() {
  Weg w1("B500", 10000.0, Tempolimit::Landstrasse);
  Weg::vKopf();
  cout << w1 << endl;
}

void vAufgabe_5() {
  Weg w1("B500", 10000.0, Tempolimit::Landstrasse);

  unique_ptr<Fahrzeug> f1 = make_unique<Fahrzeug>("BMW", 150);
  unique_ptr<Fahrzeug> f2 = make_unique<Fahrzeug>("Audi", 200);
  unique_ptr<Fahrzeug> f3 = make_unique<Fahrzeug>("VW", 100);
  unique_ptr<Fahrzeug> f4 = make_unique<Fahrzeug>("Opel", 51000);

  w1.vAnnahme(std::move(f1));
  w1.vAnnahme(std::move(f2));
  w1.vAnnahme(std::move(f3), 2.0); // Parking
  w1.vAnnahme(std::move(f4), 4.0); // Parking

  Weg::vKopf();
  cout << w1 << endl;

  // Run simulation loop (reseting and modifying)
  dGlobaleZeit = 0.0;
  dSimulationsEnde = 6.0;

  while (dGlobaleZeit < dSimulationsEnde) {
    dGlobaleZeit += dZeitTakt;
    cout << "Zeit: " << dGlobaleZeit << endl;
    w1.vSimulieren(); // This will trigger behavior logic
    cout << w1 << endl;
  }
}

void vAufgabe_6() {
  bInitialisiereGrafik(800, 500);

  Weg W1("W1", 500, Tempolimit::Innerorts);
  Weg W2("W2", 500, Tempolimit::Landstrasse);

  std::unique_ptr<Fahrzeug> p1 = std::make_unique<PKW>("Audi", 150, 4, 600);
  std::unique_ptr<Fahrzeug> p2 = std::make_unique<PKW>("BMW", 120, 2, 500);
  std::unique_ptr<Fahrzeug> p3 = std::make_unique<Fahrrad>("Bike", 25);
  std::unique_ptr<Fahrzeug> p4 = std::make_unique<PKW>("Oldtimer", 45, 10);

  W1.vKopf();

  W1.vAnnahme(std::move(p1), 1.0); // Park
  W1.vAnnahme(std::move(p3));      // Drive
  W2.vAnnahme(std::move(p2));      // Drive
  W2.vAnnahme(std::move(p4), 3.0); // Park

  // Draw Road
  int coords[] = {100, 250, 700, 250};
  bZeichneStrasse(W1.getName(), W2.getName(), 500, 2, coords);

  // Simulation Loop
  for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += 0.5) {
    vSetzeZeit(dGlobaleZeit);

    cout << "Zeit: " << dGlobaleZeit << endl;

    W1.vSimulieren();
    W1.vAusgeben(cout);
    W1.vZeichnen();

    W2.vSimulieren();
    W2.vAusgeben(cout);
    W2.vZeichnen();

    vSleep(100); // Wait 200ms
  }

  vBeendeGrafik();
}
void vAufgabe_6a() {
  using namespace vertagt;
  VListe<int> vListe;
  static std::mt19937 device(0); // seed is same every time (0)
  std::uniform_int_distribution<int> dist(1, 10);

  for (int i = 0; i < 10; ++i) {
    vListe.push_back(dist(device));
  }
  vListe.vAktualisieren(); // Commit initial population

  cout << "Liste vor Erase:" << endl;
  for (auto it = vListe.begin(); it != vListe.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;

  for (auto it = vListe.begin(); it != vListe.end(); ++it) {
    if (*it > 5) {
      vListe.erase(it);
    }
  }

  cout << "Liste nach Erase (ohne Aktualisieren):" << endl;
  for (auto it = vListe.begin(); it != vListe.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;

  vListe.vAktualisieren();

  cout << "Liste nach Aktualisieren:" << endl;
  for (auto it = vListe.begin(); it != vListe.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;

  vListe.push_front(100);
  vListe.push_back(200);
  vListe.vAktualisieren();

  cout << "Liste am Ende:" << endl;
  for (auto it = vListe.begin(); it != vListe.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

#include "Kreuzung.h"

void vAufgabe_7() {
  bInitialisiereGrafik(1000, 600);

  auto kr1 = std::make_shared<Kreuzung>("Kr1", 0);
  auto kr2 = std::make_shared<Kreuzung>("Kr2", 1000); // Tankstelle
  auto kr3 = std::make_shared<Kreuzung>("Kr3", 0);
  auto kr4 = std::make_shared<Kreuzung>("Kr4", 0);

  // bagla
  // S1
  Kreuzung::vVerbinde(kr1, kr2, "W12", "W21", 40, Tempolimit::Innerorts);

  // S2
  Kreuzung::vVerbinde(kr2, kr3, "W23a", "W32a", 115, Tempolimit::Autobahn);

  // S3
  Kreuzung::vVerbinde(kr2, kr3, "W23b", "W32b", 40, Tempolimit::Innerorts);

  // S4
  Kreuzung::vVerbinde(kr2, kr4, "W24", "W42", 55, Tempolimit::Innerorts);

  // S5
  Kreuzung::vVerbinde(kr3, kr4, "W34", "W43", 85, Tempolimit::Autobahn);

  // S6
  Kreuzung::vVerbinde(kr4, kr4, "W44a", "W44b", 130, Tempolimit::Landstrasse);

  int str1[] = {680, 40, 680, 300};
  bZeichneStrasse("W12", "W21", 40, 2, str1);

  int str2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
  bZeichneStrasse("W23a", "W32a", 115, 6, str2);

  int str3[] = {680, 300, 680, 570};
  bZeichneStrasse("W23b", "W32b", 40, 2, str3);

  int str4[] = {680, 300, 320, 300};
  bZeichneStrasse("W24", "W42", 55, 2, str4);

  int str5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
  bZeichneStrasse("W34", "W43", 85, 5, str5);

  int str6[] = {320, 300, 170, 300, 70,  250, 80,
                90,  200, 60,  320, 150, 320, 300};
  bZeichneStrasse("W44a", "W44b", 130, 7, str6);

  kr1->vAnnahme(std::make_unique<PKW>("Audi", 150, 8, 50), 0.5);
  kr1->vAnnahme(std::make_unique<PKW>("BMW", 180, 10, 60), 1.0);
  kr1->vAnnahme(std::make_unique<Fahrrad>("Bike", 25), 1.5);

  // cizdir
  bZeichneKreuzung(680, 40);
  bZeichneKreuzung(680, 300);
  bZeichneKreuzung(680, 570);
  bZeichneKreuzung(320, 300);

  for (dGlobaleZeit = 0; dGlobaleZeit < 20; dGlobaleZeit += 0.1) {
    vSetzeZeit(dGlobaleZeit);

    // Simuliere Kreuzungen
    kr1->vSimulieren();
    kr2->vSimulieren();
    kr3->vSimulieren();
    kr4->vSimulieren();

    // araclari cizdir
    auto wege1 = kr1->getWege();
    for (auto &w : wege1)
      w->vZeichnen();

    auto wege2 = kr2->getWege();
    for (auto &w : wege2)
      w->vZeichnen();

    auto wege3 = kr3->getWege();
    for (auto &w : wege3)
      w->vZeichnen();

    auto wege4 = kr4->getWege();
    for (auto &w : wege4)
      w->vZeichnen();

    vSleep(200);
  }
  vBeendeGrafik();
}