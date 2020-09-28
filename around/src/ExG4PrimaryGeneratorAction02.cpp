#include<fstream>
#include<iostream>
#include "ExG4PrimaryGeneratorAction02.hh"
// Подключаем необходимы заголовочные файлы
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"

	

// Класс, в котором описывается положение, тип, энергия, направление вылета
// и распределение начальных частиц
int numb = 0;
const G4String ExG4PrimaryGeneratorAction02::fgkDefaultParticleName = "gamma";
const G4double ExG4PrimaryGeneratorAction02::fgkDefaultEnergy = 19.8*MeV;
ExG4PrimaryGeneratorAction02::ExG4PrimaryGeneratorAction02()
  : G4VUserPrimaryGeneratorAction(),
    fGeneralParticleSource(0),
	fEnvelopeBox(0)
{
  fGeneralParticleSource  = new G4GeneralParticleSource();
}



ExG4PrimaryGeneratorAction02::~ExG4PrimaryGeneratorAction02()
{
  delete fGeneralParticleSource;
}


void ExG4PrimaryGeneratorAction02::GeneratePrimaries(G4Event* anEvent)
{
  //Эта функция вызывается в начале каждого первичного события запуска частицы
  // Для избежания зависимости этого класса от класса DetectorConstruction,
  // мы получаем ссылку на объем детектора через класс G4LogicalVolumeStore

  //G4double envSizeX = 0;
  //G4double envSizeY = 0;
  //G4double envSizeZ = 0;
  // Проверяем или ссылка на fEnvelopeBox пустая
  //if (!fEnvelopeBox)
 // {
     // Если пустая, то получаем ссылку на объем детектора
  //  G4LogicalVolume* envLV
 //     = G4LogicalVolumeStore::GetInstance()->GetVolume("Target");
 //   if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
 // }
  // Получаем размеры объема, стороны по x и y предполагается что одинаковы
 // if ( fEnvelopeBox ) {
 //   envSizeX = fEnvelopeBox->GetXHalfLength()*2.;
 //   envSizeY = fEnvelopeBox->GetYHalfLength()*2.;
 //   envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
 // }
 // else  {//Если ссылка на fEnvelopeBox пустая, выдаем предупреждение
  //  G4ExceptionDescription msg;
  ///  msg << "Envelope volume of box shape not found.\n";
  //  msg << "Perhaps you have changed geometry.\n";
   // msg << "The gun will be place at the center.";
 //   G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
   //  "MyCode0002",JustWarning,msg);
 // }
  // Объявляем переменные положения пушки части
  G4double x0 = 0;
  G4double y0 = 0;
  G4double z0 = 10.*cm;
  // Устанавливаем положение
  fGeneralParticleSource->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  // Генерируем первичное событие
	fGeneralParticleSource->GeneratePrimaryVertex(anEvent);
	numb += 1;
	std::ofstream filea1("number.dat", std::ios::trunc);
    	filea1 << std::setw(15) << numb << std::endl;
	filea1.close();
}
