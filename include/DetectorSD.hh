
#ifndef DetectorSD_h
#define DetectorSD_h 1

#include <G4VSensitiveDetector.hh>
#include "Constants.hh"
#include <G4Types.hh>

#include <vector>

#include "globals.hh"


class G4Step;
class G4TouchableHistory;

//class RunAction;
class DetectorSD: public G4VSensitiveDetector
	{
public :
	    DetectorSD(G4String name);
	    ~DetectorSD();
		
	    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history );
private :
	//G4double totalEdepStripes[n_layers][n_layers];
	//std::vector<G4double> X_event;
	//std::vector<G4double> Y_event;
	G4double eventEdepTotal;
	n_event = 0;
	};

#endif
