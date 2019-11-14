#ifndef Ex2G4DetectorConstruction_h
#define Ex2G4DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class Ex2G4DetectorConstruction : public G4VUserDetectorConstruction
{
public :
    Ex2G4DetectorConstruction();

    virtual ~Ex2G4DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    virtual void ConstructSDandField();
protected:
};
#endif
