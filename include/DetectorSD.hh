#include <G4VSensitiveDetector.hh>
#include <G4Types.hh>
#include <vector>

#ifndef DetectorSD_h
#define DetectorSD_h 1
	class G4Step;
        class G4TouchableHistory;
	class DetectorSD: public G4VSensitiveDetector
	{
private :
	std::vector<G4double> energies;
	std::vector<G4double> angles;
	std::vector<G4String> particles;
	std::vector<G4int> particleIDs;
	std::vector<G4double> dEs;
	std::vector<G4double> X;
	std::vector<G4double> Y;
	std::vector<G4double> Z;

public :
	    DetectorSD(G4String name);
	    ~DetectorSD();

	    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history );
	};
#endif
