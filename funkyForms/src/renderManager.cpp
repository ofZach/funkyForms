#include "renderManager.h"



//---------------------------------------------------------------
void renderManager::setup(){

    blocks.load("building/blocks.svg");
    
    float width = blocks.getWidth();
    float scale = RENDER_WIDTH / width;
    
    fbo.allocate(RENDER_WIDTH, RENDER_HEIGHT, GL_RGBA, 4);
    
    fbo.begin();
    ofClear(0,0,0,255);
    ofLine(0,0,RENDER_WIDTH, RENDER_HEIGHT);
    ofPushMatrix();
    ofScale(scale, scale);
    
    //blocks.draw();
    
    
    ofSetLineWidth(10);
    for (int i = 0; i < blocks.getNumPath(); i++){
        ofSetColor(255);
        ofPath p = blocks.getPathAt(i);
        ofPolyline pp = p.getOutline()[0];
        pp.draw();
        
    }
    
    ofSetLineWidth(1);
    ofPopMatrix();
    
    
    ofRectangle rect = getRectForScreen(SCREEN_LEFT);
    cout << rect << endl;
    
    ofLine(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
    
    fbo.end();
}


//---------------------------------------------------------------
void renderManager::update(){
}


ofRectangle renderManager::getRectForScreen( screenName name ){
    
    // 0 = left
    // 1 = right
    // 2 = center
    // 3 = top
    
    int which = 0;
    switch (name){
        case SCREEN_LEFT:
            which = 0;
            break;
        case SCREEN_RIGHT:
            which = 1;
            break;
        case SCREEN_CENTER:
            which = 2;
            break;
        case SCREEN_TOP:
            which = 3;
            break;
    }
    
    float width = blocks.getWidth();
    float scale = RENDER_WIDTH / width;
    
    ofPath p = blocks.getPathAt(which);
    ofPolyline pp = p.getOutline()[0];
    ofRectangle rect = pp.getBoundingBox();
    
    rect.x *= scale;
    rect.y *= scale;
    rect.width *= scale;
    rect.height *= scale;
    
    return rect;
    
}


//---------------------------------------------------------------
void renderManager::draw(){
    
    fbo.draw(0,0);
}