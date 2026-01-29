#pragma once
#include <iostream>
#include <string>

// Type& -> Reference alias
// &obj -> address of obj

class Simulationsobjekt {
protected:
  std::string p_sName;
  const int p_iID;
  double p_dZeit; // last updated simulation time
  static int p_iMaxID;

public:
  Simulationsobjekt();
  Simulationsobjekt(std::string sName);
  Simulationsobjekt(const Simulationsobjekt &) = delete; // Disable copy
  virtual ~Simulationsobjekt();

  virtual void vAusgeben(std::ostream &out) const;
  virtual void vSimulieren() = 0; // Pure virtual
  virtual std::string getName() const;

  Simulationsobjekt &operator=(const Simulationsobjekt &other);
  bool operator==(const Simulationsobjekt &other) const;
};

std::ostream &operator<<(std::ostream &out, const Simulationsobjekt &obj);