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
// $Id: DetectorMessenger.cc 48195 2011-02-02 15:33:39Z jjacquem $
// GEANT4 tag $Name: geant4-09-04 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger( DetectorConstruction* Det)
:Detector(Det)
{ 
  BubbleDir = new G4UIdirectory("/Bubble/");
  BubbleDir->SetGuidance("UI commands of this example");
  
  detDir = new G4UIdirectory("/Bubble/det/");
  detDir->SetGuidance("detector control");
       
  RadMaterCmd = new G4UIcmdWithAString("/Bubble/det/setRadMat",this);
  RadMaterCmd->SetGuidance("Select Material of the Radiator.");
  RadMaterCmd->SetParameterName("choice",false);
  RadMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ElectronDumpMaterCmd = new G4UIcmdWithAString("/Bubble/det/setElectronDumpMat",this);
  ElectronDumpMaterCmd->SetGuidance("Select Material of the Electron Dump.");
  ElectronDumpMaterCmd->SetParameterName("choice",false);
  ElectronDumpMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
  RadThickCmd = new G4UIcmdWithADoubleAndUnit("/Bubble/det/setRadThick",this);
  RadThickCmd->SetGuidance("Set Thickness of the Radiator");
  RadThickCmd->SetParameterName("Size",false);
  RadThickCmd->SetRange("Size>=0.");
  RadThickCmd->SetUnitCategory("Length");
  RadThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ElectronDumpThickCmd = new G4UIcmdWithADoubleAndUnit("/Bubble/det/setElectronDumpThick",this);
  ElectronDumpThickCmd->SetGuidance("Set Thickness of the Electron Dump");
  ElectronDumpThickCmd->SetParameterName("Size",false);
  ElectronDumpThickCmd->SetRange("Size>=0.");
  ElectronDumpThickCmd->SetUnitCategory("Length");  
  ElectronDumpThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  UpdateCmd = new G4UIcmdWithoutParameter("/Bubble/det/update",this);
  UpdateCmd->SetGuidance("Update geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);

  MagFieldCmd = new G4UIcmdWithADoubleAndUnit("/Bubble/det/setMagField",this);  
  MagFieldCmd->SetGuidance("Define magnetic field.");
  MagFieldCmd->SetGuidance("Magnetic field will be in Z direction.");
  MagFieldCmd->SetParameterName("Bz",false);
  MagFieldCmd->SetUnitCategory("Magnetic flux density");
  MagFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete RadMaterCmd; delete ElectronDumpMaterCmd;
  delete RadThickCmd; delete ElectronDumpThickCmd;
  delete UpdateCmd;
  delete MagFieldCmd;
  delete detDir;
  delete BubbleDir;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == RadMaterCmd )
   { Detector->SetRadiatorMaterial(newValue);}
   
  if( command == ElectronDumpMaterCmd )
   { Detector->SetElectronDumpMaterial(newValue);}
  
  if( command == RadThickCmd )
   { Detector->SetRadiatorThickness(RadThickCmd
                                               ->GetNewDoubleValue(newValue));}
   
  if( command == ElectronDumpThickCmd )
   { Detector->SetElectronDumpThickness(ElectronDumpThickCmd->GetNewDoubleValue(newValue));}
  
 if( command == MagFieldCmd )
   { Detector->SetMagField(MagFieldCmd->GetNewDoubleValue(newValue));}

  //  if( command == UpdateCmd )
    //   { Detector->UpdateGeometry(); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
