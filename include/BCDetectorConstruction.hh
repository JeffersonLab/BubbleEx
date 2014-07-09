//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 7/8/2014 11:00:52 PM  
//  by darren
//
// Constructs the Detector('s). Here we set the gdml parser to read the gdml 
// files which contain the geometry. All old geometry beamline, radiator, bubble
// , photondump have been removed and put into gdml along with the other 
// geometry.
//
// The sweep magnet and edump need to be created in gdml. the geometry was 
// commented out and not being used. the commands and functions were removed
// mainly because for them to work now they would have to be adjusted
// to fit with gdml reading. when needed these can be recreated but so that they
// are functional with the gdml geometry.
// most of what was available were commands to adjust setting such as lenght, 
// material of geometry, set magnetic field and other properties.
// If needed we can also setup the write command to work
// with these so that G4 writes the gdml after adjustment.
//
// The modifications to the files generally follow from the G4 examples G01-4.
// Other sources which seem to have followed these examples are remoll and 
// hmolpol (which has good notes for figuring out what is happening)
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
// 
// constructs the detectors or links to them in gdml through the method
// gdml parser defined here. also sets any other reading, writing 
// capabilities such as properties of detectors. 
// Auxillary capabilities ,
// define materials ,
// magfields,
// color reading and defining (which I cant seem to get to work on a large scale
// file but works on smaller files)
// are also defined here if needed
// 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//

// constructs detector

#include "BCDetectorConstruction.hh"



// Geant4 includes

//

#include "globals.hh"

#include "G4GeometryManager.hh"

#include "G4VisAttributes.hh"

#include "G4Color.hh"



// Materials

//

#include "G4Material.hh"

#include "G4NistManager.hh"



// Geometry includes

#include "G4LogicalVolume.hh"

#include "G4VPhysicalVolume.hh"

#include "G4PVPlacement.hh"

#include "G4Box.hh"

#include "G4Tubs.hh"

#include "G4PVReplica.hh"

#include "G4ExtrudedSolid.hh"

#include "G4PhysicalVolumeStore.hh"

#include "G4LogicalVolumeStore.hh"

#include "G4SolidStore.hh"



// Messenger

//

#include "BCDetectorMessenger.hh"



// GDML parser include

//

#include "G4GDMLParser.hh"



#include "G4PhysicalConstants.hh"

#include "G4SystemOfUnits.hh"



#include "G4UniformMagField.hh"

#include "G4FieldManager.hh"

#include "G4TransportationManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

// set for sensdata
#include "BCSensitiveDetector.hh"
#include "G4SDManager.hh"

// Color extension included for reading
#include "BCColorReader.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BCDetectorConstruction::BCDetectorConstruction()

{

// set default file to read    
  fReadFile = "geometry/BubbleMother.gdml";

  fReader = new BCColorReader;
  fParser = new G4GDMLParser(fReader);

    // passing info between classes
  fdetectorMessenger = new BCDetectorMessenger(this);

}
// Destructor
//
BCDetectorConstruction::~BCDetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// creates geometry of actual system

