#pragma once
#include "Simulationsobjekt.h"
#include "vertagt_liste.h"
#include <iostream>
#include <list>
#include <memory>

#include "Tempolimit.h"
#include <limits>

class Fahrzeug; // forward declaration
class Kreuzung; // forward declaration

class Weg : public Simulationsobjekt {
public:
  static void vKopf();
  void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug); // Araci yola kabul eder

  void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit);
  std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug &fzg);
  Weg();

  Weg(std::string sName, double dLaenge,
      Tempolimit eTempolimit = Tempolimit::Autobahn,
      std::weak_ptr<Kreuzung> pZielKreuzung = std::weak_ptr<Kreuzung>());
  // son satirdaki default parameter

  virtual ~Weg();

  virtual void vSimulieren() override;
  virtual void vAusgeben(std::ostream &o) const override;
  void vZeichnen() const;
  double getTempolimit() const;
  double getLange() const;

  // weak_ptr cünkü yol cift seritli
  // ters yönlü yol
  void setRueckweg(std::weak_ptr<Weg> weg);
  std::shared_ptr<Weg> getRueckweg() const;
  std::shared_ptr<Kreuzung> getZielKreuzung() const;

protected:
  double p_dLange; // total length of weg
  vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
  Tempolimit p_eTempolimit;
  std::weak_ptr<Weg> p_pRueckweg;
  const std::weak_ptr<Kreuzung> p_pZielKreuzung;
};