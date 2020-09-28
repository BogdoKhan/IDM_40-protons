#include "ExG4ActionInitialization01.hh"
#include "ExG4PrimaryGeneratorAction02.hh"//Подключаем обязательный класс
//в котором описываются источник начальных частиц

/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он должен наследоваться от
/// класса G4VUserActionInitialization

/// Конструктор
ExG4ActionInitialization01::ExG4ActionInitialization01()
 : G4VUserActionInitialization()
{}
//Деструктор, ничего не объявляли, поэтому оставим пустым
ExG4ActionInitialization01::~ExG4ActionInitialization01()
{}
//Создание источника первичных частиц
void ExG4ActionInitialization01::Build() const
{
SetUserAction(new ExG4PrimaryGeneratorAction02);//Задается источник первичных частиц
// через обязательный класс ExG4PrimaryGeneratorAction01
}