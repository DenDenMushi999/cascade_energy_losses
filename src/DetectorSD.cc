#include <G4Step.hh>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <G4Types.hh>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "DetectorSD.hh"
#include "get_time.hh"
#include "G4RunManager.hh"
#define PI 3.14159265     

using namespace std;
// Конструктор чувствительной области, по умолчанию инициализируем нижнюю и верхнюю
// границы гистограммы в 0 и 200 ГэВ
DetectorSD::DetectorSD(G4String name)
	: G4VSensitiveDetector(name)
{
	G4cout << "\n\n ------- The program in constructor of DetectorSD ------- " << G4endl << G4endl ; 
}


//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history )
{
   	// get energy in initial step
	G4double energy = step->GetPreStepPoint()->GetKineticEnergy();

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

		G4cout << "\n ---------     New run ! " << k << " , X = " << X <<" , Z = " << Z 
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

		k+=1;

		edepTotal = 0.0;
		G4double edep = step->GetTotalEnergyDeposit();
		edepTotal += edep;
		
		//G4cout << "\n ---------    New Run! " << edepTotal.size() << " , X = "<< pos[0] << " , Z = " << pos[2] 
		//<< " ----------" << G4endl;
		
		/*edepTotal.push_back(0.);
		X.push_back(pos[0]);
		Z.push_back(pos[2]);
		*/
	}
	else 
	{
		//store edep until new particle launched
		G4double edep = step->GetTotalEnergyDeposit();
		edepTotal += edep;
	}

	//G4cout << "The step's particle ID:" << trackID << endl << endl;
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

