#ifndef CaloHit_h
#define CaloHit_h 1

#include <G4VHit.hh>
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"

#include "globals.hh"
#include <G4Types.hh>

class CaloHit : public G4VHit
{
public :
    CaloHit( const G4int kHitIDnumber);
    ~CaloHit(  );
    void Print();
    void Draw();

public :
    void setEdep (const G4double E ) { fEdep = E; }
    //void setStripNumber (const G4int copyNo ) { fStripNumber = copyNo; }
    void setCoords (const G4ThreeVector pos ) { fX = pos[0]; fY = pos[1]; fZ = pos[2]; }

    G4double GetEdep () { return fEdep;}
    G4ThreeVector GetCoords() { return G4ThreeVector(fX, fY, fZ); }
    //G4int GetStripNumber () { return fStripNumber; }

private :
    G4int fHitID;
    G4double fEdep;
    //G4double fStripNumber; 
    //Then add X,Y, theta, phi
    G4double fX;
    G4double fY;
    G4double fZ;
};

typedef G4THitsCollection<CaloHit> hitCollection;

#endif