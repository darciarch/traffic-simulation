#pragma once
#include "Simulationsobjekt.h"
#include "Weg.h"
#include <list>
#include <memory>

class Fahrzeug;
class PKW;

class Kreuzung : public Simulationsobjekt {
public:
  Kreuzung(std::string sName, double dTankstelle);
  virtual ~Kreuzung();

  static void vVerbinde(std::shared_ptr<Kreuzung> k1,
                        std::shared_ptr<Kreuzung> k2, std::string sNameHin,
                        std::string sNameRueck, double dLaenge,
                        Tempolimit eLimit);
  void vVerbinde(std::shared_ptr<Weg> pWeg);
  void vTanken(Fahrzeug &fFahrzeug);
  void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit);
  void vSimulieren() override;
  void vAusgeben(std::ostream &out) const override;
  std::shared_ptr<Weg> pZufaelligerWeg(Weg &weg); // hangi yoldan geldik
  std::list<std::shared_ptr<Weg>> getWege() const;
  double getTankstelle() const;

private:
  std::list<std::shared_ptr<Weg>> p_pWege; // list of all roads
  double p_dTankstelle;
};
