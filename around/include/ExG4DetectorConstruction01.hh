#ifndef ExG4DetectorConstruction01_h
#define ExG4DetectorConstruction01_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// \brief The ExG4DetectorConstruction01 class Класс геометрии установки,
///  объявление материалов и детекторов

class ExG4DetectorConstruction01 : public G4VUserDetectorConstruction
{
  public:
    //Конструктор, вызывается при создании экземпляра класса
    //Обычно используется для задания начальных значений и значений по умолчанию
    //при создании геометрии и материалов
    ExG4DetectorConstruction01();
    //Деструктор, вызывается при удалении экземпляра класса
    //Обычно используется для освобождения памяти инициализированных массивов внутри класса
    virtual ~ExG4DetectorConstruction01();
    //Объявление и создание детекторов и среды
    virtual G4VPhysicalVolume* Construct();
    //Установка чувствительного объема. Когда частица в нем, то в нем извлекается
    //вся информация о треке и параметрах частицы на каждом шаге моделирования
    virtual void ConstructSDandField();
    private:
  
  G4int fNofLayers;
  
  protected:
  
};
#endif