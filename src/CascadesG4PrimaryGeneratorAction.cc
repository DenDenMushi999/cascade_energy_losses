#include "CascadesG4PrimaryGeneratorAction.hh"
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
CascadesG4PrimaryGeneratorAction::CascadesG4PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fEnvelopeBox(0)
{
    fParticleGun  = new G4ParticleGun(0);
    GPSgun = InitializeGPS();    
}

// Деструктор
CascadesG4PrimaryGeneratorAction::~CascadesG4PrimaryGeneratorAction()
{
    // удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
    delete fParticleGun;
    delete GPSgun;
}

G4GeneralParticleSource* CascadesG4PrimaryGeneratorAction::InitializeGPS()
 {
   G4GeneralParticleSource * gps = new G4GeneralParticleSource();
   
   // setup details easier via UI commands see gps.mac
 
   // particle type
   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   G4ParticleDefinition* optPhoton = particleTable->FindParticle("mu-");  
   gps->GetCurrentSource()->SetParticleDefinition(optPhoton);
 
   // set energy distribution
   G4SPSEneDistribution *eneDist = gps->GetCurrentSource()->GetEneDist() ;
   eneDist->SetEnergyDisType("Mono"); // or gauss
   eneDist->SetMonoEnergy(3.*GeV);
 
   // set position distribution
   G4SPSPosDistribution *posDist = gps->GetCurrentSource()->GetPosDist();
   posDist->SetPosDisType("Point");  // or Point,Plane,Volume,Beam
   posDist->SetCentreCoords(G4ThreeVector(0.0*cm,0.0*cm,-13.0*cm));
 
   // set angular distribution
   G4SPSAngDistribution *angDist = gps->GetCurrentSource()->GetAngDist();
   angDist->SetParticleMomentumDirection( G4ThreeVector(0., 0., 1.) );
 
   return gps;
}

void CascadesG4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //Эта функция вызывается в начале каждого первичного события запуска частицы
    // Для избежания зависимости этого класса от класса DetectorConstruction,
    // мы получаем ссылку на объем детектора через класс G4LogicalVolumeStore
    G4double envSizCascadesXZ = 0;
    G4double envSizeY = 0;
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
      envSizCascadesXZ = fEnvelopeBox->GetXHalfLength()*2.;
      envSizeY = fEnvelopeBox->GetYHalfLength()*2.;
    }
    else  {//Если ссылка на fEnvelopeBox пустая, выдаем предупреждение
      G4ExceptionDescription msg;
      msg << "Envelope volume of box shape not found.\n";
      msg << "Perhaps you have changed geometry.\n";
      msg << "The gun will be place at the center.";
      G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
       "MyCode0002",JustWarning,msg);
    }
    // Объявляем переменные положения пушки частиц
    G4double x0 = 0;
    G4double y0 = 10*cm;
    G4double z0 = 0;
    // Устанавливаем положение
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    // Генерируем первичное событие
    fParticleGun->GeneratePrimaryVertex(anEvent);
    GPSgun->GeneratePrimaryVertex(anEvent);
}
