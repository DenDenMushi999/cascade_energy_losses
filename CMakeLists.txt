
#CMakeList.txt, с его помощью собирается проект Geant4, файл основан на примере
#B1 входящим в исходники Geant4
#Как правило здесь настраивать ничего не надо

# Запуск проекта, проверка необходимой версии Cmake
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
# Название проекта
project(Cascade)

# Поиск пакетов Geant4, включение всех доступных интерфейсов пользователя
# (Qt, GAG, tcsh, csh) и драйверов визуализации по умолчанию.
# Можно использовать переменную окружения WITH_GEANT4_UIVIS, установить в OFF (выключено)
# через командную строку или с помощью ccmake/cmake-gui для сборки проекта только в
# пакетном режимом
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Подключение директорий  из Geant4
# Подключение директорий проекта
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Расположение искодного кода и заголовочных файлов этого проекта
# Заголовочные файлы подключаются, значит что они будут показаны в
# IDE - среде разработки
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Иногда возникает проблема, что не находит файлы проекта
# это потому, что у файлов исходников могут быть другие расширения, например

# file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
# file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

# Добавление исполняемого файла и линковка его с библиотеками Geant4
#
add_executable(cascades cascades.cc ${sources} ${headers})
target_link_libraries(cascades ${Geant4_LIBRARIES})

# Копирование скриптов в директорию сборки - туда, где мы собираем проект.
# Таким образом мы сможем запустить проект в директории сборки - текущей рабочей
# директории, что нужно например, при отладке.
#
set(CASCADES_SCRIPTS
  run1.mac
  run2.mac
  run3.mac
  center_angles.mac
  beam_1000.mac
  beam_Zline.mac
  beam_Xline.mac
  GPSgun.g4mac
  loop.mac
  loop_Zline.mac
  loop_Xline.mac
  X_bias.mac
  Z_bias.mac
  vis.mac
  init_vis.mac
  )

# There are specified directories where to bring files from( I argument in configure_file)
# and where to put them (II argument). 
# Here scripts are searching in ${PROJECT_SOURCE_DIR}/macros folder
# and are placing in ${PROJECT_BINARY_DIR}/macros directory

foreach(_script ${CASCADES_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/macros/${_script}
    ${PROJECT_BINARY_DIR}/macros/${_script}
    COPYONLY
    )
endforeach()

source_group("Test_folder" FILES ${FILES_TO_ADD})

# Для внутеренего использования в Geant4, но не имеет влияния если проект
# компилируется для отдельного использования
#
add_custom_target(Cascade DEPENDS cascades)

# Установка исполняемого файла в 'bin' директорию по пути
# установки CMAKE_INSTALL_PREFIX
#
install(TARGETS cascades DESTINATION bin)
