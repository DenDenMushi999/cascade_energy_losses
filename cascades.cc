#include "G4RunManager.hh"
#include "G4UImanager.hh"

// include mandatory header files
#include "DetectorConstruction.hh"
#include "QGSP_BERT_HP.hh"
#include "ActionInitialization.hh"

#ifdef G4UI_USE //Если используется интерфейс пользователя то включаем визуализацию
#include "G4VisExecutive.hh"//Визуализация
#include "G4UIExecutive.hh"//Выбор соответствующего интерфейса пользователя
#endif

#include <G4UIterminal.hh>

int main(int argc, char** argv)
{
    G4RunManager* runManager = new G4RunManager;
    
    runManager->SetUserInitialization(new QGSP_BERT_HP());
    DetectorConstruction* detConstruction = new DetectorConstruction();
    runManager->SetUserInitialization(detConstruction);
    runManager->SetUserInitialization(new ActionInitialization());
	runManager->Initialize();

   
    //uncomment this to apply visualization
	/*   
    G3VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
	*/	
    
	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	
	/*
	// Проверяем или были переданы через командную сроку параметры
	if ( argc == 1 ) 
    {
    //Если через командную строку ничего не передавалось
    // То устанавливаем  интерактивный режим
    // Если используется визуализация
		#ifdef G4UI_USE
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);//Создание интерфейса пользователя
        UImanager->ApplyCommand("/control/execute vis.mac");//Отрисовываем по заранее подготовленному
        // файлу vis.mac
        ui->SessionStart();//Запуск интерфейса пользователя
        delete ui;//Удаление интерфейса пользователя
        #endif
	*/
	if (argc != 1) 
    {
		//if have more than 1 parameter, execute this argument (macrofile)
	    G4String command = "/control/execute" ;
        
		//The first parameter in main is macrofile
		G4String fileName = argv[1];
       
        UImanager->ApplyCommand(command+fileName);
    }
    

	//
	
    G4UIsession* session = new G4UIterminal;
    session->SessionStart();
	delete session;
	

    delete runManager;
    return 0;
}
