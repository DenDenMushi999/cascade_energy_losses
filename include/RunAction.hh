#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//...oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class G4Run;
class RunAction : public G4UserRunAction
{
public:
	RunAction();
	virtual ~RunAction();
	std::vector<G4double> hist_energies;
	std::vector<G4double> hist_particles;
	std::vector<G4double> hist_angles;
	virtual void BeginOfRunAction(const G4Run* run);
	virtual void EndOfRunAction(const G4Run* run);
};

                  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
