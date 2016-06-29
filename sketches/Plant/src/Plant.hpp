//
//  Plant.hpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include "ofMain.h"
#include "SvgPlant.hpp"

class Plant{
public:
    vector<SvgPlant> svgplants;
    void setup();
    void update();
    void draw();
};

#endif /* Plant_hpp */
