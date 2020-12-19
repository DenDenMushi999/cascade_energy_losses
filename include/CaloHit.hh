#ifndef CaloHit_h
#define CaloHit_h 1

#include <G4VHit.hh>
#include "G4THitsCollection.hh"

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
    void setStripNumber (const G4int copyNo ) { fStripNumber = copyNo; }

    G4double GetEdep () { return fEdep;}
    G4int GetStripNumber () { return fStripNumber; }

private :
    G4int gHitID;
    G4double fEdep;
    G4double fStripNumber; 
    //Then add X,Y, theta, phi

};

typedef G4THitsCollection<CaloHit> hitCollection;

#endif