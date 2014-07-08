//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//
// Constructs the Detector('s). Here we set the gdml parser to read the gdml 
// files which contain the geometry. All old geometry beamline, radiator, bubble
// , photondump have been removed and put into gdml along with the other 
// geometry.
//
// The file originally seemed if it had been modified from a EM G4 example and 
// had different abilities commented out. These have all been taken out for the 
// most part. Mainly because for them to work now they would have to be adjusted
// to fit with gdml reading. If needed these can be recreated but so that they
// are functional with the gdml geometry.
// most of what was available were commands to adjust setting such as lenght, 
// material of geometry. If needed we can also setup the write command to work
// with these so that G4 writes the gdml after adjustment.
//
// The modifications to the files generally follow from the G4 examples G01-4.
// Other sources which seem to have followed these examples are remoll and 
// hmolpol (which has good notes for figuring out what is happening)
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef BCDetectorConstruction_h
#define BCDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4GDMLReadStructure.hh"
#include "G4GDMLParser.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"

#include "G4LogicalVolumeStore.hh"

class G4Box;
class G4Tubs;
class G4ExtrudedSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class BCDetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class BCDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    BCDetectorConstruction();
   ~BCDetectorConstruction();

  public:

  
    // Reading GDML
    //
    void SetReadFile( const G4String& str );

    // Extended reader
    // for color and other extensions
    G4GDMLReadStructure* fReader;

    // GDMLparser
    //
    G4GDMLParser* fParser;  

   G4VPhysicalVolume* Construct();

//  void FindLogicalVolume( const G4String& fvol );

   // Removed command functions and constant bindings for the G4 geomentry

  
  private:
    

        
    // Read/write Settings
    //
    G4String fReadFile;     

    // Detector Messenger
    //
    BCDetectorMessenger* fdetectorMessenger;


};


// not sure if we need pointers to the physical Electron Dump, dont think so, g4 should do it through parser


//     void DefineMaterials();
//  public:

// removed the getmaterial pointers, however the histogram setup needs to find the physiRadiator 
//and physiElectronDump which points to here through the steppingaction.cc
// Options change the setup 
// or setup geometries so they will have same id.   
// using second option for now.
//     void PrintCalorParameters(); 
// were used to reference g4 built geometries need to find other way to reference if phys naming 
// doesnt work
//     const G4VPhysicalVolume* GetphysiWorld() {return fWorldPhysVol;};           
//     const G4VPhysicalVolume* GetRadiator()   {return physiRadiator;};
//     const G4VPhysicalVolume* GetSweepMagnet()   {return physiSweepMagnet;};
//     const G4VPhysicalVolume* GetElectronDump()        {return physiElectronDump;};
//     const G4VPhysicalVolume* GetPhotonCollimator()        {return physiPhotonCollimator;};
//     const G4VPhysicalVolume* GetBubble()     {return physiBubble;};
//     const G4VPhysicalVolume* GetPhotonDump()     {return physiPhotonDump;};



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
