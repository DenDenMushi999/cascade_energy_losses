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

#ifndef G4UI_USE
#include "UIterminal.hh"
#endif

int main(int argc, char** argv)
{
    G4RunManager* runManager = new G4RunManager;
    
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new QGSP_BERT_HP());
    runManager->SetUserInitialization(new ActionInitialization());
    runManager->Initialize();

   
    //uncomment this to apply visualization
    /*
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
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
    
    }
    else  
    {
        // Если были переданы параметры, то включаем пакетный режим
        G4String command = "/control/execute ";//Записываем в строковую переменную
        // команду выполнить
        G4String fileName = argv[1];//Имя файла из командной строки при запуске проекта
        // Мы считаем, что первым параметром было передано имя файла с командами для запуска
        // проекта в пакетном режиме
        UImanager->ApplyCommand(command+fileName);//Выполнение команды
    }
    */

    /*
    G4UIsession* session = new G4UIterminal;
    session->SessionStart();
    delete session;
    */

    //launch macrofile
    ///*
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4String command = "/control/execute " ;
    G4String fileName = "run3.mac" ;
    UImanager->ApplyCommand(command+fileName);
    //*/

    delete runManager;
    return 0;
}
