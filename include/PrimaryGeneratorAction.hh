#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;
class G4GeneralParticleSource;

/// Класс определения источника первичных частиц
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    // Метод из базового класса, задает параметры источника начальных частиц
    virtual void GeneratePrimaries(G4Event*);

    // Метод для доступа к источнику частиц (пушке частиц ;) )
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

 // private:
 //   G4GeneralParticleSource * InitializeGPS();
  private:
    G4ParticleGun*  fParticleGun; // указатель на источник частиц
    
    //G4GeneralParticleSource* GPSgun;
    
    // Временная переменная объема
    G4Box* fEnvelopeBox;
};
#endif
