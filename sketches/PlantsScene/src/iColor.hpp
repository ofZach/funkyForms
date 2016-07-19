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
    
    int timeCounter = 0;
    float indexCount = 0;
    ofColor pallete[4] = {
        ofColor::cadetBlue,
        ofColor::lightPink,
        ofColor::lightYellow,
        ofColor::lightCoral
    };
//    ofColor pallete[9] = {
//        ofColor(251,49,1),
//        ofColor(190,130,19),
//        ofColor(247,198,11),
//        ofColor(36,202,144),
//        ofColor(164,208,240),
//        ofColor(42,137,222),
//        ofColor(105,133,166),
//        ofColor(3,82,221),
//        ofColor(170,178,170)
//    };
    bool isGrow = false;
    bool isCollapse = false;
    ofColor baseColor;
    int colorCounts = 5;
    float length;
    bool isFinished = false;
public:
    struct Color{
        ofRectangle rect;
        int delay;
        float start;
        float end;
        float min;
        float speed;
        float width;
        bool isFinished = false;
        bool isGrow = false;
        ofColor color;
    };
    vector<Color> colors;
    void setup(float _indexCount, ofColor _baseColor);
    int getColorCount(){return colorCounts;}
    bool getFinished(){return isFinished;}
    Color *getColor(int index){return &colors[index];}
    void grow();
    void colapse();
    void update();
    ofColor getColorAt(int index);
    void init();
    void reset(){ timeCounter=0; init();}
};

#endif /* iColor_hpp */
