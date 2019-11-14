#include "Ex2G4ActionInitialization.hh"
#include "Ex2G4PrimaryGeneratorAction.hh"

Ex2G4ActionInitialization::Ex2G4ActionInitialization()
 : G4VUserActionInitialization()
{}
//Деструктор, ничего не объявляли, поэтому оставим пустым
Ex2G4ActionInitialization::~Ex2G4ActionInitialization()
{
	
}
//Создание источника первичных частиц
void Ex2G4ActionInitialization::Build() const
{
SetUserAction(new Ex2G4PrimaryGeneratorAction);//Задается источник первичных частиц
// через обязательный класс ExG4PrimaryGeneratorAction01
}
