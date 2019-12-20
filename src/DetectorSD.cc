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
#include "RunAction.hh"

using namespace std;
// Конструктор чувствительной области, по умолчанию инициализируем нижнюю и верхнюю
// границы гистограммы в 0 и 200 ГэВ
DetectorSD::DetectorSD(G4String name): 
					G4VSensitiveDetector(name)
{
	vector<G4double>().swap(energies);
	vector<G4double>().swap(angles);
	vector<G4String>().swap(particles);
	vector<G4int>().swap(particleIDs);
	vector<G4double>().swap(dEs);
	vector<G4double>().swap(X);
	vector<G4double>().swap(Y); 
	vector<G4double>().swap(Z);
}
//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history )
{
   	// get energy in begin of step
	double energy = step->GetPreStepPoint()->GetKineticEnergy();

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
	G4ThreeVector pos = track->GetPosition();

	//get particle name of step
	//G4String const det_particle = step->GetTrack()->GetDefinition()->GetParticleName();
	
	//get dE of step
	G4double dE = step->GetDeltaEnergy();

	//G4cout << "The step's particle ID:" << trackID << endl << endl;


	if( (energy >=0.0) )
	{
	energies.push_back(energy);
	//angles.push_back(angle);
	//particles.push_back(det_particle);
	//particleIDs.push_back(trackID);
	dEs.push_back(dE);
	X.push_back(pos[0]);
	Y.push_back(pos[1]);
	Z.push_back(pos[2]);
	}
    
	return true;
}

DetectorSD::~DetectorSD()
{
	G4cout << " --- Program in destructor ~Ex2G4DetectorSD() --- " << G4endl ;
	//string date = get_time();
	ofstream file("spectrum.dat");
	file.precision(5);
	file << "Energy\t\t" << "dE\t\t" 
	     << "X\t\t" << "Y\t\t" << "Z\t\t" << endl << endl;
	int length = energies.size();
	for(int i = 0; i<length; i++)
	{
		file << energies[i]/MeV << "\t\t"
			<< dEs[i] << "\t\t"
			/*<< angles[i] << "\t\t"
			<< particles[i] << "\t\t"
		  	<< particleIDs[i] << "\t\t"
			*/
			<< X[i] << "\t\t"
	      		<< Y[i] << "\t\t"
			<< Z[i] << "\t\t" << endl ;
	}

	file.close();
}
