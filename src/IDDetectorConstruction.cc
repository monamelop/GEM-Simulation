#include "IDDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4GenericMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IDDetectorConstruction::IDDetectorConstruction()
: G4VUserDetectorConstruction(),
  fVisAttributes()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IDDetectorConstruction::~IDDetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* IDDetectorConstruction::Construct()
{
  using namespace std;
  G4bool checkOverlaps = true;

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();




  //************** BEGIN of World definition ***********************
  G4double worldSize = 1.*m;
  //G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_Galactic"); //Galactic = vacuum
  IDConstructMaterials();
  G4Material* argonGas = G4Material::GetMaterial("G4_Ar");

  /******************** Alguns Elementos *************************/
  G4Element* elO = new G4Element("Oxygen", "O2", 8, 16*g/mole);
  G4Element* elC = new G4Element("Carbon", "C", 6, 12.01*g/mole);
  G4Element* elFe = new G4Element("Iron", "Fe", 26, 55.85*g/mole);
  G4Element* elSi = new G4Element("Silicon", "Si", 14, 28.09*g/mole);
  G4Element* elCa = new G4Element("Calcium", "Ca", 20, 40.08*g/mole);
  G4Element* elF = new G4Element("Fluorine", "F", 9, 19.00*g/mole);
  G4Element* elN = new G4Element("Nitrogen","N",7., 14.01*g/mole);
  G4Element* elH = new G4Element("Hydrogen","H",1., 1.01*g/mole);

  G4Material* Copper = new G4Material("Copper", 29.,63.54*g/mole, 8.96*g/cm3);
  G4Material* Aluminium = new G4Material("Aluminium",13.,26.98*g/mole,2.7*g/cm3);




  /*********************** gas Argon ***************************/
  G4double density;
  G4int nel,natoms;
  density = 0.002*g/cm3;
  G4Material* co2 = new G4Material("CO2",density,nel=2);
  co2->AddElement(elC, natoms=1);
  co2->AddElement(elO, natoms=2);


  density = 0.002*g/cm3;
  G4Material* GEM_ArCO2 = new G4Material("GEM_ArCO2",density,nel=2);
  GEM_ArCO2->AddMaterial(co2, 10*perCent);
  GEM_ArCO2->AddMaterial(argonGas, 90*perCent);



  G4Material* worldMaterial = nist->FindOrBuildMaterial("GEM_ArCO2");






  G4Box* solidWorld =
    new G4Box("World",
      0.5*worldSize, 0.5*worldSize, 0.5*worldSize);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,
                        worldMaterial,
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

  //************** END of World definition ***********************

  // *************** BEGIN: Shape definition *********************
  // G4double density = 2.46*g/cm3;
  // G4double a = 10.012937*g/mole; //massa molar
  // G4double z = 5.; //numero atomico
  G4double esp = 5.*um; //espessura da placa
  //********* Boron Carbide - B4C ***************

  G4Isotope* B10 = new G4Isotope("Boron10", 5, 10, 10*g/mole);
  G4Element* elB = new G4Element("Boron", "Boron", 1);
  elB->AddIsotope(B10,1.0);


  G4Material* BoronCarbide = new G4Material("BoronCarbide", 2.52*g/cm3, 6);
  BoronCarbide->AddElement(elB, 80*perCent);
  BoronCarbide->AddElement(elC, 18.1*perCent);
  BoronCarbide->AddElement(elFe, 1*perCent);
  BoronCarbide->AddElement(elSi, 0.5*perCent);
  BoronCarbide->AddElement(elCa, 0.3*perCent);
  BoronCarbide->AddElement(elF, 0.025*perCent);


  /*
  // ******************* 10B ****************************
  G4Isotope* isoB10 = new G4Isotope("B10", 5, 10, 10.012937*g/mole);
  G4Element* el_b10 = new G4Element("elementB10","B10",1);
  el_b10->AddIsotope(isoB10,100*perCent);
  G4Material* boron_layer_material = new G4Material("B10",2.34*g/cm3,1);
  boron_layer_material->AddElement(el_b10,1);
  */

  // Kapton Dupont de Nemur (density: 1.396-1.430, get middle )
  density = 1.413*g/cm3;
  G4Material* Kapton = new G4Material("Kapton", density, 4);
  Kapton->AddElement(elO,5);
  Kapton->AddElement(elC,22);
  Kapton->AddElement(elN,2);
  Kapton->AddElement(elH,10);



  G4double espKap = 50.*um;
  G4double espCu = 5.*um;

  G4double espAl = 500.*um;


  //**************************** DEFINICAO DOS SHAPES *************************************//
  G4Box* solidShape1 = new G4Box("Shape1", 0.1*worldSize, 0.1*worldSize, 0.5*esp); //B4C
  G4Box* solidShape2 = new G4Box("Shape2", 0.1*worldSize, 0.1*worldSize, 0.5*esp); //B4C
  G4Box* solidShape3 = new G4Box("Shape3", 0.1*worldSize, 0.1*worldSize, 0.5*esp); //B4C
  G4Box* solidShape4 = new G4Box("Shape4", 0.1*worldSize, 0.1*worldSize, 0.5*esp); //B4C
  G4Box* solidShape5 = new G4Box("Shape5", 0.1*worldSize, 0.1*worldSize, 0.5*esp); //B4C
  G4Box* solidShapeKapton = new G4Box("ShapeKapton", 0.1*worldSize, 0.1*worldSize, 0.5*espKap); //Kapton
  G4Box* solidShapeCopper = new G4Box("ShapeCopper",0.1*worldSize, 0.1*worldSize, 0.5*espCu); //Cobre
  G4Box* solidShapeAl = new G4Box("ShapeAl",0.1*worldSize, 0.1*worldSize, 0.5*espAl); //Aluminium
  //sempre é necessário dividir o tamanho da coordenada por 2
  //pois ele entende x_i como o intervalo -x_i a x_i

  //********************* 10B **********************************
  //G4LogicalVolume* logicShapeB10 = new G4LogicalVolume(solidShapeB10, boron_layer_material, "ShapeB10");

  G4LogicalVolume* logicShape1 = new G4LogicalVolume(solidShape1, BoronCarbide, "Shape1");
  G4LogicalVolume* logicShape2 = new G4LogicalVolume(solidShape2, BoronCarbide, "Shape2");
  G4LogicalVolume* logicShape3 = new G4LogicalVolume(solidShape3, BoronCarbide, "Shape3");
  G4LogicalVolume* logicShape4 = new G4LogicalVolume(solidShape4, BoronCarbide, "Shape4");
  G4LogicalVolume* logicShape5 = new G4LogicalVolume(solidShape5, BoronCarbide, "Shape5");

  G4LogicalVolume* logicShapeCopper = new G4LogicalVolume(solidShapeCopper, Copper, "ShapeCopper");
  G4LogicalVolume* logicShapeKap = new G4LogicalVolume(solidShapeKapton, Kapton, "ShapeKapton");
  G4LogicalVolume* logicShapeAl = new G4LogicalVolume(solidShapeAl, Aluminium, "ShapeAl");
  //**************************** FIM DO LOGICSHAPE ********************************

  //****************** B10 Only ************************************
  //new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicShapeB10, "ShapeB10", logicWorld, false, 0, checkOverlaps);
  //new G4PVPlacement(0, G4ThreeVector(0.,0.,5.*cm), logicShapeB10, "ShapeB10", logicWorld, false, 0, checkOverlaps);
  //new G4PVPlacement(0, G4ThreeVector(0.,0.,10.*cm), logicShapeB10, "ShapeB10", logicWorld, false, 0, checkOverlaps);
  //new G4PVPlacement(0, G4ThreeVector(0.,0.,15.*cm), logicShapeB10, "ShapeB10", logicWorld, false, 0, checkOverlaps);




  /*

  G4int nplacas = 1; //numero de placas
  G4double d = 5.*mm; //distancia entre as placas
  G4int cont = 0;

  //localizacoes das placas no espaco

  while(cont < nplacas){
    new G4PVPlacement(0, G4ThreeVector(0.,0.,d*cont), logicShape1, "Shape1", logicWorld, false, 0, checkOverlaps);
    cont = cont + 1.;
  }
  */


  //********************************* STARTS IPEN DETECTOR ***********************************************
  //Aluminio

  new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicShapeAl, "ShapeAl", logicWorld, false, 0, checkOverlaps);
  G4double mespAl = espAl/2.;
  G4double mesp = esp/2.;
  G4double posB1 = mespAl+mesp;
  new G4PVPlacement(0, G4ThreeVector(0.,0.,posB1), logicShape1, "Shape1", logicWorld, false, 0, checkOverlaps);



  //************ ADICIONANDO 1 PLACA DE GEM ****************************

  // posicao da placa de B4C

  G4double adrift = 2000.*um;

  G4double posB2 = posB1+mesp+adrift+mesp;
  new G4PVPlacement(0, G4ThreeVector(0.,0.,posB2), logicShape2, "Shape2", logicWorld, false, 0, checkOverlaps);


  G4double ThCopper = 0.5*espCu;
  G4double ThKapton = 0.5*espKap;

  G4double pos1G1 = posB2+mesp+ThCopper;
  G4double pos2G1 = pos1G1+ThCopper+ThKapton;
  G4double pos3G1 = pos2G1+ThKapton+ThCopper;
  new G4PVPlacement(0, G4ThreeVector(0.,0.,pos1G1), logicShapeCopper, "ShapeCopper", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,pos2G1), logicShapeKap, "ShapeKapton", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,pos3G1), logicShapeCopper, "ShapeCopper", logicWorld, false, 0, checkOverlaps);

  G4double posB3 = pos3G1+ThCopper+mesp;
  new G4PVPlacement(0, G4ThreeVector(0.,0.,posB3), logicShape3, "Shape3", logicWorld, false, 0, checkOverlaps);


  // ************ ADICIONANDO SEGUNDA PLACA DE GEM

  G4double transfer = 1000.*um;

  G4double posB4 = posB3+mesp+transfer+mesp;
  new G4PVPlacement(0, G4ThreeVector(0.,0.,posB4), logicShape4, "Shape4", logicWorld, false, 0, checkOverlaps);

  G4double pos1G2 = posB4+mesp+ThCopper;
  G4double pos2G2 = pos1G2+ThCopper+ThKapton;
  G4double pos3G2 = pos2G2+ThKapton+ThCopper;
  new G4PVPlacement(0, G4ThreeVector(0.,0.,pos1G2), logicShapeCopper, "ShapeCopper", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,pos2G2), logicShapeKap, "ShapeKapton", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,pos3G2), logicShapeCopper, "ShapeCopper", logicWorld, false, 0, checkOverlaps);

  // posicao da placa de B4C
  G4double posB5 = pos3G2+ThCopper+mesp;
  new G4PVPlacement(0, G4ThreeVector(0.,0.,posB5), logicShape5, "Shape5", logicWorld, false, 0, checkOverlaps);


  // *************** END: Shape definition *********************


  //visualization
  G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));

    // cor do B4C
  visAttributes = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
  logicShape1->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);


    // cor do B4C
  visAttributes = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
  logicShape2->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);


    // cor do B4C
  visAttributes = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
  logicShape3->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

    // cor do B4C
  visAttributes = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
  logicShape4->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

    // cor do B4C
  visAttributes = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
  logicShape5->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);


    // cor do kapton
  visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,0.,1.0));
  logicShapeKap->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);


    //cor do Cobre

  visAttributes = new G4VisAttributes(G4Colour(0.45,0.25,0.,1.0));
  logicShapeCopper->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);



  return physWorld;
}

void IDDetectorConstruction::IDConstructMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    // Air
    nistManager->FindOrBuildMaterial("G4_AIR");

    // Argon gas
    nistManager->FindOrBuildMaterial("G4_Ar");

    // Vacuum "Galactic"
     nistManager->FindOrBuildMaterial("G4_Galactic");

    // boron
    nistManager->FindOrBuildMaterial("G4_B");

    // Cadmium
    nistManager->FindOrBuildMaterial("G4_Cd");

    // Aluminium
    nistManager->FindOrBuildMaterial("G4_Al");


}
