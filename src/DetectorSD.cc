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


//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history )
{
   	// get energy in initial step
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

	//G4cout << "The step's particle ID:" << trackID << endl << endl;
	G4double edep = step->GetTotalEnergyDeposit();
	*(edepTotal.end() - 1) += edep;
	
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

