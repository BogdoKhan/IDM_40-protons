#include "ExG4DetectorConstruction01.hh"
#include "ExG4DetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"

#include "G4Element.hh"


ExG4DetectorConstruction01::ExG4DetectorConstruction01()
: G4VUserDetectorConstruction(),
fNofLayers(-1)
{ }

ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{ }

G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{
    fNofLayers = 1;
    
  	G4NistManager* nist = G4NistManager::Instance();

   	//Materials
	G4Material* polystyr_mat = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
	G4Material* fluoro_mat = nist->FindOrBuildMaterial("G4_TEFLON");
    G4Material* steel_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4Material* air_mat = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
	
	//Build TiD of the target
	G4Element* Ti = nist->FindOrBuildElement(22);

	G4int iz, n, ncomponents, natoms; //iz=number of protons  in an isotope;
                                      // n=number of nucleons in an isotope;                                  
	G4double abundance, a, density;                                     

	G4Isotope* H = new G4Isotope("protium", iz=1, n=1, a=1.00783*g/mole);
	G4Isotope* D = new G4Isotope("deuterium", iz=1, n=2, a=2.0141*g/mole);

	G4Element* Du  = new G4Element("Deuterium", "D", ncomponents=2);
	Du->AddIsotope(H, abundance= 10.*perCent);
	Du->AddIsotope(D, abundance= 90.*perCent);
	
	 G4Material* TiD_mat = 
	 new G4Material("TiD", density= 1.78*g/cm3, ncomponents=2);
	 TiD_mat->AddElement(Du, natoms=17);
	 TiD_mat->AddElement(Ti, natoms=10);
	 TiD_mat->SetChemicalFormula("Ti_D");
	
	G4bool checkOverlaps = true;
	
	//Rotation matrix
	G4Rep3x3 rottemp(-1,0,0, 
					  0,1,0, 
					  0,0,1);
	G4RotationMatrix* rotm = new G4RotationMatrix(rottemp);
	
	//World size
	G4double world_sizeX = 70*cm;
	G4double world_sizeY = 70*cm;  
	G4double world_sizeZ = 70*cm;

	//World
	G4Box* solidWorld =
	new G4Box("World",                       
	   0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);    
	
	
	G4LogicalVolume* logicWorld =
	new G4LogicalVolume(solidWorld,          
						world_mat,           
						"World");            
	
	G4VPhysicalVolume* physWorld =
	new G4PVPlacement(0,                     
					  G4ThreeVector(),       
					  logicWorld,            
					  "World",               
					  0,                     
					  false,                 
					  0,                     
					  checkOverlaps);
	
	
	//Target chamber steel tube
	G4Tubs* solidTube =
	new G4Tubs("Tube", 
			   8.9*cm, 9.*cm, 13.85*cm, 0.*deg, 360.*deg);

	G4LogicalVolume* logicTube =
	new G4LogicalVolume(solidTube,            
						steel_mat,            
						"Tube");         
	
	new G4PVPlacement(rotm,                   
					G4ThreeVector(0.*cm,0.,1.85*cm),
					logicTube,               
					"Tube",                
					logicWorld,            
					false,                 
					0,                       
					checkOverlaps);
	
	
	//Vacuum chamber big steel lid
	G4Tubs* solidLid =
	new G4Tubs("Lid", 
			   8.9*cm, 30.*cm, 1.*cm, 0.*deg, 360.*deg);

	G4LogicalVolume* logicLid =
	new G4LogicalVolume(solidLid,
						steel_mat,            
						"Lid");         

	new G4PVPlacement(rotm,                      
					G4ThreeVector(0.*cm,0.,-13*cm),
					logicLid,              
					"Lid",               
					logicWorld,           
					false,                   
					0,                      
					checkOverlaps);
	
	 //Target chamber steel lid
	G4Tubs* solidLidTb =
	new G4Tubs("LidT", 
			   0*cm, 11.*cm, 1.*cm, 0.*deg, 360.*deg);

	G4LogicalVolume* logicLidTb =
	new G4LogicalVolume(solidLidTb,           
						steel_mat,             
						"LidT");         

	new G4PVPlacement(rotm,                       
					G4ThreeVector(0.*cm,0., 16.7*cm), 
					logicLidTb,                
					"LidT",                
					logicWorld,              
					false,                   
					0,                       
					checkOverlaps);
	
	//TARGET_FILAMENT
	G4Tubs* solidTar =
	new G4Tubs("Target", 
			   0.*cm, 48.5*mm, 25.*um, 0.*deg, 360.*deg);

	G4LogicalVolume* logicTar =
	new G4LogicalVolume(solidTar,          
						steel_mat,           
						"Target");        

	new G4PVPlacement(rotm,                       
					G4ThreeVector(0.*cm,0.,-51.2*um),
					logicTar,                
					"Target",                
					logicWorld,              
					false,                   
					0,                       
					checkOverlaps);
	
	//TARGET TiD layer
	G4Tubs* solidTarTid =
	new G4Tubs("Target_TiD", 
			   0.*cm, 48.5*mm, 0.6*um, 0.*deg, 360.*deg);

	G4LogicalVolume* logicTarTid =
	new G4LogicalVolume(solidTarTid,          
						TiD_mat,           
						"Target_TiD");        

	new G4PVPlacement(rotm,                       
					G4ThreeVector(0.,0.,-0.6*um),
					logicTarTid,                
					"Target_TiD",                
					logicWorld,              
					false,                   
					0,                       
					checkOverlaps);
	
	//Fluoroplactic insulator
	G4Tubs* solidFluoroIns =
	new G4Tubs("FluoroInsulator", 
			   45.*mm, 50.*mm, 1.*mm, 0.*deg, 360.*deg);

	G4LogicalVolume* logicFluoroIns =
	new G4LogicalVolume(solidFluoroIns,          
						fluoro_mat,           
						"FluoroInsulator");        

	new G4PVPlacement(rotm,                       
					G4ThreeVector(0.,0.,1.*mm),
					logicFluoroIns,                
					"FluoroInsulator",                
					logicWorld,              
					false,                   
					0,                       
					checkOverlaps);
	
	//Steel flange_lesser
	G4Tubs* solidFlangeLess =
	new G4Tubs("FlangeLesser", 
			   45.*mm, 60.*mm, 4.*mm, 0.*deg, 360.*deg);

	G4LogicalVolume* logicFlangeLess =
	new G4LogicalVolume(solidFlangeLess,          
						steel_mat,           
						"FlangeLesser");        

	new G4PVPlacement(rotm,                       
					G4ThreeVector(0.,0.,6.*mm),
					logicFlangeLess,                
					"FlangeLesser",                
					logicWorld,              
					false,                   
					0,                       
					checkOverlaps);
	
	//Steel insulator foil
	G4Tubs* solidFoil =
	new G4Tubs("SteelFoil", 
			   0.*mm, 55.*mm, 25.*um, 0.*deg, 360.*deg);

	G4LogicalVolume* logicFoil =
	new G4LogicalVolume(solidFoil,          
						steel_mat,           
						"SteelFoil");        

	new G4PVPlacement(rotm,                       
					G4ThreeVector(0.,0.,10.025*mm),
					logicFoil,                
					"SteelFoil",                
					logicWorld,              
					false,                   
					0,                       
					checkOverlaps);
	
	//Steel flange_greater
	G4Tubs* solidFlangeGreat =
	new G4Tubs("FlangeGreat", 
			   50.*mm, 60.*mm, 4.*mm, 0.*deg, 360.*deg);

	G4LogicalVolume* logicFlangeGreat =
	new G4LogicalVolume(solidFlangeGreat,          
						steel_mat,           
						"FlangeGreat");        

	new G4PVPlacement(rotm,                       
					G4ThreeVector(0.,0.,14.05*mm),
					logicFlangeGreat,                
					"FlangeGreat",                
					logicWorld,              
					false,                   
					0,                       
					checkOverlaps);
	
	//Polystyrene detector
	G4Tubs* solidDetector =
	new G4Tubs("Detector", 
			   0.*mm, 57.5*mm, 2.*mm, 0.*deg, 360.*deg);

	G4LogicalVolume* logicDetector =
	new G4LogicalVolume(solidDetector,          
						polystyr_mat,           
						"Detector");        

	new G4PVPlacement(rotm,                       
					G4ThreeVector(0.,0.,20.05*mm),
					logicDetector,                
					"Detector",                
					logicWorld,              
					false,                   
					0,                       
					checkOverlaps);
	
	return physWorld;
}

void ExG4DetectorConstruction01::ConstructSDandField()
{
  	//Create sensitive detector object in heap
    ExG4DetectorSD* sd1
		= new ExG4DetectorSD("DetectorSD", "DetectorSD1HitsCollection", fNofLayers);
	G4SDManager::GetSDMpointer()->AddNewDetector(sd1);
	SetSensitiveDetector("Detector", sd1, true);
}









