#include "Ex2G4DetectorConstruction.hh"
#include "Ex2G4DetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


Ex2G4DetectorConstruction::Ex2G4DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

Ex2G4DetectorConstruction::~Ex2G4DetectorConstruction()
{ }

G4VPhysicalVolume* Ex2G4DetectorConstruction::Construct()
{
    //create an instance of class which from we can get
    //standart materials
    G4NistManager* nist = G4NistManager::Instance();
    
    G4double det_sizeXY = 25*cm, tar_sizeZ = 0.001*mm, det_sizeZ = 0.15*cm;

    G4Material* det_mat = nist->FindOrBuildMaterial("G4_Au");

    G4bool checkOverlaps = true;

    G4double world_sizeXY = 30*cm;//Размер по x и y здесь будут одинаковы - ширина и высота
    G4double world_sizeZ  = 20*cm;//Размер по z - толщина
    // Выбор материала для мира из предопределенных в Geant4, для зала берем воздух
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    
    G4Box* solidWorld = 
    new G4Box("World",
            0.5*world_sizeXY,
            0.5*world_sizeXY,
            0.5*world_sizeZ
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
            0.5*det_sizeXY, 0.5*det_sizeXY, 0.5*det_sizeZ
    );

    G4LogicalVolume* logicDet = 
    new G4LogicalVolume(solidDet,
                        det_mat,
                        "Detector");

    new G4PVPlacement(0,
                    G4ThreeVector(0,0,5*cm),
                    logicDet,
                    "Detector",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

    G4Box* solidTar = 
    new G4Box ("Target",
                0.5*det_sizeXY, 0.5*det_sizeXY, 0.5*tar_sizeZ
    );

    G4LogicalVolume* logicTar = 
    new G4LogicalVolume(solidTar,
                        det_mat,
                        "Target");

    new G4PVPlacement(0,
                    G4ThreeVector(0,0,-5*cm),
                    logicTar,
                    "Target",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);


    return physWorld;
}

void Ex2G4DetectorConstruction::ConstructSDandField()
{
    G4String trackerChamberSDname = "Detector";
    Ex2G4DetectorSD* aTrackerSD = new Ex2G4DetectorSD(trackerChamberSDname);
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);

    SetSensitiveDetector("Detector", aTrackerSD, true);
}   