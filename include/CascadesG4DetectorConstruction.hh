#ifndef CascadesG4DetectorConstruction_h
#define CascadesG4DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class CascadesG4DetectorConstruction : public G4VUserDetectorConstruction
{
public :
    CascadesG4DetectorConstruction();

    virtual ~CascadesG4DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    virtual void ConstructSDandField();
protected:
};
#endif
