#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4SDManager;
class DetectorSD;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public :
    DetectorConstruction();
    G4Material*  materCsI;
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    virtual void ConstructSDandField();

    int GetN_layers() { return n_layers; }
protected:
    //////////// Default sizes and variables ////////////////////////////////
    G4bool checkOverlaps = true;
    
    //G4double CFRP_width = 0.4*mm
    //G4double edgeCFRP_width = 3*mm;
    /*
    const int n_layers = 22;
    G4double det_sizeXZ = 80*cm, det_sizeY = 25*cm;

    G4double world_sizeXY = 120*cm; //Размер по x и y здесь будут одинаковы - ширина и высота
    G4double world_sizeZ  = 80*cm; //Размер по z - толщина

    G4double strip_sizeXY = 36*mm;
    G4double strip_sizeZ = 296*mm;

    //G4double airSpace = 0.05*mm;
    G4double tungstenWidth = 0.1*mm;
    */
    //////////////////////////////////////////////////////////////////////////
};
#endif
