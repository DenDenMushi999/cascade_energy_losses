#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh"

// include mandatory header files
#include "DetectorConstruction.hh"
#include "QGSP_BERT_HP.hh"
#include "ActionInitialization.hh"

//#ifdef G4UI_USE //Если используется интерфейс пользователя то включаем визуализацию
#include "G4VisExecutive.hh"//Визуализация
#include "G4UIExecutive.hh"//Выбор соответствующего интерфейса пользователя
//#endif

#include <G4UIterminal.hh>
#include <cmath>

#include <G4Types.hh>
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"


int main(int argc, char** argv)
{
	
	// Construct the default run manager
	//
//#ifdef G4MULTITHREADED
//	G4MTRunManager* runManager = new G4MTRunManager;
//#else
	G4RunManager* runManager = new G4RunManager;
//#endif
	
	int n_events = 1000;
	// This line enable to send comands in program
    G4UImanager* UImanager = G4UImanager::GetUIpointer();


    runManager->SetUserInitialization(new QGSP_BERT_HP());
    DetectorConstruction* detConstruction = new DetectorConstruction();
    runManager->SetUserInitialization(detConstruction);
    runManager->SetUserInitialization(new ActionInitialization());
	runManager->Initialize();

	UImanager->ApplyCommand("/control/execute macros/start_setup.mac");

	/////////// Launch particle with angles from 0 to pi/4 with step pi/36 /////////
	/*
	for (double angle= M_PI/36; angle <= M_PI/4; angle+= M_PI/36)
	{

		G4cout << "angle = " << angle << "\n" ;
		UImanager->ApplyCommand("/gun/particle/e-");
		UImanager->ApplyCommand("/gun/energy/100 GeV");
		UImanager->ApplyCommand("gun/position 0 0 0 cm");
		std::string direction = "gun/direction " + std::to_string(sin(angle)) + " " +std::to_string(-cos(angle)) + " 0" ;
		UImanager->ApplyCommand(direction);
		UImanager->ApplyCommand("run/beamOn 1000");
	}
	*/
	////////// end of launch //////////////
	
	
	//runManager->BeamOn(n_events);
	
	
	////////////// Open Terminal /////////////////////////
	/*
	G4UIsession* session = new G4UIterminal;
	session->SessionStart();
	delete session;
	*/
	///////////// end of open Terminal ///////////////////////
	

	// Checking what a Geant4_DATASETS variable containes
	#ifdef Geant4_DATASETS
		G4cout << G4endl << Geant4_DATASETS << G4endl;
	#else
		G4cout << "The project has no datasets" << G4endl;
	#endif

	
	//////////// Turning on Visualisation ///////////////
	/*
	G4VisManager* visManager = new G4VisExecutive;
	// Инициализация менеджера визуализации
	visManager->Initialize();
	// Получение указателя на менеджера взаимодействия с пользователем
	// Проверяем или были переданы через командную сроку параметры
	if ( argc == 1 ) { //Если через командную строку ничего не передавалось
		// То устанавливаем  интерактивный режим
		// Если используется визуализация
		#ifdef G4UI_USE
		G4UIExecutive* ui = new G4UIExecutive(argc, argv);//Создание интерфейса пользователя
		UImanager->ApplyCommand("/control/execute vis.mac");//Отрисовываем по заранее подготовленному
		// файлу vis.mac
		ui->SessionStart();//Запуск интерфейса пользователя
		delete ui;//Удаление интерфейса пользователя
		#endif
	}
	else {
		// Если были переданы параметры, по включаем пакетный режим
		G4String command = "/control/execute ";//Записываем в строковую переменную
		// команду выполнить
		G4String fileName = argv[1];//Имя файла из командной строки при запуске проекта
		// Мы считаем, что первым параметром было передано имя файла с командами для запуска
		// проекта в пакетном режиме
		UImanager->ApplyCommand(command+fileName);//Выполнение команды
	delete visManager;
	}
	*/
	/////////// end of Visualisation /////////////

	
	/////////// B1-versioin of Process macro or start UI session /////////
	
	G4VisManager* visManager = new G4VisExecutive;
	// G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
	// G4VisManager* visManager = new G4VisExecutive("Quiet");
	visManager->Initialize();
	G4UIExecutive* ui = 0;
	if ( argc == 1 ) {
		ui = new G4UIExecutive(argc, argv);
	}
	if ( ! ui ) {
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else { 
		// interactive mode
		UImanager->ApplyCommand("/control/execute macros/init_vis.mac");
		ui->SessionStart();
		delete ui;
  	}
	delete visManager;
	
	/////////// end //////////////////////////////////

    delete runManager;
    return 0;
}
