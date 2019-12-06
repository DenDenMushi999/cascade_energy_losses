#ifndef CascadesG4PrimaryGeneratorAction_h
#define CascadesG4PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// Класс определения источника первичных частиц
class CascadesG4PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    CascadesG4PrimaryGeneratorAction();
    virtual ~CascadesG4PrimaryGeneratorAction();

    // Метод из базового класса, задает параметры источника начальных частиц
    virtual void GeneratePrimaries(G4Event*);

    // Метод для доступа к источнику частиц (пушке частиц ;) )
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun*  fParticleGun; // указатель на источник частиц
    // Временная переменная объема
    G4Box* fEnvelopeBox;
};
#endif
