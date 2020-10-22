#include <G4VSensitiveDetector.hh>
#include <G4Types.hh>
#include <vector>

#ifndef DetectorSD_h
#define DetectorSD_h 1
class G4Step;
class G4TouchableHistory;
//class RunAction;
class DetectorSD: public G4VSensitiveDetector
	{
public :
	G4double X;
	G4double Z;
	G4double edepTotal;
	int k = 0;
	/*
	std::vector<G4double> X;
	std::vector<G4double> Z;
	std::vector<G4double> edepTotal;
	*/
public :
	    DetectorSD(G4String name );
	    ~DetectorSD();
		
	    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history );
private :
	};

#endif
