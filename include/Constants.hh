/// \file Constants.hh
/// \brief Definition of constants.

#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"

//constexpr G4double CFRP_width = 0.4*mm
//constexpr G4double edgeCFRP_width = 3*mm;

constexpr int n_layers = 22;
constexpr G4double det_sizeXZ = 80*cm, det_sizeY = 25*cm;

constexpr G4double world_sizeXY = 120*cm; //Размер по x и y здесь будут одинаковы - ширина и высота
constexpr G4double world_sizeZ  = 80*cm; //Размер по z - толщина

constexpr G4double strip_sizeXY = 36*mm;
constexpr G4double strip_sizeZ = 296*mm;

//constexpr G4double airSpace = 0.05*mm;
constexpr G4double tungstenWidth = 0.1*mm;
constexpr G4bool checkOverlaps = false;

#endif