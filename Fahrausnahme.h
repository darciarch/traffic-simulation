#pragma once

#include <exception>
#include <string>

class Fahrzeug;
class Weg;

class Fahrausnahme : public std::exception {
public:
  Fahrausnahme(Fahrzeug &fahrzeug, Weg &weg);
  virtual ~Fahrausnahme() = default;

  virtual void vBearbeiten() const = 0; // pure virtual function
  // = 0 demek zorunlu override edilmeli demek

protected:
  Fahrzeug &p_pFahrzeug;
  Weg &p_pWeg;
};

// Losfahren = harekete gecmek
class Losfahren : public Fahrausnahme {
public:
  Losfahren(Fahrzeug &fahrzeug, Weg &weg);
  virtual void vBearbeiten() const override;
};

class Streckenende : public Fahrausnahme {
public:
  Streckenende(Fahrzeug &fahrzeug, Weg &weg);
  virtual void vBearbeiten() const override;
};
