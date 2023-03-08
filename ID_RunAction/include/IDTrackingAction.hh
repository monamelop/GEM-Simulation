#ifndef IDTrackingAction_h
#define IDTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class IDEventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class IDTrackingAction : public G4UserTrackingAction {

  public:
    IDTrackingAction(IDEventAction* eventAction);
   ~IDTrackingAction() {};

    virtual void  PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

  private:
    IDEventAction* fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
