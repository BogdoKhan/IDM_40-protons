
#ifndef ExG4DetectorSD_h
#define ExG4DetectorSD_h 1

#include "ExG4PrimaryGeneratorAction02.hh"

#include<G4VSensitiveDetector.hh>

#include "ExG4DetectorHit.hh"


#include <vector>
class G4Step;
class G4HCofThisEvent;

/// Calorimeter sensitive detector class
///
/// In Initialize(), it creates one hit for each calorimeter layer and one more
/// hit for accounting the total quantities in all layers.
///
/// The values are accounted in hits in ProcessHits() function which is called
/// by Geant4 kernel at each step.

class ExG4DetectorSD : public G4VSensitiveDetector
{
  public:
    ExG4DetectorSD(const G4String& name, 
                     const G4String& hitsCollectionName, 
                     G4int nofCells);
    virtual ~ExG4DetectorSD();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);
	
	
  private:
  	
    ExG4DetectorHitsCollection* fHitsCollection;
    G4int  fNofCells;
	
	private:
	// static const int NOBINS = 250;
      const double HIST_MAX;
     const double HIST_MIN;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif



//   class G4Step;
//   class G4TouchableHistory;
   /// Класс определения чувствительной области детектора
 //  class ExG4DetectorSD: public G4VSensitiveDetector
  //   {
   //  private:
       //Создадим гистограмму в которую запишем распределение
       //энергии протонов
       //Число бинов (интервалов в гистограмме)
    //   static const int NOBINS = 1000;
       //Максимальная энергия в гистограмме
     //  const double HIST_MAX;
       //Минимальная энергия в гистограмме
     //  const double HIST_MIN;
       //Объявляем саму гистограмму
     //  int histogram[NOBINS];
       //Постоим также угол, на который рассеялся протон
      // int histogram_angle[NOBINS];
	   //counter
	//   int counter;
	 //  private:
   // ExG4DetectorHitsCollection* fHitsCollection;
   // G4int  fNofCells;
    // public:
       //Контструктора, в нем обнуляем гистограммы
     //   ExG4DetectorSD(G4String name);
        //Декструктор, в нем выведем гистограммы в файл
        //Вывод данных в файл лучше делать здесь чем в ProcessHits, так как
        //вызов деструктора происходит в конце работы программы,
        //а если записывать в процессе моделирования, то значительное
        //время будет тратится на ожидание записи в файл. А это относительно
        //медленная процедура и занимает много времени и в результате
        //моделирование будет занимать больше времени чем нужно.
   //     ~ExG4DetectorSD();
        //Когда частица попадает в этот чувствительный объем, тогда на каждом
        //её шаге моделирования вызывается эта функция.
        //В ней мы можем получить и передать информацию о состоянии
        //частицы, и ее треке
	//	 virtual void   Initialize(G4HCofThisEvent* hitCollection);
   // virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
   // virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);
   //  };
//#endif /* SENSITIVEDETECTOR */