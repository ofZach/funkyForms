#include "renderManager.h"
#include "ofxXmlSettings.h"


//---------------------------------------------------------------
void renderManager::setup(){


    ofxXmlSettings settings;
    settings.load("building/temp.xml");
    settings.pushTag("groups");
    cout << settings.getNumTags("group");
    
    for (int i = 0; i < 6; i++){
        settings.pushTag("group", i);
        
        string name = settings.getValue("name", "");
        //cout << settings.getValue("name", "") << endl;
        vector < ofPolyline > lines;
       
        int nLines = settings.getNumTags("line");
        
        for (int j = 0; j < nLines; j++){
            settings.pushTag("line", j);
            int nPts = settings.getNumTags("pt");
            
            ofPolyline line;
            
            for (int k = 0; k < nPts; k++){
                settings.pushTag("pt", k);
                float x = settings.getValue("x", 0.0f);
                float y = settings.getValue("y", 0.0f);
                float z = settings.getValue("z", 0.0f);
                ofPoint pt(x,y,z);
                line.addVertex(pt);
                
                settings.popTag();
                
            }
            line.setClosed(true);
            lines.push_back(line);
            settings.popTag();
        }

        
        if (name == "edges") edges = lines;
        if (name == "blocks") blocks2 = lines;
        if (name == "pillar") pillar = lines;
        if (name == "engraving") engraving = lines;
        if (name == "6outerWindows") outerWindows = lines;
        if (name == "innerWindows") innerWindows = lines;
        
        
        
        
        settings.popTag();
    }
 //   std::exit(0);
    
    
    for (auto & line : edges){
        ofPolyline lineResample = line.getResampledBySpacing(5);
        edgesResampled.push_back(lineResample);
    }

    for (auto & line : innerWindows){
        ofPolyline lineResample = line.getResampledBySpacing(5);
        innerWindowsResampled.push_back(lineResample);
    }
    
    for (auto & line : outerWindows){
        ofPolyline lineResample = line.getResampledBySpacing(5);
        outerWindowsResampled.push_back(lineResample);
    }
    
   
    for (auto & line : engraving){
        ofPolyline lineResample = line.getResampledBySpacing(5);
        engravingResampled.push_back(lineResample);
    }
    
    for (auto & line : pillar){
        ofPolyline lineResample = line.getResampledBySpacing(5);
        pillarResampled.push_back(lineResample);
    }
    
    for (auto & line : blocks2){
        ofPolyline lineResample = line.getResampledBySpacing(5);
        blocks2Resampled.push_back(lineResample);
    }
    
    
    
    
   // blocks.load("building/blocks.svg");
   // windows.load("building/main-window.svg");
    
    
    float width = 2100;
    float scale = RENDER_WIDTH / width;
    
    fbo.allocate(RENDER_WIDTH, RENDER_HEIGHT, GL_RGBA, 4);
    
    fbo.begin();
    ofClear(0,0,0,255);
    ofLine(0,0,RENDER_WIDTH, RENDER_HEIGHT);
    ofPushMatrix();
    ofScale(scale, scale);
    
    //blocks.draw();
    
    
//    ofSetLineWidth(10);
//    for (int i = 0; i < blocks.getNumPath(); i++){
//        ofSetColor(255);
//        ofPath p = blocks.getPathAt(i);
//        ofPolyline pp = p.getOutline()[0];
//        pp.draw();
//        
//    }
    
    ofSetLineWidth(1);
    ofPopMatrix();
    
    
    ofRectangle rect = getRectForScreen(SCREEN_LEFT);
    
    ofLine(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
    
    fbo.end();
    
    
    

    
    //building/anotherTry.svg
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
        case SCREEN_TABLE:
            which = 4;
            break;
    }
    
    if (which != 4){
        float width = 2100; //blocks.getWidth();
        float scale = RENDER_WIDTH / width;
        
        //ofPath p = blocks2.getPathAt(which);
        ofPolyline pp = blocks2[which];
        ofRectangle rect = pp.getBoundingBox();
        
        rect.x *= scale;
        rect.y *= scale;
        rect.width *= scale;
        rect.height *= scale;
        
        return rect;
    } else {
        
        //float width = 2100; //blocks.getWidth();
       // float scale = RENDER_WIDTH / width;
        
        ofRectangle table(0,0,500,50);
        ofRectangle myBounds = getWholeRectangle(); //(0,0,2100, 2100*(RENDER_ASPECT));
        
      //  myBounds.x *= scale;
      //  myBounds.y *= scale;
      //  myBounds.width *= scale;
      //  myBounds.height *= scale;
     //
        table.scaleTo(myBounds);
        //table.y = myBounds.getHeight() - table.height;
    
        table.scaleFromCenter(3.0);
        table.y = myBounds.getHeight() - table.height;
        
        return table;
    }
}

void renderManager::drawBuidling(){
    ofSetColor(255);
    
    for (auto & a : innerWindows){
        //cout << a.getBoundingBox() << endl;
        a.draw();
    }
    for (auto & a : outerWindows){
        a.draw();
    }
    
    for (auto & a : engraving){
        a.draw();
    }
    
    for (auto & a : pillar){
        a.draw();
    }
    
    for (auto & a : blocks2){
        a.draw();
    }
    
    for (auto & a : edges){
        a.draw();
    }

}


//---------------------------------------------------------------
void renderManager::draw(){
    
    fbo.draw(0,0);
}