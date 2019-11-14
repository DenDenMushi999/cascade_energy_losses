#include "CascadesG4ActionInitialization.hh"
#include "CascadesG4PrimaryGeneratorAction.hh"

CascadesG4ActionInitialization::CascadesG4ActionInitialization()
 : G4VUserActionInitialization()
{}
//Деструктор, ничего не объявляли, поэтому оставим пустым
CascadesG4ActionInitialization::~CascadesG4ActionInitialization()
{
	
}
//Создание источника первичных частиц
void CascadesG4ActionInitialization::Build() const
{
SetUserAction(new CascadesG4PrimaryGeneratorAction);//Задается источник первичных частиц
// через обязательный класс ExG4PrimaryGeneratorAction01
}
