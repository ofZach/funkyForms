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
        Color col;
        colors.push_back(col);
        if (i == 0) {
            colors[i].isGrow = true;
        }
        ofRectangle r;
        r.setWidth(0);
        r.setHeight(20);
        colors[i].rect = r;
        colors[i].delay = ofMap(i, 0, colorCounts, 0, 60);
        colors[i].color = pallete[(int)ofRandom(4)];
        colors[i].width = 0;
        colors[i].start = 0;
        colors[i].end = 0;
        colors[i].speed = ofRandom(0.002, 0.02);
        length /= 2;
        colors[i].min = length;
        
    }
    timeCounter = 0;
}
bool iColor::getGrowDone(){
    
    for (int i = 0; i < colors.size(); i++) {
        if( i < colors.size()-1){
            if (!colors[i].isFinished) {
                return false;
            }
        }
    }
    return true;
}
void iColor::update(){
    
    if (isGrow) {
        for (int i = 0; i < colors.size(); i++) {
            Color *c = &colors[i];
            if (i>0) {
                c->rect.alignTo(colors[i-1].rect.getTopRight(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_TOP);
            }
            if(c->isGrow && c->rect.getWidth() < c->min){
                c->rect.width = c->rect.getWidth()+c->speed;
            }
            // check next
            if( i < colors.size()-1){
                if (c->rect.getWidth() >c->min ) {
                    if(!c->isFinished){
                        colors[i+1].isGrow = true;
                    }
                    c->isFinished = true;
                }
            }
            c->start = c->rect.getLeft();
            c->end = c->rect.getRight();
            
            float x = ofMap(c->start, 0, 1, 0, 500);
            ofSetColor(c->color);
            ofDrawCircle(x, 100, 10);
            
            float x2 = ofMap(c->end, 0, 1, 0, 500);
            ofSetColor(c->color);
            ofDrawCircle(x2, 200, 10);
        }
        timeCounter++;
    }else{
        if(isCollapse){
            for (int i = 0; i < colors.size(); i++) {
                Color &c = colors[i];
                c.isFinished = false;
                if (i>0) {
                    c.rect.alignTo(colors[i-1].rect.getTopRight(), OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_TOP);
                }
                if(c.rect.getWidth() > 0.01){
                    c.rect.width = c.rect.getWidth()-c.speed;
                }
                if (i==0) {
                    if(c.rect.width < 0.01){
                        isCollapse = false;
                        isFinished = true;
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
    isFinished = false;
}
void iColor::colapse(){
    isCollapse = true;
    isGrow = false;
}
ofColor iColor::getColorAt(int index){
    for(auto &c: colors){
        float end = ofMap(c.end, 0, 1, 0, indexCount);
        float start = ofMap(c.start, 0, 1, 0, indexCount);
        if (index < end && index >= start) {
            return c.color;
        }
    }
    return baseColor;
}