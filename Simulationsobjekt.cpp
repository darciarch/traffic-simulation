#include "Simulationsobjekt.h"
#include <iomanip>

using namespace std;

int Simulationsobjekt::p_iMaxID = 1;

Simulationsobjekt::Simulationsobjekt()
    : p_iID(p_iMaxID++), p_sName(""), p_dZeit(0.0) {
  cout << "Simulationsobjekt: Name - ID | " << p_sName << " - " << p_iID
       << " wurde erstellt." << endl;
}

Simulationsobjekt::Simulationsobjekt(string sName)
    : p_iID(p_iMaxID++), p_sName(sName), p_dZeit(0.0) {
  cout << "Simulationsobjekt: Name - ID | " << p_sName << " - " << p_iID
       << " wurde erstellt." << endl;
}

Simulationsobjekt::~Simulationsobjekt() {
  cout << "Simulationsobjekt: Name - ID | " << p_sName << " - " << p_iID
       << " wurde geloscht." << endl;
}

void Simulationsobjekt::vAusgeben(ostream &out) const {
  out << left << setw(5) << p_iID << setw(15) << p_sName;
}

ostream &operator<<(ostream &out, const Simulationsobjekt &obj) {
  obj.vAusgeben(out);
  return out;
}

Simulationsobjekt &
Simulationsobjekt::operator=(const Simulationsobjekt &other) {
  if (this == &other) {
    return *this;
  }
  this->p_sName = other.p_sName;
  this->p_dZeit = other.p_dZeit;
  return *this;
}

bool Simulationsobjekt::operator==(const Simulationsobjekt &other) const {
  return p_iID == other.p_iID;
}

std::string Simulationsobjekt::getName() const { return p_sName; }