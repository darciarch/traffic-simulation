#include "Verhalten.h"
#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <iostream>

Verhalten::Verhalten(Weg &weg) : p_Weg(weg) {}

Weg &Verhalten::getWeg() const { return p_Weg; }

// Fahren Implementation
Fahren::Fahren(Weg &weg) : Verhalten(weg) {}

double Fahren::dStrecke(Fahrzeug &aFzg, double dZeitIntervall) {
  double dPossibleDistance = aFzg.dGeschwindigkeit() * dZeitIntervall;
  double dRemainingDistance = p_Weg.getLange() - aFzg.getAbschnittStrecke();

  if (dRemainingDistance < 0.000001) { // Epsilon check
    throw Streckenende(aFzg, p_Weg);
  }

  if (dPossibleDistance > dRemainingDistance) {
    return dRemainingDistance;
  } else {
    return dPossibleDistance;
  }
}

Parken::Parken(Weg &weg, double dStartzeitpunkt)
    : Verhalten(weg), p_dStartzeitpunkt(dStartzeitpunkt) {}

double Parken::dStrecke(Fahrzeug &aFzg, double dZeitIntervall) {
  if (dGlobaleZeit < p_dStartzeitpunkt) {
    return 0.0; // Still parking
  } else {
    if (dGlobaleZeit - dZeitIntervall < p_dStartzeitpunkt) {
      throw Losfahren(aFzg, p_Weg);
    }
    return 0.0;
  }
}
