#include <G4Step.hh>
#include <fstream>
#include <iostream>
#include <vector>
#include <G4Types.hh>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "CascadesG4DetectorSD.hh"

using namespace std;
// Конструктор чувствительной области, по умолчанию инициализируем нижнюю и верхнюю
// границы гистограммы в 0 и 50 МэВ
CascadesG4DetectorSD::CascadesG4DetectorSD(G4String name): 
					G4VSensitiveDetector(name)
{
	// Обнуляем гистограммы
    vector<G4double>().swap(energies);
    vector<G4double>().swap(angles);
    vector<G4String>().swap(particles);
}
//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool CascadesG4DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
	// Получаем кинетическую энергии частицы с предыдущего шага, т.е. начальную
	// кинетическую энегрию перед текущим шагом
	double energy = step->GetPreStepPoint()->GetKineticEnergy();
    
    G4ThreeVector ang = step->GetPreStepPoint()->GetMomentumDirection();
    G4ThreeVector *centerVector = new G4ThreeVector(0,0,1);
    double angle=ang.angle(*centerVector);
    // Так как у нас измеряются углы между векторами, то максимальный
    // угол равен пи/2 , минимальный -0
    G4String const det_particle = step->GetTrack()->GetDefinition()->GetParticleName();

	if( (energy >=0.0 && energy < 50*MeV) && (angle >=0.0 && angle < 1.5707) )
    {
        energies.push_back(energy);
        angles.push_back(angle);
        particles.push_back(det_particle);
    }

	step->GetTrack()->SetTrackStatus(fStopAndKill);
    return true;
}

CascadesG4DetectorSD::~CascadesG4DetectorSD()
{
	ofstream file("spectrum.dat");

    file << "Energy\t\t" << " " << "angle\t\t" << "particle" << endl << endl;
    int length = energies.size();
	for(int i = 0; i<length; i++)
    {
        file << energies[i]/MeV << "\t\t"
             << angles[i] << "\t\t"
             << particles[i] << std::endl;
    }

    // Закрываем файл
    file.close();
}
