#include "IDRunAction.hh"
#include "IDPrimaryGeneratorAction.hh"
#include "IDDetectorConstruction.hh"


#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IDRunAction::IDRunAction()
: G4UserRunAction(),
  fSumAlpha(0)
{
  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fSumAlpha);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IDRunAction::~IDRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDRunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDRunAction::EndOfRunAction(const G4Run*)
{
  std::ofstream ofs;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4int sum  = fSumAlpha.GetValue();
  if(IsMaster() && sum!=0){
     ofs.open ("output", std::ofstream::app);
     G4double espessura = 5.; // MUDAR AQUI
     if(espessura == 0.25){
        ofs << "1 placa - catodo G1 G2" "\n";
        ofs << "Espessura: " "\t" << "Eficiencia: " "\n";
     }
     ofs << espessura << "\t" << "\t" << sum <<"E-4"<< "\n";
     ofs.close();

   }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDRunAction::SumAlpha(G4int sum)
{
  fSumAlpha  += sum;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
