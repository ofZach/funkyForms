

#pragma once


#include "ofMain.h"
#include "cvManager.h"


class baseScene {
    
    
public:
    
    virtual void setup(){}
    virtual void update(){}
    virtual void draw(){}
    
    virtual void stop(){}
    virtual void start(){}
    
    virtual void blobBorn(int id){}
    virtual void blobDied(int id){}
    
    cvPacket * cvData;
    

};


