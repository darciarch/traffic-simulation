#include "Fahrrad.h"
#include "SimuClient.h"
#include "Weg.h"
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

Fahrrad::Fahrrad(string sName, double dMaxGeschwindigkeit)
    : Fahrzeug(sName, dMaxGeschwindigkeit) {}

double Fahrrad::dGeschwindigkeit() const {
  int iAnzahl20kms = (int)(p_dGesamtStrecke / 20);
  double dAktuelleGeschwindigkeit =
      p_dMaxGeschwindigkeit * pow(0.9, iAnzahl20kms);
  return ((dAktuelleGeschwindigkeit < 12.0) ? 12.0 : dAktuelleGeschwindigkeit);
}

void Fahrrad::vAusgeben(ostream &o) const {
  Fahrzeug::vAusgeben(o);
  o << setw(20) << "-" << setw(15) << "-" << setw(15) << "-" << endl;
}

void Fahrrad::vZeichnen(const Weg &weg) const {
  bZeichneFahrrad(getName(), weg.getName(),
                  getAbschnittStrecke() / weg.getLange(), dGeschwindigkeit());
}