//#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include <chrono>
#include <random>
#include <math.h> 
#include <string>
#include <sstream>
#include <sys/stat.h>

#include "ExG4PrimaryGeneratorAction02.hh"
#include "ExG4DetectorSD.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

using namespace std;

int pre = 0;
double endp = 0;
static const int NOBINS = 1000;
   G4String* pname = new G4String;
//double enrg = 0;*/

double histogram0[NOBINS];

//Sigma generator that simulates the normal distribution of energies in peaks
//as the Poisson distribution of scintillation photons
//The real FWHM(E) function of detector is used
//0.056 for NaI & 2.57924/4.438 = 0.5812 for Polystyrene

double sigen (double engot) {
	double enrg = 0.0;
	if (engot != 0) {
		double sig = 0.052/2.355*engot*sqrt(4.438/engot);
		//double sig = 0.5812/2.355*engot*sqrt(4.438/engot);
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		default_random_engine generator (seed);
		normal_distribution<double> distribution (0.0,sig);
		double randgen =  distribution(generator);
		enrg = engot + randgen - 1;
		if (enrg < 0) { enrg = 0.0; }
	}
	else {
		return 0.0;
	}
	return enrg;
}

//Spectrum filler that writes every catched energy for one primary in file

void sp1(const double& endep) {
	//double endp1 = sigen(endep);
	if (endep != 0) {
		ofstream fileen ("../testdata/energyloss.dat", ios::app);
		fileen << endep << '\n';
		fileen.close();
	}
}

//Template function Tracker that tracks the behavior of particle, including
//all kind of its and secondary particles' interactions

template <typename TEnr, typename TStr, typename TInt1, typename TInt2, typename TInt3, typename TNum, typename TName, typename TEnr1>
void Tracker(TEnr endep, TStr p1, TInt1 PID, TInt2 TID, TInt3 step, TNum pre0, TNum numbr, TNum post0, TName part, TEnr1 kinetic){
	double endp1 = sigen(endep);
	//if (endp1 != 0) {
		ofstream filex3 ("../testdata/test.dat", ios::app);
		if (/*static_cast<string>(p1) != "DUMMY" &&*/ pre0 == numbr){
		filex3 << "collected energy " << setw(10) << endp1 << " from particle "
		<< setw(10)<< part << " with energy " << setw(10) << kinetic << " caused by process " 
		<< setw(20) << p1 << " parent " << PID << " track " << TID << " step " 
		<< step << " event " << pre0 << " " << " " << post0 << " " << numbr << endl;
			}
		else {
		filex3 << endp1 << " event " << pre0 << endl << endl;
			}
		filex3.close();
	//}
}

//Template function ProcessorForParticles that processes hits of primary and
//secondary particles and writes the info in spectrum/tracker

template <typename TPid, typename TNumb, typename TPre, typename TEndp, typename TDep, 
		typename TProc, typename TTrack, typename TStep, typename TPart, typename TEnr1>
void ProcessorForParticles (TPid parid, TNumb numb0, TPre& pre0, TPre& post0, 
							TEndp& endp0, TDep DepEnr, TProc procname, TTrack trackid, 
							TStep stepno, TPart partname, TEnr1 energy1){
			
			//GAMMAS ONLY -----------------------------------
			
//Check #1: The particles that hits is NOT primary
//This particle is generated from another primary -> write backstored energy
//in spectrum and store the energy for NEW particle. If not - +=stored energy
	//if (parid != 0) {
		if (numb0 != pre0) {
			sp1(endp0);
			Tracker(endp0, procname, parid, trackid, stepno, pre0, numb0, post0, partname, energy1);
			endp0 = 0;
			endp0 += DepEnr;
			Tracker(endp0, procname, parid, trackid, stepno, pre0 + 1, numb0, post0, partname, energy1);
		}
		else {
			endp0 += DepEnr;
			Tracker(endp0, procname, parid, trackid, stepno, pre0, numb0, post0, partname, energy1);
		}
	//}
//Else Check:  the particle that hits IS primary. Then you must write backstored energy
//in spectrum and begin the new storage.
	//else {
		/*if (numb0 != pre0) {
			sp1(endp0);
			Tracker(endp0, procname, parid, trackid, stepno, pre0, numb0, post0, partname, energy1);
			endp0 = 0;
		}
		else {
			
		}*/
	//}
			//GAMMAS END---------------------------------------
}
    
