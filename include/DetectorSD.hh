#ifndef DetectorSD_h
#define DetectorSD_h 1

#include <G4VSensitiveDetector.hh>
#include <G4Types.hh>

#include "Constants.hh"
#include "CaloHit.hh"

#include <vector>

#include "globals.hh"


class G4Step;
class G4TouchableHistory;

//class RunAction;
class DetectorSD: public G4VSensitiveDetector
{
public :
	    DetectorSD(G4String SDname);
	    ~DetectorSD();
		
		void Initialize (G4HCofThisEvent* kHCEvent);
	    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history );
		void EndOfEvent (G4HCofThisEvent* kHCEvent);
		void addTotal ( G4double);

private :
	//G4double totalEdepStripes[n_layers][n_layers];
	//std::vector<G4double> X_event;
	//std::vector<G4double> Y_event;
	G4double eventEdepTotal;
	G4THitsCollection<CaloHit>* gHitCollection;
	G4int fCollectionID = -1; // -1 for initializing variable in Initialize
	G4int n_event = -1;
};

#endif
