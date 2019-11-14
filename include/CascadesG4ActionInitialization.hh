#ifndef CascadesG4ActionInitialization_h
#define CascadesG4ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он должен наследоваться от
/// класса G4VUserActionInitialization

class CascadesG4ActionInitialization : public G4VUserActionInitialization
{
public :
	CascadesG4ActionInitialization();
	virtual ~CascadesG4ActionInitialization();
	virtual void Build() const;
};
#endif
