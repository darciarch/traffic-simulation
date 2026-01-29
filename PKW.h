#pragma once
#include "Fahrzeug.h"

extern double inf;

class PKW : public Fahrzeug {

private:
  double p_dVerbrauch;
  double p_dTankVolumen;
  double p_dTankinhalt;

public:
  PKW(std::string sName, double dGeschwindigkeit, double dVerbrauch,
      double dTankVolumen = 55.0);
  ~PKW();

  double dTanken(double dMenge = inf) override;
  double dGeschwindigkeit() const override;
  void vSimulieren() override;
  void vAusgeben(std::ostream &o) const override;
  void vZeichnen(const Weg &weg) const override;
};