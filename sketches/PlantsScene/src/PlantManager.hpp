//
//  PlantManager.hpp
//  PlantsScene
//
//  Created by Zerc on 7/18/16.
//
//

#ifndef PlantManager_hpp
#define PlantManager_hpp

#include "ofMain.h"
#include "inputManager.h"
#include "Plant.hpp"

class PlantManager{
public:
    class Anchor{
        ofVec2f pos;
        vector<Plant> plants;
    };

    vector<Plant> plants;
    inputManager *IM;
    void setup(inputManager *_IM);
    void onNewTarget();
    void update();
    void draw();
};

#endif /* PlantManager_hpp */
