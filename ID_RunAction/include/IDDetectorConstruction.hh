#ifndef IDDetectorConstruction_h
#define IDDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VisAttributes;
class G4VPhysicalVolume;
class G4LogicalVolume;
class IDRunAction;
/// Detector construction class to define materials and geometry.

class IDDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    IDDetectorConstruction();
    virtual ~IDDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    void IDConstructMaterials();

  private:

    IDRunAction* fRunAction;

    std::vector<G4VisAttributes*> fVisAttributes;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
