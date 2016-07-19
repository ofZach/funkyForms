//
//  iColor.cpp
//  BlocksOrtho
//
//  Created by Zerc on 7/8/16.
//
//

#include "iColor.hpp"
void iColor::setup(float _indexCount, ofColor _baseColor){
    indexCount = _indexCount;
    baseColor = _baseColor;
    init();
}
void iColor::init(){
    colors.clear();
    length = 1;
    for (int i = 0; i < colorCounts; i++) {
        Color c;
        if (i == 0) {
            c.isGrow = true;
        }
        ofRectangle r;
        r.setWidth(0);
        r.setHeight(20);
        c.rect = r;
        c.delay = ofMap(i, 0, colorCounts, 0, 60);
        c.color = pallete[(int)ofRandom(4)];
        c.width = 0;
        c.start = 0;
        c.end = 0;
        c.speed = ofRandom(0.007, 0.02);
        length /= 2;
        c.min = length;
        colors.push_back(c);
    }
    timeCounter = 0;
}
void iColor::update(){
    if (isGrow) {
        for (int i = 0; i < colors.size(); i++) {
            Color &c = colors[i];
            if (i>0) {
                c.rect.alignTo(colors[i-1].rect.getTopRight(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_TOP);
            }
            if(c.isGrow && c.rect.getWidth() < c.min){
                c.rect.width = c.rect.getWidth()+c.speed;
            }
            // check next
            if( i < colors.size()-1){
                if (c.rect.getWidth() > c.min ) {
                    if(!c.isFinished){
                        colors[i+1].isGrow = true;
                    }
                    c.isFinished = true;
                }
            }
            c.start = c.rect.getLeft();
            c.end = c.rect.getRight();
            
            float x = ofMap(c.start, 0, 1, 0, 500);
            ofSetColor(c.color);
            ofDrawCircle(x, 100, 10);
            
            float x2 = ofMap(c.end, 0, 1, 0, 500);
            ofSetColor(c.color);
            ofDrawCircle(x2, 200, 10);
        }
        timeCounter++;
    }else{
        if(isCollapse){
            for (int i = 0; i < colors.size(); i++) {
                Color &c = colors[i];
                if (i>0) {
                    c.rect.alignTo(colors[i-1].rect.getTopRight(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_TOP);
                }
                if(c.rect.getWidth() > 0.01){
                    c.rect.width = c.rect.getWidth()-c.speed;
                }
                if (i==0) {
                    if(c.rect.width < 0.01){
                        isCollapse = false;
                        init();
                    }
                    
                }
                c.start = c.rect.getLeft();
                c.end = c.rect.getRight();
                
                float x = ofMap(c.start, 0, 1, 0, 500);
                ofSetColor(c.color);
                ofDrawCircle(x, 0, 10);
                
                float x2 = ofMap(c.end, 0, 1, 0, 500);
                ofSetColor(c.color);
                ofDrawCircle(x2, 0, 10);
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