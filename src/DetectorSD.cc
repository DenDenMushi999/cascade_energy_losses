
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <G4Types.hh>
#include "G4SystemOfUnits.hh"

#include <G4Step.hh>
#include "G4ThreeVector.hh"
#include "G4RunManager.hh"

#include "DetectorConstruction.hh"
#include "DetectorSD.hh"
#include "CaloHit.hh"

#include "get_time.hh"

#define PI 3.14159265     

using namespace std;

DetectorSD::DetectorSD(G4String SDname)
	: G4VSensitiveDetector(SDname)
{
	G4cout << "\n\n ------- The program in constructor of DetectorSD ------- " << G4endl << G4endl ; 
	collectionName.insert(SDname);
}


void DetectorSD::Initialize( G4HCofThisEvent* kHCEvent )
{
	gHitCollection = new G4THitsCollection<CaloHit>(SensitiveDetectorName, collectionName[0]);
 
   /* To insert the collection, we need to get an unique ID for it */
   if(fCollectionID<0) fCollectionID = GetCollectionID(0); // <<-- this is to get an ID for collectionName[0]
 
   /* add the info into the collection */
   kHCEvent->AddHitsCollection(fCollectionID, gHitCollection);
}

//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* )
{
   	// get energy in initial step
	auto PreStepPoint = step->GetPreStepPoint(); 

	////////////////////// First method of analising Hit ///////////////////////// 
	/*
	G4double energy = PreStepPoint->GetKineticEnergy();
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
					<< G4endl;
		}
		file.close();

		n_event+=1;

		edepTotal = 0.0;
		G4double edep = step->GetTotalEnergyDeposit();
		edepTotal += edep;
		
		//G4cout << "\n ---------    New Run! " << edepTotal.size() << " , X = "<< pos[0] << " , Z = " << pos[2] 
		//<< " ----------" << G4endl;
		
		//edepTotal.push_back(0.);
		//X.push_back(pos[0]);
		//Z.push_back(pos[2]);
		
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
		eventEdepTotal[strip_i][strip_j] += edep;
	}
	*/
	///////////////////////////////////////////////////////////////////////////

	//////////////// second method of hit handling. Now I use G4VHit class///////////////////////////////
	
	G4double edep = step->GetTotalEnergyDeposit();
	G4int copyNo = PreStepPoint->GetPhysicalVolume()->GetCopyNo();

	CaloHit* hit = new CaloHit( fCollectionID );

	hit->setEdep( edep );
	hit->setStripNumber ( copyNo ); 
	gHitCollection->insert(hit);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//G4cout << "The step"s particle ID:" << trackID << G4endl << G4endl;
	// *(edepTotal.end() - 1) += edep;
	
	return true;
}

void DetectorSD::EndOfEvent(G4HCofThisEvent*)
{
	/////////////////// Write to new file for each event ////////////////////////
	
	//auto runManager = new G4RunManager();
	//G4int n = runManager->GetNumberOfEventsToBeProcessed();	
	string date = get_time();
	string filename;
	if (n_event>-1) 
	{
		n_event++;
		G4cout << "End of " << n_event << " event" << G4endl ; 
		filename = "Test_HC" + to_string(n_event) + ".dat";
	}
	else 
	{
		n_event=0;
		G4cout << "\n----- Number of event is not correct so set it manually to 0----- " << G4endl; 
		G4cout << "End of " << n_event << " event " << G4endl ; 
		filename = "Test_HC" + to_string(n_event) + ".dat";
	}
	
	ofstream file(filename);
	
	
	for (auto hit : *(gHitCollection->GetVector()) ) //Yeah, that's it seems right
	{
		file << hit->GetEdep() / MeV << " "
			 << hit->GetStripNumber() 
			 << G4endl;
	}

	/*
	file << "\n" << "--------------------" << "--------------------\n" 
		<< "--------------------" << "--------------------\n"
		<< "--------------------" << "--------------------\n" << G4endl;
	*/

	file.close();
	
	////////////////////////////////////////////////////////////////////////////

	
}

DetectorSD::~DetectorSD()
{
	///*
	G4cout << " --- Program in destructor ~DetectorSD() --- " << G4endl ;
	//string date = get_time();
	/*
	ofstream file("spectrum3.dat");

	int length = edepTotal.size();
	for(int i = 0; i<length; i++)
	{
		file << edepTotal[i] << "  "
			 << X[i] << "  "
			 << Z[i]
			 << G4endl;
	}
	file.close();
	
	*/
}

