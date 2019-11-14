#include <G4VSensitiveDetector.hh>
#include <G4Types.hh>
#include <vector>

#ifndef CascadesG4DetectorSD_h
#define CascadesG4DetectorSD_h 1
	class G4Step;
	class G4TouchableHistory;

	class CascadesG4DetectorSD: public G4VSensitiveDetector
	{
	private :
	    std::vector<G4double> energies;
	    std::vector<G4double> angles;
	    std::vector<G4String> particles;
	public :
	    CascadesG4DetectorSD(G4String name);
	    ~CascadesG4DetectorSD();

	    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	};
#endif