G4VPhysicalVolume* BCDetectorConstruction::Construct()
{ 

  // Reading of Geometry from GDML
  // sets the world to PV
	G4VPhysicalVolume* fWorldPhysVol;

// sets parser with overlap check if true and in Read( false gives skip schema 
// check)
//  fParser.SetOverlapCheck(true);

  fParser->Read(fReadFile,false);
  // Prints the material information
  //
  G4cout << *(G4Material::GetMaterialTable() ) << G4endl;

  // Giving World Physical Volume from GDML Parser
  //
  fWorldPhysVol = fParser->GetWorldVolume();

 // Auxiliary Information 
// sets the options for auxiliary information not otherwise covered or 
// set such as color, setting sensitive detectors, ....
   // can add in color and other abilities, see g4 examples, remoll, 
   // and hmolpol. 
   // 
// base requirements start here

// tells g4 aux tag exists on volume

   const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
   std::cout << "Found " << auxmap->size()
             << " volume(s) with auxiliary information."
             << G4endl << G4endl;

// then goes through tagged volumes to give list of what was found 
   for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
       iter!=auxmap->end(); iter++) 
   {
     G4cout << "Volume " << ((*iter).first)->GetName()
            << " has the following list of auxiliary information: "
            << G4endl << G4endl;
     for (G4GDMLAuxListType::const_iterator 
     vit=(*iter).second.begin();
          vit!=(*iter).second.end();vit++)
     {
     //
	std::cout << "--> Type: " << (*vit).type
                 << " Value: " << (*vit).value << std::endl;
// end base requirements for Aux option now define those options and response
// if found here.
// follows from g04 gdml_ext.cc and remoll with help from hmolpol's notes

// using the standered options in the gui settings for display
       if ((*vit).type == "Visibility")
      { 
// refreshes color if exists, down below, then sets visibility properties
// show, hide, wireframe. can add others but just needed hide right now.
        G4Color color(1.0,1.0,1.0);
           const G4VisAttributes* visAttribute_old =
            ((*iter).first)->GetVisAttributes();
 
        if (visAttribute_old)
          color = visAttribute_old->GetColor();
   // set aux values and response here 
        G4VisAttributes visAttribute_new(color);
        if ((*vit).value == "show")  
          visAttribute_new.SetVisibility(true);
        if ((*vit).value == "hide") 
          visAttribute_new.SetVisibility(false);
        if ((*vit).value == "wireframe") 
          visAttribute_new.SetForceWireframe(true);
   
        ((*iter).first)->SetVisAttributes(visAttribute_new);
      }
     if ((*vit).type == "Color")
      {
// changes or assigns color. have to use predefined color (white, black, red,
// green, blue, cyan. magenta, grey, yellow, brown and I think i missed one)
// can set option for defining colors but have to create code and define the 
// setup

        G4Color color(1.0,1.0,1.0,1.0);
      if (G4Color::GetColour((*vit).value, color))
        {
          G4cout << "Setting color to " << (*vit).value << "." << G4endl;
               G4VisAttributes visAttribute(color);          
          ((*iter).first)->SetVisAttributes(visAttribute);
        } else
        {
          G4cout << "Color " << (*vit).value << " is not known." << G4endl;
        }
       }
     
// allows for setting or changing opaque value. scale is 0-1.0. 
      if ((*vit).type == "Alpha")
      {  
        G4Color color(1.0,1.0,1.0);
          const G4VisAttributes* visAttribute_old =
            ((*iter).first)->GetVisAttributes();

        if (visAttribute_old)
          color = visAttribute_old->GetColor();
        G4Color color_new( color.GetRed(), color.GetGreen(), color.GetBlue(),
            std::atof((*vit).value.c_str())); 

        G4VisAttributes visAttribute_new(color_new);
    
        ((*iter).first)->SetVisAttributes(visAttribute_new);
      }
      
  // end of the visible option we have.
    //   
     // added the "SensDet" auxiliary originally to make sure the physicalvolume
 // names were constant to allow for bindings and histogram output. however 
// looks like assigning the names can be done in gdml, see gdml file.
// keeping in though since it is here.

   // Sensitive detectors
   // allows for tracking of hits
   //------------------------------------------------ 

 // attaches to volume finds name in list made above   
// gives it name SDv"auxvalue"
        if ((*vit).type=="SensDet")
       {
              G4SDManager* SDman = G4SDManager::GetSDMpointer();
   G4String trackerChamberSDname = "SDv"+(*vit).value;
   BCSensitiveDetector* aTrackerSD = new BCSensitiveDetector(trackerChamberSDname);
   SDman->AddNewDetector( aTrackerSD );
         
         G4cout << "Attaching sensitive detector " << (*vit).value
                << " to volume " << ((*iter).first)->GetName()
                <<  G4endl << G4endl;

         G4VSensitiveDetector* mydet = SDman->FindSensitiveDetector((*vit).value);
         if(mydet) 
         {
           G4LogicalVolume* myvol = (*iter).first;
           myvol->SetSensitiveDetector(mydet);
         }
         else
         {
           G4cout << (*vit).value << " detector not found" << G4endl;
         }
       }
     }
   }
   //
   // End of Auxiliary Information block

         

   return fWorldPhysVol;
}

void BCDetectorConstruction::SetReadFile( const G4String& str )
{
  fReadFile= str;
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// can reimplement define materials inorder to make changing material easier in
// gui if needed other wise if nist manager for gdml works can use it.
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void DetectorConstruction::DefineMaterials()
//{ 
//// use G4-NIST materials data base
////
//G4NistManager* man = G4NistManager::Instance();
//defaultMaterial = man->FindOrBuildMaterial("G4_Galactic");
//man->FindOrBuildMaterial("G4_Cu");
//man->FindOrBuildMaterial("G4_Al");
//man->FindOrBuildMaterial("G4_WATER");
//man->FindOrBuildMaterial("G4_AIR");
//man->FindOrBuildMaterial("G4_NITROUS_OXIDE");

//// define gas material at non STP conditions (density=0.846g/cm3, T=-5 C (268.15 K), P=60 atm)
// G4double density = 0.846*g/cm3;
// SuperHeatLiquid = 
//   man->BuildMaterialWithNewDensity("SuperHeatLiquid","G4_NITROUS_OXIDE",density,268.15*kelvin,60.0*atmosphere);

//// print table
////
//G4cout << *(G4Material::GetMaterialTable()) << G4endl;
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// code that needs to be reintegrated with correct gdml file and bindings to work
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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

//void DetectorConstruction::SetMagField(G4double fieldValue)
//{
//  //apply a global uniform magnetic field along Z axis
//  // we have it set for detector not global
//  // G4FieldManager* fieldMgr
//  //   = G4TransportationManager::GetTransportationManager()->GetFieldManager();

//  //apply a local uniform magnetic field along Z axis
//  G4FieldManager* fieldMgr = new G4FieldManager(magField);
//  
//  if(magField) delete magField;		//delete the existing magn field
//  
//  if(fieldValue!=0.)			// create a new one if non nul
//    { magField = new G4UniformMagField(G4ThreeVector(0.,0.,fieldValue));
//      fieldMgr->SetDetectorField(magField);
//      fieldMgr->CreateChordFinder(magField);
//      
//      // Set magnetic field in Sweep Magnet and its daughters:
//      G4bool allLocal = true ;
//      //      logicSweepMagnet->SetFieldManager(fieldMgr, allLocal) ;
//      //

//    } else {
//    magField = 0;
//    fieldMgr->SetDetectorField(magField);
//  }
//}

