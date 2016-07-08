//
//  iColor.hpp
//  BlocksOrtho
//
//  Created by Zerc on 7/8/16.
//
//

#ifndef iColor_hpp
#define iColor_hpp

#include "ofMain.h"
class iColor{
private:
    struct Color{
        int delay;
        int start;
        int end;
        int min;
        int speed;
        bool isGrow = false;
        ofColor color;
    };
    vector<Color> colors;
    int colorCounts = 5;
    int timeCounter = 0;
    int indexCount = 0;
    ofColor pallete[9] = {
        ofColor(251,49,1),
        ofColor(190,130,19),
        ofColor(247,198,11),
        ofColor(36,202,144),
        ofColor(164,208,240),
        ofColor(42,137,222),
        ofColor(105,133,166),
        ofColor(3,82,221),
        ofColor(170,178,170)
    };
    bool isGrow = false;
    bool isCollapse = false;
    ofColor baseColor;
public:
    void setup(int _indexCount, ofColor _baseColor);
    void grow();
    void colapse();
    void update();
    ofColor getColorAt(int index);
    void init();
    void reset(){ timeCounter=0; init();}
};

#endif /* iColor_hpp */
