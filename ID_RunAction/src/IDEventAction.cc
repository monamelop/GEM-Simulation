#include "IDEventAction.hh"
#include "IDRunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"

IDEventAction::IDEventAction(IDRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fSumAlpha(0)
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IDEventAction::~IDEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDEventAction::BeginOfEventAction(const G4Event*)
{
  fSumAlpha = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDEventAction::EndOfEventAction(const G4Event* event)
{
  G4int eventID = event->GetEventID();
  fRunAction->SumAlpha(fSumAlpha);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
