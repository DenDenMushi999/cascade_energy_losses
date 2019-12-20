#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
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
    //DetectorSD* aTrackerSD;
    
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    virtual void ConstructSDandField();
protected:
};
#endif
