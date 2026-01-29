#include "PKW.h"
#include "SimuClient.h"
#include "Verhalten.h"
#include "Weg.h"
#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

extern double p_dZeit;
double inf = std::numeric_limits<double>::infinity();

PKW::PKW(string sName, double dGeschwindigkeit, double dVerbrauch,
         double dTankVolumen)
    : Fahrzeug(sName, dGeschwindigkeit), p_dVerbrauch(dVerbrauch),
      p_dTankVolumen(dTankVolumen), p_dTankinhalt(p_dTankVolumen / 2) {

  cout << "PKW wurde erstellt." << endl;
}

PKW::~PKW() { cout << "PKW wurde gelöscht..." << endl; }

double PKW::dTanken(double dMenge) {
  double FreiVolumen = p_dTankVolumen - p_dTankinhalt;
  double dGetankteMenge = (FreiVolumen < dMenge) ? FreiVolumen : dMenge;

  p_dTankinhalt += dGetankteMenge;
  return dGetankteMenge;
}

double PKW::dGeschwindigkeit() const {
  if (p_pVerhalten) {
    double limit = p_pVerhalten->getWeg().getTempolimit();
    return (p_dMaxGeschwindigkeit < limit) ? p_dMaxGeschwindigkeit : limit;
  }
  return p_dMaxGeschwindigkeit;
}

void PKW::vSimulieren() {
  if (p_dTankinhalt > 0.0) {
    double dZeitdiff = dGlobaleZeit - p_dZeit;
    double dVerbrauchproschnitt =
        p_dVerbrauch / 100 * dZeitdiff * p_dMaxGeschwindigkeit;
    p_dTankinhalt -= dVerbrauchproschnitt;

    Fahrzeug::vSimulieren();

    if (p_dTankinhalt < 0) {
      p_dTankinhalt = 0.0;
    }
  } else {
    p_dZeit = dGlobaleZeit;
  }
}

void PKW::vAusgeben(ostream &o) const {
  Fahrzeug::vAusgeben(o);
  o << setw(20) << p_dVerbrauch << setw(15) << p_dTankVolumen << setw(15)
    << p_dTankinhalt << endl;
}

void PKW::vZeichnen(const Weg &weg) const {
  bZeichnePKW(getName(), weg.getName(), getAbschnittStrecke() / weg.getLange(),
              dGeschwindigkeit(), p_dTankinhalt);
}