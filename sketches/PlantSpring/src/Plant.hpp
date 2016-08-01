//
//  Plant.hpp
//  PlantSpring
//
//  Created by Zerc on 8/1/16.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include "ofMain.h"
#include "PlantRig.hpp"

class Plant{
public:
    // rig
    PlantRig rig;
    
    void setup();

    void update();
    
    void draw();
};

#endif /* Plant_hpp */
