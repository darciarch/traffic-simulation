#include "Fahrzeug.h"
#include "Verhalten.h"
#include <iomanip>
#include <iostream>
#include <typeinfo>
using namespace std;

extern double dGlobaleZeit;

Fahrzeug::Fahrzeug(string sName)
    : Simulationsobjekt(sName), p_dMaxGeschwindigkeit(0.0),
      p_dGesamtStrecke(0.0), p_dAbschnittStrecke(0.0), p_dGesamtZeit(0.0) {
  cout << "Fahrzeug: Name - ID | " << p_sName << " - " << p_iID
       << " wurde erstellt." << endl;
}

Fahrzeug::Fahrzeug()
    : Simulationsobjekt(""), p_dMaxGeschwindigkeit(0.0), p_dGesamtStrecke(0.0),
      p_dAbschnittStrecke(0.0), p_dGesamtZeit(0.0) {
  cout << "Fahrzeug: Name - ID | " << p_sName << " - " << p_iID
       << " wurde erstellt." << endl;
}

Fahrzeug::Fahrzeug(string sName, double dMaxGeschwindigkeit)
    : Simulationsobjekt(sName),
      p_dMaxGeschwindigkeit((dMaxGeschwindigkeit >= 0) ? dMaxGeschwindigkeit
                                                       : 0.0),
      p_dGesamtStrecke(0.0), p_dAbschnittStrecke(0.0), p_dGesamtZeit(0.0) {
  cout << "Fahrzeug: Name - ID | " << p_sName << " - " << p_iID
       << " wurde erstellt." << endl;
}

Fahrzeug::~Fahrzeug() {
  // Destructor chaining calls Simulationsobjekt destructor automatically
}

void Fahrzeug::vKopf() {
  cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(20)
       << "MaxGeschwindigkeit" << setw(15) << "Gesamtstrecke" << setw(18)
       << "AbschnittStrecke" << setw(20) << "Verbrauchen (100km)" << setw(15)
       << "TankVolumen" << setw(15) << "TankInhalt" << endl;
  cout << setfill('-') << setw(100) << " " << setfill(' ') << " " << endl;
}

void Fahrzeug::vAusgeben(ostream &o) const {
  Simulationsobjekt::vAusgeben(o);
  o << setw(15) << p_dMaxGeschwindigkeit << setw(15) << p_dGesamtStrecke
    << setw(15) << p_dAbschnittStrecke;
}

void Fahrzeug::vSimulieren() {
  if (dGlobaleZeit > p_dZeit) {
    double dZeitDiff = dGlobaleZeit - p_dZeit;
    double dStrecke = 0.0;

    // if (p_pVerhalten != nullptr) { FOR BEST PRACTICE REASONS
    if (p_pVerhalten) {
      dStrecke = p_pVerhalten->dStrecke(*this, dZeitDiff);
    } else {
      dStrecke = dGeschwindigkeit() * dZeitDiff;
    }

    p_dGesamtStrecke += dStrecke;
    p_dAbschnittStrecke += dStrecke;
    p_dGesamtZeit += dZeitDiff; // Total time the vehicle has been moving
    p_dZeit = dGlobaleZeit;     // Update last simulated time
  }
}

double Fahrzeug::dTanken(double dMenge) { return 0.0; }

double Fahrzeug::dGeschwindigkeit() const { return p_dMaxGeschwindigkeit; }

double Fahrzeug::getAbschnittStrecke() const { return p_dAbschnittStrecke; }

bool Fahrzeug::operator<(const Fahrzeug &fahrzeug) const {
  if (this->p_dGesamtStrecke < fahrzeug.p_dGesamtStrecke) {
    return true;
  } else {
    return false;
  }
}

void Fahrzeug::operator=(const Fahrzeug &fahrzeug) {
  Simulationsobjekt::operator=(fahrzeug);
  this->p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;
  this->p_dGesamtStrecke = fahrzeug.p_dGesamtStrecke;
  this->p_dGesamtZeit = fahrzeug.p_dGesamtZeit;
}

void Fahrzeug::vNeueStrecke(Weg *pWeg) {
  p_pVerhalten = std::make_unique<Fahren>(*pWeg);
  p_dAbschnittStrecke = 0.0;
  p_dZeit = dGlobaleZeit;
}

void Fahrzeug::vNeueStrecke(Weg *pWeg, double dStartzeit) {
  p_pVerhalten = std::make_unique<Parken>(*pWeg, dStartzeit);
  p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vZeichnen(const Weg &weg) const {}