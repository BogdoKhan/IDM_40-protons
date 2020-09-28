#ifndef ExG4ActionInitialization01_h
#define ExG4ActionInitialization01_h 1

#include "G4VUserActionInitialization.hh"

/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он должен наследоваться от
/// класса G4VUserActionInitialization

class ExG4ActionInitialization01 : public G4VUserActionInitialization
{
  public:
    ExG4ActionInitialization01();//Конструктор
    virtual ~ExG4ActionInitialization01();//Деструктор
    virtual void Build() const;//Создание источника первичных частиц

};
#endif