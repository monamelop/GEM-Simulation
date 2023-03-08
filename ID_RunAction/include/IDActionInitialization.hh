#ifndef IDActionInitialization_h
#define IDActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class IDActionInitialization : public G4VUserActionInitialization
{
  public:
    IDActionInitialization();
    virtual ~IDActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
