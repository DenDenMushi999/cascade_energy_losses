#include "PrimaryGeneratorAction.hh"
// Подключаем необходимы заголовочные файлы
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

// Класс, в котором описывается положение, тип, энергия, направление вылета
// и распределение начальных частиц
PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fEnvelopeBox(0)
{
  G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle);
}

// Деструктор
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    // удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent )
{
    /*
    G4double envSizeCascadesXY = 0;
    G4double envSizeZ = 0;
    // Проверяем, не пустая ли ссылка на fEnvelopeBox
    if (!fEnvelopeBox)
    {
       // Если пустая, то получаем ссылку на объем детектора
      G4LogicalVolume* envLV
        = G4LogicalVolumeStore::GetInstance()->GetVolume("Detector");
      if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
    }
    // Получаем размеры объема, стороны по x и y предполагается что одинаковы
    if ( fEnvelopeBox ) {
      envSizeCascadesXY = fEnvelopeBox->GetXHalfLength()*2.;
      envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
    }
    else  {//Если ссылка на fEnvelopeBox пустая, выдаем предупреждение
      G4ExceptionDescription msg;
      msg << "Envelope volume of box shape not found.\n";
      msg << "Perhaps you have changed geometry.\n";
      msg << "The gun will be place at the center.";
      G4Exception("PrimaryGeneratorAction::GeneratePrimaries()",
       "MyCode0002",JustWarning,msg);
    }
    */

    ///////// Set 100 Gev electrons ///////////////////
    
    /*
    G4int n_particle = 1;
    G4ParticleGun* fParticleGun  = new G4ParticleGun(n_particle);
    */
    
    /*
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle
        = particleTable->FindParticle(particleName="e-");
    fParticleGun->SetParticleDefinition(particle);
    
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    //fParticleGun->SetParticlePosition(G4ThreeVector(0.,0., -30.*cm));
    fParticleGun->SetParticleEnergy(100.*GeV);
    */
   
    fParticleGun->GeneratePrimaryVertex(anEvent);
    
    /////////  end of set ////////////////////////////////////
    
    //GPSgun->GeneratePrimaryVertex(anEvent);
}
