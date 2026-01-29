#pragma once
#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {

public:
  Fahrrad(std::string sName, double MaxGeschwindigkeit);
  double dGeschwindigkeit() const override;
  void vAusgeben(std::ostream &o) const override;
  void vZeichnen(const Weg &weg) const override;
};