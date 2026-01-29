#include "Weg.h"
#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include <iomanip>
#include <iostream>

using namespace std;

Weg::Weg() : Simulationsobjekt() {}

Weg::Weg(string sName, double dLaenge, Tempolimit eTempolimit,
         std::weak_ptr<Kreuzung> pZielKreuzung)
    : Simulationsobjekt(sName), p_dLange(dLaenge), p_eTempolimit(eTempolimit),
      p_pZielKreuzung(pZielKreuzung) {}

Weg::~Weg() {}

double Weg::getTempolimit() const {
  switch (p_eTempolimit) {
  case Tempolimit::Innerorts:
    return 50.0;
  case Tempolimit::Landstrasse:
    return 100.0;
  case Tempolimit::Autobahn:
    return std::numeric_limits<double>::max();
  }
}

double Weg::getLange() const { return p_dLange; }

void Weg::vSimulieren() {
  p_pFahrzeuge.vAktualisieren();
  for (auto &p : p_pFahrzeuge) {
    try {
      p->vSimulieren();
    } catch (const Fahrausnahme &e) {
      e.vBearbeiten();
    }
  }
  p_pFahrzeuge.vAktualisieren();
}

void Weg::vAusgeben(std::ostream &o) const {
  Simulationsobjekt::vAusgeben(o);
  o << ": " << std::setw(12) << p_dLange << " ( ";
  for (const auto &p : p_pFahrzeuge) {
    o << p->getName() << " ";
  }
  o << ")";
}

void Weg::vKopf() {
  cout << left << setw(4) << "ID" << " | " << setw(10) << "Name" << " | "
       << setw(12) << "Lange" << " | " << "Fahrzeuge" << endl;

  cout << setfill('-') << setw(60) << "" << setfill(' ') << '\n';
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug) {
  pFahrzeug->vNeueStrecke(this);
  p_pFahrzeuge.push_back(std::move(pFahrzeug));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit) {
  pFahrzeug->vNeueStrecke(this, dStartzeit);
  p_pFahrzeuge.push_front(std::move(pFahrzeug));
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug &aFzg) {
  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
    if (*it != nullptr && **it == aFzg) {
      // sahipliği (unique_ptr) listeden alıp yerel bir değişkene tasi.
      // listedeki o eleman nullptr olur.
      std::unique_ptr<Fahrzeug> pBulunanFzg = std::move(*it);

      // Boş kalan (nullptr olan) elemanı listeden silmek için işaretle
      p_pFahrzeuge.erase(it);

      // Bulunan aracı (sahipliğiyle birlikte) geri döndür.
      return pBulunanFzg;
    }
  }
  return nullptr;
}

void Weg::vZeichnen() const {
  for (const auto &p : p_pFahrzeuge) {
    p->vZeichnen(*this);
    // *this suanda icinde bulundugumuz objenin kendisi
    // yildiz solda -> dereferance
    // yildiz sagda gibi bir durum yok (carpan operatörü)
  }
}

void Weg::setRueckweg(std::weak_ptr<Weg> weg) { p_pRueckweg = weg; }

std::shared_ptr<Weg> Weg::getRueckweg() const { return p_pRueckweg.lock(); }

// lock() make weak_ptr to shared_ptr (if it still survives)
// if it doesn't survive, return nullptr
std::shared_ptr<Kreuzung> Weg::getZielKreuzung() const {
  return p_pZielKreuzung.lock();
}