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
// $Id: DetectorConstruction.hh 48195 2011-02-02 15:33:39Z jjacquem $
// GEANT4 tag $Name: geant4-09-04 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4Tubs;
class G4ExtrudedSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();

  public:
  
     void SetBeamPipeMaterial (G4String);

     void SetRadiatorMaterial (G4String);     
     void SetRadiatorThickness(G4double);     

     void SetSweepMagnetMaterial (G4String);     

     void SetElectronDumpMaterial (G4String);     
     void SetElectronDumpThickness(G4double);

     void SetPhotonCollimatorMaterial (G4String);

     void SetBubbleMaterial (G4String);     
     void SetBubbleThickness(G4double);

     void SetPhotonDumpMaterial (G4String);
   
     void SetMagField(G4double);

     G4VPhysicalVolume* Construct();

     void UpdateGeometry();
     
  public:
  
     void PrintCalorParameters(); 
                    
     G4double GetWorldSizeZ()           {return WorldSizeZ;}; 
     G4double GetWorldSizeXY()          {return WorldSizeXY;};

     G4Material* GetBeamPipeMaterial()  {return RadiatorMaterial;};

     G4Material* GetRadiatorMaterial()  {return RadiatorMaterial;};
     G4double    GetRadiatorThickness() {return RadiatorThickness;};

     G4Material* GetSweepMagnetMaterial()       {return SweepMagnetMaterial;};
     
     G4Material* GetElectronDumpMaterial()       {return ElectronDumpMaterial;};
     G4double    GetElectronDumpThickness()      {return ElectronDumpThickness;};
 
     G4Material* GetPhotonCollimatorMaterial()       {return PhotonCollimatorMaterial;};
    
     G4Material* GetBubbleMaterial()       {return BubbleMaterial;};
     G4double    GetBubbleThickness()      {return BubbleThickness;};
 
     G4Material* GetPhotonDumpMaterial()       {return PhotonDumpMaterial;};            

     const G4VPhysicalVolume* GetphysiWorld() {return physiWorld;};           
     const G4VPhysicalVolume* GetRadiator()   {return physiRadiator;};
     const G4VPhysicalVolume* GetSweepMagnet()   {return physiSweepMagnet;};
     const G4VPhysicalVolume* GetElectronDump()        {return physiElectronDump;};
     const G4VPhysicalVolume* GetPhotonCollimator()        {return physiPhotonCollimator;};
     const G4VPhysicalVolume* GetBubble()     {return physiBubble;};
     const G4VPhysicalVolume* GetPhotonDump()     {return physiPhotonDump;};

  private:

     G4Material*        BeamPipeMaterial;
     G4double           innerRadiusOfBeamPipe;
     G4double           outerRadiusOfBeamPipe;
     G4double           lengthOfBeamPipe;
     G4double           startAngleOfBeamPipe;
     G4double           spanningAngleOfBeamPipe;
     G4double           BeamPipeZpos;

     G4Material*        RadiatorMaterial;
     G4double           RadiatorThickness;
     G4double           innerRadiusOfRadiator;
     G4double           outerRadiusOfRadiator;
     G4double           startAngleOfRadiator;
     G4double           spanningAngleOfRadiator;
     G4double           RadiatorZpos;

     G4Material*        SweepMagnetMaterial;
     G4double           SweepMagnetSizeX;
     G4double           SweepMagnetSizeY;
     G4double           SweepMagnetSizeZ;
     G4double           SweepMagnetZpos;

     G4Material*        ElectronDumpMaterial;
     G4double           ElectronDumpThickness;
     G4double           innerRadiusOfElectronDump;
     G4double           outerRadiusOfElectronDump;
     G4double           startAngleOfElectronDump;
     G4double           spanningAngleOfElectronDump;
     G4double           ElectronDumpZpos;
     G4double           ElectronDumpYpos;

     G4Material*        PhotonCollimatorMaterial;
     G4double           PhotonCollimatorThickness;
     G4double           innerRadiusOfPhotonCollimator;
     G4double           outerRadiusOfPhotonCollimator;
     G4double           startAngleOfPhotonCollimator;
     G4double           spanningAngleOfPhotonCollimator;
     G4double           PhotonCollimatorZpos;

     G4Material*        BubbleMaterial;
     G4double           BubbleThickness;
     G4double           innerRadiusOfBubble;
     G4double           outerRadiusOfBubble;
     G4double           startAngleOfBubble;
     G4double           spanningAngleOfBubble;
     G4double           BubbleZpos;
     
     G4Material*        PhotonDumpMaterial;
     G4double           PhotonDumpThickness;
     G4double           innerRadiusOfPhotonDump;
     G4double           outerRadiusOfPhotonDump;
     G4double           startAngleOfPhotonDump;
     G4double           spanningAngleOfPhotonDump;
     G4double           PhotonDumpZpos;
 
 //

     G4Material*        defaultMaterial;
     G4double           WorldSizeXY;
     G4double           WorldSizeZ;
            
     G4Box*             solidWorld;    //pointer to the solid World 
     G4LogicalVolume*   logicWorld;    //pointer to the logical World
     G4VPhysicalVolume* physiWorld;    //pointer to the physical World

     G4Tubs*            solidBeamPipe;    //pointer to the solid BeamPipe
     G4LogicalVolume*   logicBeamPipe;    //pointer to the logical BeamPipe
     G4VPhysicalVolume* physiBeamPipe;    //pointer to the physical BeamPipe
         
     G4Tubs*            solidRadiator; //pointer to the solid Radiator
     G4LogicalVolume*   logicRadiator; //pointer to the logical Radiator
     G4VPhysicalVolume* physiRadiator; //pointer to the physical Radiator

     G4Box*            solidSweepMagnet;      //pointer to the solid SweepMagnet
     G4LogicalVolume*   logicSweepMagnet;      //pointer to the logical SweepMagnet
     G4VPhysicalVolume* physiSweepMagnet;      //pointer to the physical SweepMagnet

     
     G4Tubs*            solidElectronDump;      //pointer to the solid Electron Dump
     G4LogicalVolume*   logicElectronDump;      //pointer to the logical Electron Dump
     G4VPhysicalVolume* physiElectronDump;      //pointer to the physical Electron Dump

     G4Tubs*            solidPhotonCollimator;      //pointer to the solid Photon Collimator
     G4LogicalVolume*   logicPhotonCollimator;      //pointer to the logical Photon Collimator
     G4VPhysicalVolume* physiPhotonCollimator;      //pointer to the physical Photon Collimator

     G4Material*        SuperHeatLiquid;
     G4Tubs*            solidBubble;      //pointer to the solid Bubble
     G4LogicalVolume*   logicBubble;      //pointer to the logical Bubble
     G4VPhysicalVolume* physiBubble;      //pointer to the physical Bubble

    G4Tubs*            solidPhotonDump;      //pointer to the solid Electron Dump
  //     G4ExtrudedSolid*   solidPhotonDump;      //pointer to the solid Electron Dump
     G4LogicalVolume*   logicPhotonDump;      //pointer to the logical Electron Dump
     G4VPhysicalVolume* physiPhotonDump;      //pointer to the physical Electron Dump

     G4UniformMagField* magField;      //pointer to the magnetic field
     
     DetectorMessenger* detectorMessenger;  //pointer to the Messenger
      
  private:
    
     void DefineMaterials();
     G4VPhysicalVolume* ConstructBubble();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

