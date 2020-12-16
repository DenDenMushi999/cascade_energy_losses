#include "DetectorConstruction.hh"
#include "DetectorSD.hh"
#include "Constants.hh"

#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Material.hh"
#include "G4SubtractionSolid.hh"
#include "G4AssemblyVolume.hh"

#include "globals.hh"


DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
	G4cout << "\n\n ---- The program in constructor of Detector Construction "
	<< G4endl << G4endl;		
}

DetectorConstruction::~DetectorConstruction()
{
    delete materCsI;
	G4cout << "\n\n ------The program in destructor of Detector Construction  ---- " 
	<< G4endl << G4endl;
}
/*
DetectorSD* DetectorConstruction::getDetectorSD()
{ return aTrackerSD; }
*/

G4VPhysicalVolume* DetectorConstruction::Construct()
{   

    ///////////// Create a materCsI /////////////////////////////////////////
    
    //create an instance of class which from we can get
    //standart materials
    G4NistManager* nist = G4NistManager::Instance();
    G4Element* elemCs = nist->FindOrBuildElement("Cs");
    G4Element* elemI  = nist->FindOrBuildElement("I");
    materCsI    = new G4Material( "CsI(Tl)"  	, 	4.53  * g/cm3 , 2       );
    materCsI    -> AddElement( elemCs ,  5  );
    materCsI    -> AddElement( elemI  ,  5  );
    G4Material* det_mat = nist->FindOrBuildMaterial("CsI(Tl)");
    
    //////////////////////////////////////////////////////////////////////////

    //Выбор материала для мира из предопределенных в Geant4, для зала берем воздух
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    
    //////////////// Create a world ///////////////////////////////////////////

    G4Box* solidWorld = 
    new G4Box("World",
            0.5*world_sizeXY,
            0.5*world_sizeXY,
            0.5*world_sizeZ
    );

    G4LogicalVolume* logicWorld = 
    new G4LogicalVolume(solidWorld,
                        world_mat,
                        "World"
    );

    G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,
                        G4ThreeVector(),
                        logicWorld,
                        "World",
                        0,
                        false,
                        0,
                        checkOverlaps);

    ////////////////////////////////////////////////////////////////////////
    
    //////////// Create a logical volume of strip //////////////////////////
    
    G4Box* solidStrip =
    new G4Box ("strip",
                0.5*strip_sizeXY,
                0.5*strip_sizeXY,
                0.5*strip_sizeZ
    );

    G4LogicalVolume* logicStrip = 
    new G4LogicalVolume (solidStrip,
                         det_mat,
                         "logicStrip");

    
    //////////// Create a logical volume of tungsten borders of strips /////////////////
    
    G4Material* tungsten_mat = nist->FindOrBuildMaterial("G4_W");
    if ( tungsten_mat ) 
    {
        G4cout << "\n~ ~ ~ ~ ~ ~ Found material G4_W! ~ ~ ~ ~ ~ ~ ~ ~ " << G4endl << G4endl;
    }
    else 
    {
        G4cout << "\n~ ~ ~ ~ ~ ~ There are no so-called 'W' material ~ ~ ~ ~ ~ ~ ~ " << G4endl << G4endl;
    }

    G4SubtractionSolid* solidTungstenBorders =
    new G4SubtractionSolid("tungsten Borders", new G4Box("tungsten Box",0.5*(strip_sizeXY+2*tungstenWidth), 0.5*(strip_sizeXY+2*tungstenWidth), 0.5*strip_sizeZ),
                                               new G4Box("tungsten Box",0.5*strip_sizeXY, 0.5*strip_sizeXY, strip_sizeZ)); 
                                               // There was made a alongation on z-axis for exclude wrong subtraction.
                                               // In this way we have a cross-cutting substraction
    
    G4LogicalVolume* logicTungstenBorders = 
    new G4LogicalVolume (solidTungstenBorders,
                        tungsten_mat,
                        "tungsten Borders");
    

    //////////////////////////////////////////////////////////////////////////////////////


    //////////// Create a logical volume of CFRP-grid ///////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    //////////// It is not so simple task! Not finished yet /////////////////////////////
    

    ////////////// Create a single logical volume of line of strips ///////////////////
    /*
    G4AssemblyVolume* lineStrips = new G4AssemblyVolume();
    // Rotation and translation of a plate inside the assembly
    G4RotationMatrix Ra;
    G4ThreeVector Ta;
    G4Transform3D Tr;
    // Rotation of the assembly inside the world
    G4RotationMatrix Rm;

    //G4double airSpace = 0.05*mm;
    //G4double CFRP_width = 0.4*mm
    //G4double edgeCFRP_width = 3*mm;

    G4double allStripsWidth = n_layers*strip_sizeXY;
    G4double x_strip0 = -10.5*strip_sizeXY;
    G4double y_strip0 = 0;
    G4double x_strip = x_strip0;
    
    for (int i=0; i<n_layers; i++) 
    {
        Ta.setX(x_strip); Ta.setY(0.); Ta.setZ( 0.5*strip_sizeZ);        
        x_strip += strip_sizeXY;
        Tr = G4Transform3D(Ra,Ta);
        lineStrips->AddPlacedVolume( logicStrip, Tr);
    }
    */
    ////////////////////////////////////////////////////////////////////////////////////

    /////////// Attempt to place all strips separately /////////////////////////////////

    ////// initial point is in bottom left 
    G4double x_strip0 = -strip_sizeXY*(n_layers/2 - 0.5);
    G4double y_strip0 = -strip_sizeXY*(n_layers/2 - 0.5);
    G4double x_strip = x_strip0;
    G4double y_strip = y_strip0;
    G4double z_strip = -strip_sizeZ;

    int pCopyNo = 0;
    for (int i=0; i<n_layers; i++)
    {
        y_strip = y_strip0;
        for (int j=0; j<n_layers; j++)
        {
            pCopyNo = n_layers*i + j;
            y_strip += strip_sizeXY;
            new G4PVPlacement(0,
                            G4ThreeVector(x_strip, y_strip , 0),
                            logicStrip,
                            "stripPhys",
                            logicWorld,
                            false,
                            pCopyNo,
                            checkOverlaps);
        }
        x_strip += strip_sizeXY;
    }

    ////////////////////////////////////////////////////////////////////////////////////

    /////////// Attempt to place a line of strips //////////////////////////////////////

    /////////////// 1. Attempt of place 1 strip line. succeed /////////////////////////
    /*
    G4double stripX0 = 0.;
    G4double stripY0 = -10.5*strip_sizeXY; 
    G4double streipZ0 = 0.;
    G4ThreeVector Tm( stripX0, stripY0, streipZ0);
    Tr = G4Transform3D(Rm,Tm);
    lineStrips->MakeImprint( logicWorld, Tr );
    */
    ////////////////// 1.1 Attempt of place all line separately (It works, so I don't understand what the problem in 3-rd step is? ) /////////////////////////
    /*
    G4double stripX0 = 0.;
    G4double stripY0 = -10.5*strip_sizeXY; 
    G4double streipZ0 = 0.;
    G4double stripY = stripY0;  
    for (int i=0; i<n_layers; i++)
    {
        G4ThreeVector Tm( stripX0, stripY, streipZ0);
        Tr = G4Transform3D(Rm,Tm);
        lineStrips->MakeImprint( logicWorld, Tr , 0, true);
        stripY += strip_sizeXY;
    }
    */
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////// 2. Attempt to create an assemble of strip lines (unknown result) ///////////////
    /*
    G4AssemblyVolume* gridStrips = new G4AssemblyVolume();

    G4double lineStripsX0 = 0.;
    G4double lineStripsY0 = -10.5*strip_sizeXY;
    G4double lineStreipsZ0 = 0.;
    G4double lineStripsY = lineStripsY0;

    for (int i=0; i<n_layers; i++)
    {
        Ta.setX(0.); Ta.setY(lineStripsY*1.05); Ta.setZ(0.);        
        Tr = G4Transform3D(Ra,Ta);
        lineStripsY += strip_sizeXY;
        lineStrips->AddPlacedAssembly( lineStrips, Tr );
    }
    */
    /////////////// 3. Attempt to place an assemble of ALL strips (unknown result) //////////////
    /*
    G4ThreeVector Tm( 0., 0., 0.);
    Tr = G4Transform3D(Rm,Tm);
    gridStrips->MakeImprint( logicWorld, Tr );
    */
    //////////////////////////////////////////////////////////////////////////////////////


    /////////// Create a full-CsI detector ( like full-metal jacket :)) )//////////////////
    /*
    G4Box* solidDet = 
    new G4Box ("Detector",
            0.5*det_sizeXZ, 0.5*det_sizeY,  0.5*det_sizeXZ
    );

    G4LogicalVolume* logicDet = 
    new G4LogicalVolume(solidDet,
                        det_mat,
                        "Detector");

    // And place it
    /*
    new G4PVPlacement(0,
                    G4ThreeVector(0, -det_sizeY/2, 0),
                    logicDet,
                    "Detector",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);
    */
   /////////////////////////////////////////////////////////////////////////////////////////
    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    G4String CaloSDname = "Calorimeter";
    DetectorSD* CaloSD = new DetectorSD(CaloSDname);
    
    G4SDManager* SDmgr = G4SDManager::GetSDMpointer();
    SDmgr->AddNewDetector(CaloSD);

    SetSensitiveDetector("logicStrip",  // name of logical volume of strip defined in Construct()
                        CaloSD,         // SD object
                        true);          // don't know, maybe it should be false
}   

