#include "CascadesG4DetectorConstruction.hh"
#include "CascadesG4DetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


CascadesG4DetectorConstruction::CascadesG4DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

CascadesG4DetectorConstruction::~CascadesG4DetectorConstruction()
{ }

G4VPhysicalVolume* CascadesG4DetectorConstruction::Construct()
{
    //create an instance of class which from we can get
    //standart materials
    G4NistManager* nist = G4NistManager::Instance();
    
    G4double det_sizeXZ = 80*cm, det_sizeY = 25*cm;

    G4Material* det_mat = nist->FindOrBuildMaterial("G4_Au");

    G4bool checkOverlaps = true;

    G4double world_sizeXZ = 120*cm; //Размер по x и y здесь будут одинаковы - ширина и высота
    G4double world_sizeY  = 80*cm; //Размер по z - толщина
    // Выбор материала для мира из предопределенных в Geant4, для зала берем воздух
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    
    G4Box* solidWorld = 
    new G4Box("World",
            0.5*world_sizeXZ,
            0.5*world_sizeXZ,
            0.5*world_sizeY
    );

    G4LogicalVolume* logicWorld = 
    new G4LogicalVolume(solidWorld,
                        world_mat,
                        "World"
    );

    G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,
                        G4ThreeVector(),
                        logicWorld,
                        "World",
                        0,
                        false,
                        0,
                        checkOverlaps);

    G4Box* solidDet = 
    new G4Box ("Detector",
            0.5*det_sizeXZ, 0.5*det_sizeXZ, 0.5*det_sizeY
    );

    G4LogicalVolume* logicDet = 
    new G4LogicalVolume(solidDet,
                        det_mat,
                        "Detector");

    new G4PVPlacement(0,
                    G4ThreeVector(0, -det_sizeY/2, 0),
                    logicDet,
                    "Detector",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);


    return physWorld;
}

void CascadesG4DetectorConstruction::ConstructSDandField()
{
    G4String trackerChamberSDname = "Detector";
    CascadesG4DetectorSD* aTrackerSD = new CascadesG4DetectorSD(trackerChamberSDname);
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);

    SetSensitiveDetector("Detector", aTrackerSD, true);
}   