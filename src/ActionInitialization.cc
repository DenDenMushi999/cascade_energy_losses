#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{  }
//Деструктор, ничего не объявляли, поэтому оставим пустым
ActionInitialization::~ActionInitialization()
{  }
//Создание источника первичных частиц
void ActionInitialization::Build() const
{
    //Задается источник первичных частиц
	SetUserAction(new PrimaryGeneratorAction);
	// через обязательный класс ExG4PrimaryGeneratorAction01
}
