//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: DetectorConstruction.cc 48195 2011-02-02 15:33:39Z jjacquem $
// GEANT4 tag $Name: geant4-09-04 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4ExtrudedSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
  :BeamPipeMaterial(0),RadiatorMaterial(0),SweepMagnetMaterial(0),
 ElectronDumpMaterial(0),BubbleMaterial(0),defaultMaterial(0),
 solidWorld(0),logicWorld(0),physiWorld(0),
 solidBeamPipe(0),logicBeamPipe(0),physiBeamPipe(0),
 solidRadiator(0),logicRadiator(0),physiRadiator(0),
   // solidSweepMagnet(0),logicSweepMagnet(0),physiSweepMagnet(0),
   // solidElectronDump(0),logicElectronDump(0),physiElectronDump(0),
 solidPhotonCollimator(0),logicPhotonCollimator(0),physiPhotonCollimator(0),
 solidBubble(0),logicBubble(0),physiBubble(0),
 solidPhotonDump(0),logicPhotonDump(0),physiPhotonDump(0),
 magField(0)
{
  // default parameter values of the calorimeter
     
  WorldSizeZ = 200.0*cm;
  WorldSizeXY = 50.0*cm;

  // Construct beamline

  innerRadiusOfBeamPipe = 2.9*cm;
  outerRadiusOfBeamPipe = 3.*cm;
  lengthOfBeamPipe = 30.*cm;
  startAngleOfBeamPipe = 0.*deg;
  spanningAngleOfBeamPipe = 360.*deg;

  BeamPipeZpos = -lengthOfBeamPipe/2;

  //

  RadiatorThickness = 6.0*mm;
  innerRadiusOfRadiator = 0.*cm;
  outerRadiusOfRadiator = 2.9*cm;
  startAngleOfRadiator = 0.*deg;
  spanningAngleOfRadiator = 360.*deg;

  RadiatorZpos = RadiatorThickness/2;

  //

  // SweepMagnetSizeX = 3.*cm;
  // SweepMagnetSizeY = 6.*cm;
  // SweepMagnetSizeZ = 12.584*cm;
  
  // SweepMagnetZpos = -SweepMagnetSizeZ/2 + 15.*cm;
  
  // //

  // ElectronDumpThickness = 10.*cm;
  // innerRadiusOfElectronDump = 0.*cm;
  // outerRadiusOfElectronDump = 3.0*cm;
  // startAngleOfElectronDump = 0.*deg;
  // spanningAngleOfElectronDump = 360.*deg;

  // ElectronDumpZpos = -ElectronDumpThickness/2 + 80.*cm;
  // ElectronDumpYpos = 25.*cm;

 //

  PhotonCollimatorThickness = 15.*cm;
  innerRadiusOfPhotonCollimator = 0.4*cm;
  outerRadiusOfPhotonCollimator = 5.0*cm;
  startAngleOfPhotonCollimator = 0.*deg;
  spanningAngleOfPhotonCollimator = 360.*deg;

  PhotonCollimatorZpos = -PhotonCollimatorThickness/2 + 20.*cm;

  //

  BubbleThickness = 3.*cm;
  innerRadiusOfBubble = 0.*cm;
  outerRadiusOfBubble = 0.5*cm;
  startAngleOfBubble = 0.*deg;
  spanningAngleOfBubble = 360.*deg;

  BubbleZpos = -BubbleThickness/2 + 41.5*cm;

   //

  PhotonDumpThickness = 40.*cm;
  innerRadiusOfPhotonDump = 0.*cm;
  outerRadiusOfPhotonDump = 10.*cm;
  startAngleOfPhotonDump = 0.*deg;
  spanningAngleOfPhotonDump = 360.*deg;

  PhotonDumpZpos = -PhotonDumpThickness/2 + 120.*cm;

  // materials
  DefineMaterials();
  SetBeamPipeMaterial("G4_Al");
  SetRadiatorMaterial("G4_Cu");
  SetSweepMagnetMaterial("G4_Galactic");
  SetElectronDumpMaterial("G4_Al");
  SetPhotonCollimatorMaterial("G4_Cu");
  SetPhotonDumpMaterial("G4_Al");
  SetBubbleMaterial("SuperHeatLiquid");
  
  // create commands for interactive definition of the calorimeter
  detectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete detectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructBubble();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
// use G4-NIST materials data base
//
G4NistManager* man = G4NistManager::Instance();
defaultMaterial = man->FindOrBuildMaterial("G4_Galactic");
man->FindOrBuildMaterial("G4_Cu");
man->FindOrBuildMaterial("G4_Al");
man->FindOrBuildMaterial("G4_WATER");
man->FindOrBuildMaterial("G4_AIR");
man->FindOrBuildMaterial("G4_NITROUS_OXIDE");

// define gas material at non STP conditions (density=0.846g/cm3, T=-5 C (268.15 K), P=60 atm)
 G4double density = 0.846*g/cm3;
 SuperHeatLiquid = 
   man->BuildMaterialWithNewDensity("SuperHeatLiquid","G4_NITROUS_OXIDE",density,268.15*kelvin,60.0*atmosphere);

// print table
//
G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructBubble()
{

  // Clean old geometry, if any
  //
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
   

  //

  G4RotationMatrix Ra;
  Ra.rotateY(0.0*deg);

  //     
  // World
  //
  solidWorld = new G4Box("World",				//its name
                   WorldSizeXY/2,WorldSizeXY/2,WorldSizeZ/2);	//its size
                         
  logicWorld = new G4LogicalVolume(solidWorld,		//its solid
                                   defaultMaterial,	//its material
                                   "World");		//its name
                                   
  physiWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(),	//at (0,0,0)
                                 logicWorld,		//its logical volume
                                 "World",		//its name
                                 0,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number
  
  //                               
  // Beamline
  //
  solidBeamPipe = new G4Tubs("BeamPipe",
			     innerRadiusOfBeamPipe, 
			     outerRadiusOfBeamPipe,
			     lengthOfBeamPipe/2,
			     startAngleOfBeamPipe, 
			     spanningAngleOfBeamPipe);
  
  logicBeamPipe = new G4LogicalVolume(solidBeamPipe,
				      BeamPipeMaterial,
				      BeamPipeMaterial->GetName());
  
  G4ThreeVector positionBeamPipe = G4ThreeVector(0.,0.,BeamPipeZpos);
  G4Transform3D transformBeamPipe = G4Transform3D(Ra,positionBeamPipe);

  physiBeamPipe = new G4PVPlacement(transformBeamPipe,           //rotation, position
				    logicBeamPipe,               //its logical volume
				    BeamPipeMaterial->GetName(), //its name
				    logicWorld,             //its mother
				    false,                  //no boulean operation
				    0);                     //copy number
  
  //                               
  // Radiator
  //
  solidRadiator=0; logicRadiator=0; physiRadiator=0;  
  
  solidRadiator = new G4Tubs("Radiator",		//its name
			     innerRadiusOfRadiator, 
			     outerRadiusOfRadiator,
			     RadiatorThickness/2,
			     startAngleOfRadiator, 
			     spanningAngleOfRadiator);	    
  
  logicRadiator = new G4LogicalVolume(solidRadiator,    //its solid
				      RadiatorMaterial, //its material
				      RadiatorMaterial->GetName()); //name

  G4ThreeVector positionRadiator = G4ThreeVector(0.,0.,RadiatorZpos);
  G4Transform3D transformRadiator = G4Transform3D(Ra,positionRadiator);
 
  physiRadiator = new G4PVPlacement(transformRadiator, //rotation, position
				    logicRadiator,     //its logical volume
				    RadiatorMaterial->GetName(), //its name
				    logicWorld,             //its mother
				    false,             //no boulean operation
				    0);                //copy number
  
  //     
  // Sweep Magnet
  //
  // solidSweepMagnet=0; logicSweepMagnet=0; physiSweepMagnet=0; 
 
  // solidSweepMagnet = new G4Box("SweepMagnet",				//its name
  //                  SweepMagnetSizeX/2,SweepMagnetSizeY/2,SweepMagnetSizeZ/2);	//its size
                         
  // logicSweepMagnet = new G4LogicalVolume(solidSweepMagnet,
  // 				  SweepMagnetMaterial,
  // 				  SweepMagnetMaterial->GetName());
  
  // G4ThreeVector positionSweepMagnet = G4ThreeVector(0.,0.SweepMagnetZpos);
  // G4Transform3D transformSweepMagnet = G4Transform3D(Ra,positionSweepMagnet);

  // physiSweepMagnet = new G4PVPlacement(transformSweepMagnet, //rotation, position
  // 				logicSweepMagnet,               //its logical volume
  // 				SweepMagnetMaterial->GetName(), //its name
  // 				logicWorld,             //its mother
  // 				false,                  //no boulean operation
  // 				0);                     //copy number
  
  //                                 
  // Electron Dump
  //
  // solidElectronDump=0; logicElectronDump=0; physiElectronDump=0; 
  
  // solidElectronDump = new G4Tubs("ElectronDump",
  // 				 innerRadiusOfElectronDump, 
  // 				 outerRadiusOfElectronDump,
  // 				 ElectronDumpThickness/2,
  // 				 startAngleOfElectronDump, 
  // 				 spanningAngleOfElectronDump);
  
  // logicElectronDump = new G4LogicalVolume(solidElectronDump,
  // 				  ElectronDumpMaterial,
  // 				  ElectronDumpMaterial->GetName());
  
  
  // G4ThreeVector positionElectronDump = G4ThreeVector(0.,ElectronDumpYpos,ElectronDumpZpos);
  // G4Transform3D transformElectronDump = G4Transform3D(Rd,positionElectronDump);

  // physiElectronDump = new G4PVPlacement(transformElectronDump, //rotation, position
  // 				logicElectronDump,               //its logical volume
  // 				ElectronDumpMaterial->GetName(), //its name
  // 				logicWorld,             //its mother
  // 				false,                  //no boulean operation
  // 				0);                     //copy number
  
  //                                 
  // Photon Collimator
  //
  solidPhotonCollimator=0; logicPhotonCollimator=0; physiPhotonCollimator=0; 
  
  solidPhotonCollimator = new G4Tubs("PhotonCollimator",
				 innerRadiusOfPhotonCollimator, 
				 outerRadiusOfPhotonCollimator,
				 PhotonCollimatorThickness/2,
				 startAngleOfPhotonCollimator, 
				 spanningAngleOfPhotonCollimator);
  
  logicPhotonCollimator = new G4LogicalVolume(solidPhotonCollimator,
				  PhotonCollimatorMaterial,
				  PhotonCollimatorMaterial->GetName());
  
  
  G4ThreeVector positionPhotonCollimator = G4ThreeVector(0.,0.,PhotonCollimatorZpos);
  G4Transform3D transformPhotonCollimator = G4Transform3D(Ra,positionPhotonCollimator);

  physiPhotonCollimator = new G4PVPlacement(transformPhotonCollimator, //rotation, position
				logicPhotonCollimator,               //its logical volume
				PhotonCollimatorMaterial->GetName(), //its name
				logicWorld,             //its mother
				false,                  //no boulean operation
				0);                     //copy number
   
  //                                 
  // Bubble Chamber
  //
  solidBubble=0; logicBubble=0; physiBubble=0; 
  
  solidBubble = new G4Tubs("Bubble",
			   innerRadiusOfBubble, 
			   outerRadiusOfBubble,
			   BubbleThickness/2,
			   startAngleOfBubble, 
			   spanningAngleOfBubble);
  
  logicBubble = new G4LogicalVolume(solidBubble,
				    BubbleMaterial,
				    BubbleMaterial->GetName());

  G4ThreeVector positionBubble = G4ThreeVector(0.,0.,BubbleZpos);
  G4Transform3D transformBubble = G4Transform3D(Ra,positionBubble);
  
  physiBubble = new G4PVPlacement(transformBubble, //rotation, position
				  logicBubble,               //its logical volume
				  BubbleMaterial->GetName(), //its name
				  logicWorld,             //its mother
				  false,                  //no boulean operation
				  0);                     //copy number

  //                                 
  // Photon Dump
  //
  solidPhotonDump=0; logicPhotonDump=0; physiPhotonDump=0; 
  
  solidPhotonDump = new G4Tubs("PhotonDump",
  				 innerRadiusOfPhotonDump, 
  				 outerRadiusOfPhotonDump,
  				 PhotonDumpThickness/2,
  				 startAngleOfPhotonDump, 
  				 spanningAngleOfPhotonDump);

  logicPhotonDump = new G4LogicalVolume(solidPhotonDump,
					PhotonDumpMaterial,
					PhotonDumpMaterial->GetName());
  
  
  G4ThreeVector positionPhotonDump = G4ThreeVector(0.,0.,PhotonDumpZpos);
  G4Transform3D transformPhotonDump = G4Transform3D(Ra,positionPhotonDump);
  
  physiPhotonDump = new G4PVPlacement(transformPhotonDump, //rotation, position
				      logicPhotonDump,               //its logical volume
				      PhotonDumpMaterial->GetName(), //its name
				      logicWorld,             //its mother
				      false,                  //no boulean operation
				      0);                     //copy number
  
  //
  // Visualization attributes
  //
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  
  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);

  G4VisAttributes* BeamPipeVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  BeamPipeVisAtt->SetVisibility(true);

  G4VisAttributes* RadiatorVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  RadiatorVisAtt->SetVisibility(true);

  // G4VisAttributes* SweepMagnetVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,0.0));
  // SweepMagnetVisAtt->SetVisibility(true);

  // G4VisAttributes* ElectronDumpVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
  // ElectronDumpVisAtt->SetVisibility(true);

  G4VisAttributes* PhotonCollimatorVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  PhotonCollimatorVisAtt->SetVisibility(true);

  G4VisAttributes* BubbleVisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  BubbleVisAtt->SetVisibility(true);
  
  G4VisAttributes* PhotonDumpVisAtt= new G4VisAttributes(G4Colour(0.0,0.0,0.0));
  PhotonDumpVisAtt->SetVisibility(true);
  
  logicBeamPipe->SetVisAttributes(BeamPipeVisAtt);
  logicRadiator->SetVisAttributes(RadiatorVisAtt);
  //  logicSweepMagnet->SetVisAttributes(SweepMagnetVisAtt);
  //  logicElectronDump->SetVisAttributes(ElectronDumpVisAtt);
  logicPhotonCollimator->SetVisAttributes(PhotonCollimatorVisAtt);
  logicBubble->SetVisAttributes(BubbleVisAtt);
  logicPhotonDump->SetVisAttributes(PhotonDumpVisAtt);
  
  //
  //always return the physical World
  //
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetBeamPipeMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);      
  if (pttoMaterial) BeamPipeMaterial = pttoMaterial;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetRadiatorMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);      
  if (pttoMaterial) RadiatorMaterial = pttoMaterial;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetSweepMagnetMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =  
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  if (pttoMaterial) SweepMagnetMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetElectronDumpMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =  
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  if (pttoMaterial) ElectronDumpMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetPhotonCollimatorMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =  
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  if (pttoMaterial) PhotonCollimatorMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetBubbleMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =  
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  if (pttoMaterial) BubbleMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetPhotonDumpMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =  
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  if (pttoMaterial) PhotonDumpMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetRadiatorThickness(G4double val)
{
  // change Radiator thickness and recompute the calorimeter parameters
  RadiatorThickness = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetElectronDumpThickness(G4double val)
{
  // change Electron Dump thickness and recompute the calorimeter parameters
  ElectronDumpThickness = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetBubbleThickness(G4double val)
{
  // change Bubble thickness 
  BubbleThickness = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

void DetectorConstruction::SetMagField(G4double fieldValue)
{
  //apply a global uniform magnetic field along Z axis
  // G4FieldManager* fieldMgr
  //   = G4TransportationManager::GetTransportationManager()->GetFieldManager();

  //apply a local uniform magnetic field along Z axis
  G4FieldManager* fieldMgr = new G4FieldManager(magField);
  
  if(magField) delete magField;		//delete the existing magn field
  
  if(fieldValue!=0.)			// create a new one if non nul
    { magField = new G4UniformMagField(G4ThreeVector(0.,0.,fieldValue));
      fieldMgr->SetDetectorField(magField);
      fieldMgr->CreateChordFinder(magField);
      
      // Set magnetic field in Sweep Magnet and its daughters:
      G4bool allLocal = true ;
      //      logicSweepMagnet->SetFieldManager(fieldMgr, allLocal) ;
      //

    } else {
    magField = 0;
    fieldMgr->SetDetectorField(magField);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
