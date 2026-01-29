#pragma once
#include "Weg.h"

class Fahrzeug;

extern double dGlobaleZeit;

class Verhalten {
public:
  Verhalten(Weg &weg);
  virtual ~Verhalten() = default;

  virtual double dStrecke(Fahrzeug &aFzg, double dZeitIntervall) = 0;
  virtual Weg &getWeg() const;

protected:
  Weg &p_Weg;
};

class Fahren : public Verhalten {
public:
  Fahren(Weg &weg);
  virtual ~Fahren() = default;

  virtual double dStrecke(Fahrzeug &aFzg, double dZeitIntervall) override;
};

class Parken : public Verhalten {
public:
  Parken(Weg &weg, double dStartzeitpunkt);
  virtual ~Parken() = default;

  virtual double dStrecke(Fahrzeug &aFzg, double dZeitIntervall) override;

private:
  double p_dStartzeitpunkt; // Starttime of the parked object
};
