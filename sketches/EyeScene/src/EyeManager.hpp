//
//  EyeManager.hpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#ifndef EyeManager_hpp
#define EyeManager_hpp

#include "ofMain.h"
#include "eye.hpp"
#include "particle.h"
class EyeManager{
private:
    vector<particle> particles;
    vector<eye> eyes;
public:
    void setup();
    void update(float x, float y);
    void draw();
};

#endif /* EyeManager_hpp */
