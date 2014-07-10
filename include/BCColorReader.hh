//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
//  last updated 707/07/2014 11:10:13 PM 
//  by darren
//
// class BCColorReader
// from g03 example, for testing. it works sometimes we can adjust to our needs, 
// if needed.
// looks like it can do more than just assign color. maybe material .....
// Custom reader for handling "color" tags extensions in GDML.
// -------------------------------------------------------------------------

#ifndef BCColorReader_H
#define BCColorReader_H 1

#include <map>
#include "G4GDMLReadStructure.hh"

class G4VisAttributes;

/// GDML reader for the color attributes

class BCColorReader : public G4GDMLReadStructure
{

 public:

   BCColorReader();
  ~BCColorReader();

   void ExtensionRead(const xercesc::DOMElement* const element);
   void ColorRead(const xercesc::DOMElement* const element);

   G4VisAttributes* GetVisAttribute(const G4String& ref);

 protected:

   virtual void VolumeRead(const xercesc::DOMElement* const);

 private:

   std::map<G4String, G4VisAttributes*> fAttribs;
};

#endif
