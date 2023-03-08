#include "IDTrackingAction.hh"

#include "IDEventAction.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4StepStatus.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

#include "G4VPhysicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IDTrackingAction::IDTrackingAction(IDEventAction* eventAction)
:G4UserTrackingAction(), fEventAction(eventAction)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDTrackingAction::PreUserTrackingAction(const G4Track* track)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IDTrackingAction::PostUserTrackingAction(const G4Track* track)
{
 G4int i=1;
 G4String name = track->GetDefinition()->GetParticleName();
 G4String volumeFinal = track->GetVolume()->GetName(); //regiao onde morrem as alphas
 G4String volumeInicial = track->GetLogicalVolumeAtVertex()->GetName(); // regiao onde nascem as alphas
 G4ThreeVector position = track->GetPosition();
 G4double posz;
 posz=position.z();

 if((name == "alpha" || name == "Li7") && (volumeFinal != volumeInicial) && posz > 0 && (volumeFinal != "ShapeAl")){
   fEventAction->SumAlpha(i);
 }else  if((name == "alpha" || name == "Li7") && posz > 0 && (volumeFinal == "ShapeAl") && (volumeInicial != "Shape1")){
          fEventAction->SumAlpha(i);
        }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
