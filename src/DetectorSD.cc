
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <G4Types.hh>
#include "G4SystemOfUnits.hh"

#include <G4Step.hh>
#include "G4ThreeVector.hh"
#include "DetectorSD.hh"
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"

#include "get_time.hh"

#define PI 3.14159265     

using namespace std;

DetectorSD::DetectorSD(G4String name)
	: G4VSensitiveDetector(name)
{
	G4cout << "\n\n ------- The program in constructor of DetectorSD ------- " << G4endl << G4endl ; 
}


//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history )
{
   	// get energy in initial step
	auto PreStepPoint = step->GetPreStepPoint(); 
	G4double energy = PreStepPoint->GetKineticEnergy();

	////////////////////// First method of analising Hit ///////////////////////// 
	/*
	if ( energy > 99995)  //condition of detect an initial position of particle
	{
		//G4cout << "particle detected!" << endl ;
		//Write to file a previous values

		G4Track* const track = step->GetTrack();
		G4ThreeVector pos = track->GetPosition();
		G4ThreeVector dir = track->GetMomentumDirection();
		double angle = atan(dir[0]/dir[1])*180/PI;
		X = pos[0];
		Z = pos[2];

		G4cout << "\n ---------     New event ! " << n_event << " , X = " << X <<" , Z = " << Z 
		<< " , theta = " << angle << " deg    --------- " << G4endl;

		ofstream file("center_angles.dat", ios::app);
	    if (file.is_open())
			{
				file<< edepTotal << "  "
					<< X << "  "
					<< Z << "  "
					<< angle
					<< endl;
		}
		file.close();

		n_event+=1;

		edepTotal = 0.0;
		G4double edep = step->GetTotalEnergyDeposit();
		edepTotal += edep;
		
		//G4cout << "\n ---------    New Run! " << edepTotal.size() << " , X = "<< pos[0] << " , Z = " << pos[2] 
		//<< " ----------" << G4endl;
		
		/*edepTotal.push_back(0.);
		X.push_back(pos[0]);
		Z.push_back(pos[2]);
	}
	else 
	{
		//store edep until new particle launched

		// Get number of cell where step is
		G4int copyNo = PreStepPoint->GetPhysicalVolume()->GetCopyNo();
		G4int strip_i = copyNo / n_layers;
		G4int strip_j = copyNo % n_layers;

		//add edep to according strip 
		G4double edep = step->GetTotalEnergyDeposit();
		totalEdepStrips[strip_i][strip_j] += edep;
	}
	*/
	///////////////////////////////////////////////////////////////////////////

	//////////////// second method of hit handling. Now I use G4VHit class///////////////////////////////

	CaloHit* hit = new CaloHIt()

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//G4cout << "The step"s particle ID:" << trackID << endl << endl;
	//*(edepTotal.end() - 1) += edep;
	
	return true;
}

DetectorSD::~DetectorSD()
{
	///*
	G4cout << " --- Program in destructor ~Ex2G4DetectorSD() --- " << G4endl ;
	//string date = get_time();
	/*
	ofstream file("spectrum3.dat");

	int length = edepTotal.size();
	for(int i = 0; i<length; i++)
	{
		file << edepTotal[i] << "  "
			 << X[i] << "  "
			 << Z[i]
			 << endl;
	}
	file.close();
	
	*/
}

