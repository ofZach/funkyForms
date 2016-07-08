//
//  iColor.cpp
//  BlocksOrtho
//
//  Created by Zerc on 7/8/16.
//
//

#include "iColor.hpp"
void iColor::setup(int _indexCount, ofColor _baseColor){
    indexCount = _indexCount;
    baseColor = _baseColor;
    init();
}
void iColor::init(){
    colors.clear();
    for (int i = 0; i < colorCounts; i++) {
        Color c;
        if(i==colorCounts-1){ // make last first color
            c.delay = 0;
        }else{
            c.delay = ofRandom(1, 100);
        }
        c.color = pallete[(int)ofRandom(9)];
        c.start = 0;
        c.end = 0;
        c.speed = ofRandom(1, 3);
        c.min = ofMap(i, 0, colorCounts, 0, indexCount);
        colors.push_back(c);
    }
    timeCounter = 0;
}
void iColor::update(){
    if (isGrow) {
        for (int i = 0; i < colors.size(); i++) {
            Color &c = colors[i];
            if (c.delay == timeCounter) c.isGrow = true;
            if(i<colors.size()-1){
                if(c.isGrow && c.end < c.min) c.end+=c.speed;
            }else{
                if(c.isGrow && c.end < indexCount) c.end+=c.speed;
            }
            if(i>0) c.start = colors[i-1].end;
        }
        timeCounter++;
    }else{
        if(isCollapse){
            for (int i = 0; i < colors.size(); i++) {
                Color &c = colors[i];
                if(i == colors.size()-1){
                    if(c.end == 0){
                        isCollapse = false;
                        init();
                    }
                }
                if(c.end > 0) c.end-=10;
                if(i>0) c.start = colors[i-1].end;
            }
        }
    }
}
void iColor::grow(){
    isGrow = true;
}
void iColor::colapse(){
    isCollapse = true;
   isGrow = false;
}
ofColor iColor::getColorAt(int index){
    for(auto &c: colors){
        if (index < c.end && index >= c.start) {
            return c.color;
        }
    }
    return baseColor;
}