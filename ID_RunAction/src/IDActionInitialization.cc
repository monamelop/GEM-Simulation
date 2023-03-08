#include "IDActionInitialization.hh"
#include "IDPrimaryGeneratorAction.hh"
#include "IDEventAction.hh"
#include "IDTrackingAction.hh"
#include "IDRunAction.hh"
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IDActionInitialization::IDActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IDActionInitialization::~IDActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDActionInitialization::BuildForMaster() const
{
  IDRunAction* runAction = new IDRunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDActionInitialization::Build() const
{
  // std::ofstream ofs ("output",std::ofstream::out | std::ofstream::trunc);
  SetUserAction(new IDPrimaryGeneratorAction);

  IDRunAction* runAction = new IDRunAction;
  SetUserAction(runAction);

  IDEventAction* eventAction = new IDEventAction(runAction);
  SetUserAction(eventAction);

  IDTrackingAction* trackingAction = new IDTrackingAction(eventAction);
  SetUserAction(trackingAction);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