ExG4DetectorSD::ExG4DetectorSD(
                            const G4String& name, 
                            const G4String& hitsCollectionName,
                            G4int nofCells)
 : G4VSensitiveDetector(name),
   fHitsCollection(nullptr),
   fNofCells(nofCells),
	HIST_MAX(20.*MeV),
	HIST_MIN(0.*MeV)
{
		//Check if testdata folder exists and if not, create it
		const char* testfolder;
		testfolder = "../testdata";
		struct stat sb;

		if (stat(testfolder, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		//printf("YES\n");
		} else {
		mkdir(testfolder, 0755);
		}
		
		collectionName.insert(hitsCollectionName);
	   	ofstream file1("../testdata/testdet.dat", std::ios::trunc);
    	file1.close();
		ofstream filex2("../testdata/energyloss.dat", std::ios::trunc);
    	filex2.close();
		ofstream filex3("../testdata/test.dat", std::ios::trunc);
    	filex3.close();
		/*ofstream filex3("test.dat", std::ios::trunc);
    	filex2.close();*/
		//std::ofstream filed2("det2.dat", std::ios::trunc);
    	//filed2.close();
}

//ExG4DetectorSD::~ExG4DetectorSD() 
//{ 
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4DetectorSD::Initialize(G4HCofThisEvent* hce)
{
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool ExG4DetectorSD::ProcessHits(G4Step* step, 
                                     G4TouchableHistory*)
{  
	//definition of necessary values
	auto touchable = (step->GetPreStepPoint()->GetTouchable());
	auto touchableVol = touchable->GetVolume()->GetName();
	auto partname = step->GetTrack()->GetDefinition()->GetParticleName();
	auto DepEnr = step->GetTotalEnergyDeposit();
	//double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
	//double energy = step->GetPreStepPoint()->GetKineticEnergy();
	double energy1 = step->GetPreStepPoint()->GetKineticEnergy();
	double energy2 = step->GetPostStepPoint()->GetKineticEnergy();
	
	auto atrack = step -> GetTrack();
	auto trackid = atrack -> GetTrackID();
	auto parid = atrack -> GetParentID();
	auto stepno = atrack -> GetCurrentStepNumber();
	int post = numb;
	
	//dummy process in order to avoid undefined variable error
	
	auto procname = "DUMMY";
	if (trackid != 1 && parid != 0) {
			auto creat = atrack -> GetCreatorProcess();
			procname = creat->GetProcessName();
	}
	else {
		
	}

	if (touchableVol == "Detector") {
		ProcessorForParticles(parid, numb, pre, post, endp, DepEnr, procname, trackid, stepno, partname, energy1);
		pre = post;
	}
	
	//particleKiller
	/*if (energy1 != energy2) {
		if (trackid != 1 && parid != 0) {
						//auto creat = atrack -> GetCreatorProcess();
						//auto procname = creat->GetProcessName();
		}
		else {
			step->GetTrack()->SetTrackStatus(fStopAndKill);
		}
	}*/
	*pname = partname; // particle name
	
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4DetectorSD::EndOfEvent(G4HCofThisEvent*)
{
}

// In destructor the info from spectrum file writes into the histograms

ExG4DetectorSD::~ExG4DetectorSD() 
{ 
	string line;
	ifstream fileend;
	fileend.open("../testdata/energyloss.dat");
	double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
	if (fileend.is_open()) {
		while(getline(fileend, line)) {
			double num = stod(line);
			int index0 = int(floor((sigen(num)-HIST_MIN)/bin_width/MeV)); //energy spread simulation is used
			if(index0 >= 0 && index0 < NOBINS){
				histogram0[index0]++;
			}
		}
		fileend.close();
	}
	
	//Check if spectra folder exists and if not, create it
		const char* folder;
		folder = "../spectra";
		struct stat sb;

		if (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		//printf("YES\n");
		} else {
		mkdir(folder, 0755);
		}
	
	//Create a spectrum file with following specific data: particle and number of primaries
	stringstream ss;
	ss << numb;
	string filename = "../spectra/Sp_" + *pname  + "_" + ss.str() + ".dat";
	
	ofstream filed0(filename, ios::trunc);
    for(int i = 0; i<NOBINS; i++)
    {
        double energy0 = i*bin_width + HIST_MIN;
        filed0 << energy0 << " "
             << histogram0[i] << std::endl;
	}
	filed0.close();
	delete pname;
}

