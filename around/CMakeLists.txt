# $Id: CMakeLists.txt 2018-01-08 14:39:15Z Виктор Гавриловец $
#CMakeList.txt, с его помощью собирается проект Geant4, файл основан на примере
#B1 входящим в исходники Geant4
#Как правило здесь настраивать ничего не надо

# Запуск проекта, проверка необходимой версии Cmake
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
# Название проекта
project(example2)

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
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Иногда возникает проблема, что не находит файлы проекта
# это потому, что у файлов исходников могут быть другие расширения, например

# file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
# file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

# Добавление исполняемого файла и линковка его с библиотеками Geant4
#
add_executable(example2 example2.cpp ${sources} ${headers})
target_link_libraries(example2 ${Geant4_LIBRARIES})

# Копирование скриптов в директорию сборки - туда, где мы собираем проект.
# Таким образом мы сможем запустить проект в директории сборки - текущей рабочей
# директории, что нужно например, при отладке.
#
set(EXAMPLE1_SCRIPTS
  run1.mac
  vis.mac
  )

foreach(_script ${EXAMPLE1_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

# Для внутеренего использования в Geant4, но не имеет влияния если проект
# компилируется для отдельного использования
#
add_custom_target(ex1 DEPENDS example2)

# Установка исполняемого файла в 'bin' директорию по пути
# установки CMAKE_INSTALL_PREFIX
#
install(TARGETS example2 DESTINATION bin)