#include "G4RunManager.hh"
#include "G4UImanager.hh"

// include mandatory header files
#include "Ex2G4DetectorConstruction.hh"
#include "FTFP_BERT.hh"
#include "Ex2G4ActionInitialization.hh"


#ifdef G4UI_USE //Если используется интерфейс пользователя то включаем визуализацию
#include "G4VisExecutive.hh"//Визуализация
#include "G4UIExecutive.hh"//Выбор соответствующего интерфейса пользователя
#endif


int main(int argc, char** argv)
{
    G4RunManager* runManager = new G4RunManager;

    runManager->SetUserInitialization(new Ex2G4DetectorConstruction());
    runManager->SetUserInitialization(new FTFP_BERT());
    runManager->SetUserInitialization(new Ex2G4ActionInitialization());
    runManager->Initialize();

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
        // Если были переданы параметры, по включаем пакетный режим
        G4String command = "/control/execute ";//Записываем в строковую переменную
        // команду выполнить
        G4String fileName = argv[1];//Имя файла из командной строки при запуске проекта
        // Мы считаем, что первым параметром было передано имя файла с командами для запуска
        // проекта в пакетном режиме
        UImanager->ApplyCommand(command+fileName);//Выполнение команды
    }

    delete runManager;
    return 0;
}
