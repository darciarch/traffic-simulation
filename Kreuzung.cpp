#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <iostream>
#include <random>

using namespace std;

Kreuzung::Kreuzung(string sName, double dTankstelle)
    : Simulationsobjekt(sName), p_dTankstelle(dTankstelle) {}

Kreuzung::~Kreuzung() {}

void Kreuzung::vVerbinde(shared_ptr<Weg> pWeg) { p_pWege.push_back(pWeg); }

void Kreuzung::vVerbinde(std::shared_ptr<Kreuzung> k1,
                         std::shared_ptr<Kreuzung> k2, std::string sNameHin,
                         std::string sNameRueck, double dLaenge,
                         Tempolimit eLimit) {

  // Erzeuge die Wege, gebe Zielkreuzung im Konstruktor mit
  // Hinweg: Ziel ist k2
  std::shared_ptr<Weg> hin =
      std::make_shared<Weg>(sNameHin, dLaenge, eLimit, k2);

  // Rückweg: Ziel ist k1
  std::shared_ptr<Weg> rueck =
      std::make_shared<Weg>(sNameRueck, dLaenge, eLimit, k1);

  // Yollar birbirinin dönüşü olduğunu öğreniyor
  hin->setRueckweg(rueck);
  rueck->setRueckweg(hin);

  // Yolları kavşakların listesine ekliyor
  k1->vVerbinde(hin);
  k2->vVerbinde(rueck);
}

void Kreuzung::vTanken(Fahrzeug &fFahrzeug) {
  if (p_dTankstelle > 0) {

    double dGetankt = fFahrzeug.dTanken();
    p_dTankstelle -= dGetankt;

    if (p_dTankstelle < 0) {
      p_dTankstelle = 0;
    }
  }
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug,
                        double dStartzeit) {
  vTanken(*pFahrzeug);
  // eger liste bos degilse
  if (!p_pWege.empty()) {
    p_pWege.front()->vAnnahme(std::move(pFahrzeug), dStartzeit);
  }
}

void Kreuzung::vSimulieren() {
  for (auto &weg : p_pWege) {
    weg->vSimulieren();
  }
}

void Kreuzung::vAusgeben(ostream &out) const {
  Simulationsobjekt::vAusgeben(out);
  out << " " << p_dTankstelle << "L";
  for (auto &weg : p_pWege) {
    out << endl << "    ";
    weg->vAusgeben(out);
  }
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg &weg) {
  if (p_pWege.empty()) {
    return nullptr;
  }
  auto rueckweg = weg.getRueckweg();

  // adaylari ekle listeye haci abi
  std::vector<std::shared_ptr<Weg>> candidates;
  for (auto &w : p_pWege) {
    if (w != rueckweg) {
      candidates.push_back(w);
    }
  }

  // Sackgasse (cikmaz sokak) check
  if (candidates.empty()) {
    // Checking if rueckweg is actually in p_pWege (validity check)
    for (auto &w : p_pWege) {
      if (w == rueckweg)
        return w;
    }

    // program cökmesin diye
    // If even return way isn't there (weird), return first one
    return p_pWege.front();
  }

  // Random selection
  static std::mt19937 device(0);
  std::uniform_int_distribution<int> dist(0, candidates.size() - 1);
  return candidates[dist(device)];
}

std::list<std::shared_ptr<Weg>> Kreuzung::getWege() const { return p_pWege; }

double Kreuzung::getTankstelle() const { return p_dTankstelle; }
