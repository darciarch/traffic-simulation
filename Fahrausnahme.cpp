#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Weg.h"
#include <iomanip>
#include <iostream>

extern double dGlobaleZeit;

using namespace std;

Fahrausnahme::Fahrausnahme(Fahrzeug &fahrzeug, Weg &weg)
    : p_pFahrzeug(fahrzeug), p_pWeg(weg) {}

Losfahren::Losfahren(Fahrzeug &fahrzeug, Weg &weg)
    : Fahrausnahme(fahrzeug, weg) {}

void Losfahren::vBearbeiten() const {
  cout << "Exception: Losfahren | Fahrzeug: " << p_pFahrzeug.getName()
       << " | Weg: " << p_pWeg.getName() << endl;
  cout << "Fahrzeug " << p_pFahrzeug.getName() << " on road "
       << p_pWeg.getName() << " is starting off." << endl;
  p_pFahrzeug.vNeueStrecke(&p_pWeg);
}

Streckenende::Streckenende(Fahrzeug &fahrzeug, Weg &weg)
    : Fahrausnahme(fahrzeug, weg) {}

void Streckenende::vBearbeiten() const {
  cout << "Exception: Streckenende | Fahrzeug: " << p_pFahrzeug.getName()
       << " | Weg: " << p_pWeg.getName() << endl;
  cout << "Fahrzeug " << p_pFahrzeug.getName() << " on road "
       << p_pWeg.getName() << " has reached the end of the road." << endl;

  auto pZielKreuzung = p_pWeg.getZielKreuzung();
  if (pZielKreuzung) {
    pZielKreuzung->vTanken(p_pFahrzeug);
    auto pNeuerWeg = pZielKreuzung->pZufaelligerWeg(p_pWeg);
    // zufällig = random

    cout << "ZEIT : " << dGlobaleZeit << endl;
    cout << "KREUZUNG : " << pZielKreuzung->getName() << " "
         << pZielKreuzung->getTankstelle() << endl;
    cout << "WECHSEL : " << p_pWeg.getName() << " -> " << pNeuerWeg->getName()
         << endl;
    cout << "FAHRZEUG : " << p_pFahrzeug << endl;

    auto pFzgPtr = p_pWeg.pAbgabe(p_pFahrzeug);
    pNeuerWeg->vAnnahme(std::move(pFzgPtr));

  } else {
    p_pWeg.pAbgabe(p_pFahrzeug);
  }
}
