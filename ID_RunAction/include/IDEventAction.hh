#ifndef IDEventAction_h
#define IDEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class IDRunAction;

/// Event action class
///

class IDEventAction : public G4UserEventAction
{
  public:
    IDEventAction(IDRunAction* runAction);
    virtual ~IDEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

    void SumAlpha(G4int sum) {fSumAlpha += sum; }

  private:
    IDRunAction* fRunAction;
    G4int fSumAlpha;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
