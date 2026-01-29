#pragma once
#include "Simulationsobjekt.h"
#include <iostream>
#include <string>

extern double dGlobaleZeit;
extern double inf;

class Verhalten;
class Weg;

class Fahrzeug : public Simulationsobjekt {
protected:
  double p_dMaxGeschwindigkeit;
  double p_dGesamtStrecke;    // total distance traveled
  double p_dAbschnittStrecke; // distance traveled in current weg
  double p_dGesamtZeit;       // for the object
  std::unique_ptr<Verhalten>
      p_pVerhalten; // nesnenin Fahren mi Parken mi yaptigini
                    //  programa gösterir, her bir nesne icin ayri ayri degisir

public:
  Fahrzeug();
  Fahrzeug(std::string sName);
  Fahrzeug(std::string sName, double dMaxGeschwindigkeit);
  Fahrzeug(const Fahrzeug &) = delete;
  virtual ~Fahrzeug();

  static void vKopf();
  virtual void vAusgeben(std::ostream &o) const override;
  virtual void vSimulieren() override;
  virtual double dTanken(double dMenge = inf);
  virtual void vNeueStrecke(Weg *pWeg); // Fahrzeug enters a new Weg (Driving)
  virtual void
  vNeueStrecke(Weg *pWeg,
               double dStartzeit); // Fahrzeug enters a new Weg (Parking)
  virtual double dGeschwindigkeit() const;
  virtual void vZeichnen(const Weg &weg) const;
  double getAbschnittStrecke() const;

  bool operator<(const Fahrzeug &fahrzeug) const;
  void operator=(const Fahrzeug &Fahrzeug);
};