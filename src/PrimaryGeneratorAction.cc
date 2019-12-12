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
    //create a gun with 1 particle
    fParticleGun  = new G4ParticleGun(1);
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    // Ищем частицу, в нашем случае протон
    G4ParticleDefinition* particle
        = particleTable->FindParticle(particleName="e-");
    // Устанавливаем полученную частицу в качестве испускаемого типа начальных частиц в источнике
    fParticleGun->SetParticleDefinition(particle);
    // Устанавливаем направление движение частицы по (x,y,z)
    // Здесь устанавливается направление вдоль оси Z
    fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0,-1.0,0.0));
    // Установка начальной энергии испускаемых частиц, 50 МэВ
    fParticleGun->SetParticleEnergy(100*GeV);  
}

// Деструктор
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    // удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
    delete fParticleGun;
    delete GPSgun;
}

G4GeneralParticleSource* PrimaryGeneratorAction::InitializeGPS()
 {
   G4GeneralParticleSource * gps = new G4GeneralParticleSource();
   return gps;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //Эта функция вызывается в начале каждого первичного события запуска частицы
    // Для избежания зависимости этого класса от класса DetectorConstruction,
    // мы получаем ссылку на объем детектора через класс G4LogicalVolumeStore
    G4double envSizeCascadesXZ = 0;
    G4double envSizeY = 0;
    // Проверяем, не пустая ли ссылка на fEnvelopeBox
    if (!fEnvelopeBox)
    {
       // Если пустая, то получаем ссылку на объем детектора
      G4LogicalVolume* envLV
        = G4LogicalVolumeStore::GetInstance()->GetVolume("Detector");
      if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
    }
    // Получаем размеры объема, стороны по x и z предполагается что одинаковы
    if ( fEnvelopeBox ) {
      envSizeCascadesXZ = fEnvelopeBox->GetXHalfLength()*2.;
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
    fParticleGun->GeneratePrimaryVertex(anEvent);
    //GPSgun->GeneratePrimaryVertex(anEvent);
}
