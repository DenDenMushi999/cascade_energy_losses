#ifndef Ex2G4ActionInitialization_h
#define Ex2G4ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он должен наследоваться от
/// класса G4VUserActionInitialization

class Ex2G4ActionInitialization : public G4VUserActionInitialization
{
public :
	Ex2G4ActionInitialization();
	virtual ~Ex2G4ActionInitialization();
	virtual void Build() const;
};
#endif
