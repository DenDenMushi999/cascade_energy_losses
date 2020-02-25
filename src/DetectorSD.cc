#include <G4Step.hh>
#include <fstream>
#include <iostream>
#include <vector>
#include <G4Types.hh>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "DetectorSD.hh"
#include "get_time.hh"
#include "G4RunManager.hh"

using namespace std;
// Конструктор чувствительной области, по умолчанию инициализируем нижнюю и верхнюю
// границы гистограммы в 0 и 200 ГэВ
DetectorSD::DetectorSD(G4String name)
	: G4VSensitiveDetector(name)
{
	G4cout << "\n\n ------- The program in constructor of DetectorSD ------- " << G4endl << G4endl ; 
}

/*
void DetectorSD::append_energy(G4double E )
{   
	energies.push_back(E);	
}
void DetectorSD::append_dE(G4double dE )
{   
	dEs.push_back(dE);  
}  
void DetectorSD::append_edep(G4double edep )
{	edeps.push_back(edep);  }  
void DetectorSD::append_ID(G4int ID )
{   IDs.push_back(ID);   }  
void DetectorSD::incr_edep(G4double edep)
{   edepTotal += edep;  } 
void DetectorSD::incr_dE(G4double dE)
{   dEtotal += dE;   }
*/

//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history )
{
   	// get energy in begin of step
	G4double energy = step->GetPreStepPoint()->GetKineticEnergy();
	
	if ( energy > 99995) 
	{
		G4Track* const track = step->GetTrack();
		G4ThreeVector pos = track->GetPosition();
		G4cout << "\n ---------    New Run! " << edepTotal.size() << " , X = "<< pos[0] << " , Z = " << pos[2] 
		<< " ----------" << G4endl;
		edepTotal.push_back(0.);
		X.push_back(pos[0]);
		Z.push_back(pos[2]);
	}	

	//get angle in begin of step
	/*G4ThreeVector ang = step->GetPreStepPoint()->GetMomentumDirection();
	G4ThreeVector *centerVector = new G4ThreeVector(0,-1,0);
	double angle = ang.angle(*centerVector);
	*/

	// get trackID to differ particles with each other
	
	/*
	G4Track* const track = step->GetTrack();
	G4int trackID = track->GetTrackID();
	*/

	//get position
	//G4ThreeVector pos = track->GetPosition();

	//get particle name of step
	//G4String const det_particle = step->GetTrack()->GetDefinition()->GetParticleName();
	
	//get dE of step
	/*
	G4double dE = step->GetDeltaEnergy();
	dEtotal += dE ;
	*/

	//G4cout << "The step's particle ID:" << trackID << endl << endl;
	G4double edep = step->GetTotalEnergyDeposit();
	*(edepTotal.end()-1) += edep;

	/*
	runaction->append_energy(energy);
	runaction->append_dE(dE);
	runaction->append_edep(edep);
	//angles.push_back(angle);
	//particles.push_back(det_particle);
	runaction->append_particleID(trackID);
	runaction->incr_dE(dE);
	runaction->incr_edep(edep);
	//X.push_back(pos[0]);
	//Y.push_back(pos[1]);
	//Z.push_back(pos[2]);
    */

	/*
    energies.push_back(energy);
    dEs.push_back(dE);
    edeps.push_back(edep);
    IDs.push_back(trackID);
    dEtotal += dE;
	*/
	
	return true;
}

DetectorSD::~DetectorSD()
{
	///*
	G4cout << " --- Program in destructor ~Ex2G4DetectorSD() --- " << G4endl ;
	//string date = get_time();
	ofstream file("spectrum.dat");

	int length = edepTotal.size();
	for(int i = 0; i<length; i++)
	{
		file << edepTotal[i] << "  "
			 << X[i] << "  "
			 << Z[i]
			 << endl;
	}
	file.close();
	//*/
}

