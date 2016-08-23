#include "paintScene.h"

#define SIMPLEX_IMPLEMENTATION

#include "Simplex.h"

using namespace Simplex;

bool compareName( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.name < s2.name;
}

bool compareBrightness( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getBrightness() < s2.color.getBrightness();
}

bool compareHue( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getHue() < s2.color.getHue();
}

bool compareSaturation( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getSaturation() < s2.color.getSaturation();
}



void paintScene::setup(){
    
    simplexImage.allocate(256, 256, OF_IMAGE_GRAYSCALE);
    simplexImage2.allocate(256, 256, OF_IMAGE_GRAYSCALE);
    
    lineFbo.allocate(RM->getWholeRectangle().width, RM->getWholeRectangle().height, GL_RGBA, 4);
    
    lineFbo2.allocate(RM->getWholeRectangle().width, RM->getWholeRectangle().height, GL_RGBA, 4);
    
    rockImage.loadImage("sceneAssets/paint/stone.jpg");
    
    shader.load("sceneAssets/paint/shader/shader");
    
    lineFbo.begin();
    ofClear(0,0,0,255);
    lineFbo.end();
    
    //paint/stone_rocky_surface_texture.jpg
    
    
    
    colorNameMap["white"] = ofColor::white;
    colorNameMap["gray"] = ofColor::gray;
    colorNameMap["black"] = ofColor::black;
    colorNameMap["red"] = ofColor::red;
    colorNameMap["green"] = ofColor::green;
    colorNameMap["blue"] = ofColor::blue;
    colorNameMap["cyan"] = ofColor::cyan;
    colorNameMap["magenta"] = ofColor::magenta;
    colorNameMap["yellow"] = ofColor::yellow;
    colorNameMap["aliceBlue"] = ofColor::aliceBlue;
    colorNameMap["antiqueWhite"] = ofColor::antiqueWhite;
    colorNameMap["aqua"] = ofColor::aqua;
    colorNameMap["aquamarine"] = ofColor::aquamarine;
    colorNameMap["azure"] = ofColor::azure;
    colorNameMap["beige"] = ofColor::beige;
    colorNameMap["bisque"] = ofColor::bisque;
    colorNameMap["blanchedAlmond"] = ofColor::blanchedAlmond;
    colorNameMap["blueViolet"] = ofColor::blueViolet;
    colorNameMap["brown"] = ofColor::brown;
    colorNameMap["burlyWood"] = ofColor::burlyWood;
    colorNameMap["cadetBlue"] = ofColor::cadetBlue;
    colorNameMap["chartreuse"] = ofColor::chartreuse;
    colorNameMap["chocolate"] = ofColor::chocolate;
    colorNameMap["coral"] = ofColor::coral;
    colorNameMap["cornflowerBlue"] = ofColor::cornflowerBlue;
    colorNameMap["cornsilk"] = ofColor::cornsilk;
    colorNameMap["crimson"] = ofColor::crimson;
    colorNameMap["darkBlue"] = ofColor::darkBlue;
    colorNameMap["darkCyan"] = ofColor::darkCyan;
    colorNameMap["darkGoldenRod"] = ofColor::darkGoldenRod;
    colorNameMap["darkGray"] = ofColor::darkGray;
    colorNameMap["darkGrey"] = ofColor::darkGrey;
    colorNameMap["darkGreen"] = ofColor::darkGreen;
    colorNameMap["darkKhaki"] = ofColor::darkKhaki;
    colorNameMap["darkMagenta"] = ofColor::darkMagenta;
    colorNameMap["darkOliveGreen"] = ofColor::darkOliveGreen;
    colorNameMap["darkorange"] = ofColor::darkorange;
    colorNameMap["darkOrchid"] = ofColor::darkOrchid;
    colorNameMap["darkRed"] = ofColor::darkRed;
    colorNameMap["darkSalmon"] = ofColor::darkSalmon;
    colorNameMap["darkSeaGreen"] = ofColor::darkSeaGreen;
    colorNameMap["darkSlateBlue"] = ofColor::darkSlateBlue;
    colorNameMap["darkSlateGray"] = ofColor::darkSlateGray;
    colorNameMap["darkSlateGrey"] = ofColor::darkSlateGrey;
    colorNameMap["darkTurquoise"] = ofColor::darkTurquoise;
    colorNameMap["darkViolet"] = ofColor::darkViolet;
    colorNameMap["deepPink"] = ofColor::deepPink;
    colorNameMap["deepSkyBlue"] = ofColor::deepSkyBlue;
    colorNameMap["dimGray"] = ofColor::dimGray;
    colorNameMap["dimGrey"] = ofColor::dimGrey;
    colorNameMap["dodgerBlue"] = ofColor::dodgerBlue;
    colorNameMap["fireBrick"] = ofColor::fireBrick;
    colorNameMap["floralWhite"] = ofColor::floralWhite;
    colorNameMap["forestGreen"] = ofColor::forestGreen;
    colorNameMap["fuchsia"] = ofColor::fuchsia;
    colorNameMap["gainsboro"] = ofColor::gainsboro;
    colorNameMap["ghostWhite"] = ofColor::ghostWhite;
    colorNameMap["gold"] = ofColor::gold;
    colorNameMap["goldenRod"] = ofColor::goldenRod;
    colorNameMap["grey"] = ofColor::grey;
    colorNameMap["greenYellow"] = ofColor::greenYellow;
    colorNameMap["honeyDew"] = ofColor::honeyDew;
    colorNameMap["hotPink"] = ofColor::hotPink;
    colorNameMap["indianRed "] = ofColor::indianRed ;
    colorNameMap["indigo "] = ofColor::indigo ;
    colorNameMap["ivory"] = ofColor::ivory;
    colorNameMap["khaki"] = ofColor::khaki;
    colorNameMap["lavender"] = ofColor::lavender;
    colorNameMap["lavenderBlush"] = ofColor::lavenderBlush;
    colorNameMap["lawnGreen"] = ofColor::lawnGreen;
    colorNameMap["lemonChiffon"] = ofColor::lemonChiffon;
    colorNameMap["lightBlue"] = ofColor::lightBlue;
    colorNameMap["lightCoral"] = ofColor::lightCoral;
    colorNameMap["lightCyan"] = ofColor::lightCyan;
    colorNameMap["lightGoldenRodYellow"] = ofColor::lightGoldenRodYellow;
    colorNameMap["lightGray"] = ofColor::lightGray;
    colorNameMap["lightGrey"] = ofColor::lightGrey;
    colorNameMap["lightGreen"] = ofColor::lightGreen;
    colorNameMap["lightPink"] = ofColor::lightPink;
    colorNameMap["lightSalmon"] = ofColor::lightSalmon;
    colorNameMap["lightSeaGreen"] = ofColor::lightSeaGreen;
    colorNameMap["lightSkyBlue"] = ofColor::lightSkyBlue;
    colorNameMap["lightSlateGray"] = ofColor::lightSlateGray;
    colorNameMap["lightSlateGrey"] = ofColor::lightSlateGrey;
    colorNameMap["lightSteelBlue"] = ofColor::lightSteelBlue;
    colorNameMap["lightYellow"] = ofColor::lightYellow;
    colorNameMap["lime"] = ofColor::lime;
    colorNameMap["limeGreen"] = ofColor::limeGreen;
    colorNameMap["linen"] = ofColor::linen;
    colorNameMap["maroon"] = ofColor::maroon;
    colorNameMap["mediumAquaMarine"] = ofColor::mediumAquaMarine;
    colorNameMap["mediumBlue"] = ofColor::mediumBlue;
    colorNameMap["mediumOrchid"] = ofColor::mediumOrchid;
    colorNameMap["mediumPurple"] = ofColor::mediumPurple;
    colorNameMap["mediumSeaGreen"] = ofColor::mediumSeaGreen;
    colorNameMap["mediumSlateBlue"] = ofColor::mediumSlateBlue;
    colorNameMap["mediumSpringGreen"] = ofColor::mediumSpringGreen;
    colorNameMap["mediumTurquoise"] = ofColor::mediumTurquoise;
    colorNameMap["mediumVioletRed"] = ofColor::mediumVioletRed;
    colorNameMap["midnightBlue"] = ofColor::midnightBlue;
    colorNameMap["mintCream"] = ofColor::mintCream;
    colorNameMap["mistyRose"] = ofColor::mistyRose;
    colorNameMap["moccasin"] = ofColor::moccasin;
    colorNameMap["navajoWhite"] = ofColor::navajoWhite;
    colorNameMap["navy"] = ofColor::navy;
    colorNameMap["oldLace"] = ofColor::oldLace;
    colorNameMap["olive"] = ofColor::olive;
    colorNameMap["oliveDrab"] = ofColor::oliveDrab;
    colorNameMap["orange"] = ofColor::orange;
    colorNameMap["orangeRed"] = ofColor::orangeRed;
    colorNameMap["orchid"] = ofColor::orchid;
    colorNameMap["paleGoldenRod"] = ofColor::paleGoldenRod;
    colorNameMap["paleGreen"] = ofColor::paleGreen;
    colorNameMap["paleTurquoise"] = ofColor::paleTurquoise;
    colorNameMap["paleVioletRed"] = ofColor::paleVioletRed;
    colorNameMap["papayaWhip"] = ofColor::papayaWhip;
    colorNameMap["peachPuff"] = ofColor::peachPuff;
    colorNameMap["peru"] = ofColor::peru;
    colorNameMap["pink"] = ofColor::pink;
    colorNameMap["plum"] = ofColor::plum;
    colorNameMap["powderBlue"] = ofColor::powderBlue;
    colorNameMap["purple"] = ofColor::purple;
    colorNameMap["rosyBrown"] = ofColor::rosyBrown;
    colorNameMap["royalBlue"] = ofColor::royalBlue;
    colorNameMap["saddleBrown"] = ofColor::saddleBrown;
    colorNameMap["salmon"] = ofColor::salmon;
    colorNameMap["sandyBrown"] = ofColor::sandyBrown;
    colorNameMap["seaGreen"] = ofColor::seaGreen;
    colorNameMap["seaShell"] = ofColor::seaShell;
    colorNameMap["sienna"] = ofColor::sienna;
    colorNameMap["silver"] = ofColor::silver;
    colorNameMap["skyBlue"] = ofColor::skyBlue;
    colorNameMap["slateBlue"] = ofColor::slateBlue;
    colorNameMap["slateGray"] = ofColor::slateGray;
    colorNameMap["slateGrey"] = ofColor::slateGrey;
    colorNameMap["snow"] = ofColor::snow;
    colorNameMap["springGreen"] = ofColor::springGreen;
    colorNameMap["steelBlue"] = ofColor::steelBlue;
    colorNameMap["tan"] = ofColor::tan;
    colorNameMap["teal"] = ofColor::teal;
    colorNameMap["thistle"] = ofColor::thistle;
    colorNameMap["tomato"] = ofColor::tomato;
    colorNameMap["turquoise"] = ofColor::turquoise;
    colorNameMap["violet"] = ofColor::violet;
    colorNameMap["wheat"] = ofColor::wheat;
    colorNameMap["whiteSmoke"] = ofColor::whiteSmoke;
    colorNameMap["yellowGreen"] = ofColor::yellowGreen;
    
    // this map is useful if we want to address the colors by string.
    // since we might want to sort this, we can put them in a vector also
    
    for (unsigned int i = 0; i < colorNameMap.size(); i++){
        
        map<string, ofColor>::iterator mapEntry = colorNameMap.begin();
        std::advance( mapEntry, i );
        
        colorNameMapping mapping;
        mapping.name = mapEntry->first;
        mapping.color = mapEntry->second;
        colorNames.push_back(mapping);
        
    }
    
    
    ofSort(colorNames, compareBrightness);
    
    
    const float time = ofGetElapsedTimef();
    
    unsigned char * pix = simplexImage.getPixels().getData();
    for (int i = 0; i < 256 *256; i++){
        
        int x = i % 256;
        int y = i / 256;
        
        pix[i] =  ofNoise(x*0.03, y * 0.03, time*0.3) * 200 + ofNoise(x*0.04, y * 0.04, time*0.3) * 50;
        
    }
    
    simplexImage.update();
    
    
    unsigned char * pix2 = simplexImage2.getPixels().getData();
    for (int i = 0; i < 256 *256; i++){
        
        int x = i % 256;
        int y = i / 256;
        
        pix2[i] =  ofNoise(x*0.03, y * 0.03, time*0.3, 100000) * 200 + ofNoise(x*0.04, y * 0.04, time*0.3, 100000) * 50;
        
    }
    
    simplexImage2.update();
    

}

void paintScene::update(){
 
    
    
    if (ofGetFrameNum() % 100 == 0){
        shader.load("sceneAssets/paint/shader/shader");
    }
    
    
    meshes.clear();
    //fBm( dfBm( ofVec3f(position.x*0.3, position.y*0.3, time*0.1) ) ) * 0.5f + 0.5f;
}



void paintScene::draw(){

    
    
    lineFbo.begin();
    //ofClear(255,255,255,255);
    ofSetColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255), ofRandom(0,200));
    
    
    ofFill();
    
    ofCircle(ofGetWidth()/2 + 300 * cos(ofGetElapsedTimef()*2), ofGetHeight()/2 + 100 * sin(ofGetElapsedTimef()*4), 100);
    
    
    for (int packetId = 0; packetId < 2; packetId++){
        for (int i = 0; i < cvData[packetId]->blobs.size(); i++){
            
            ofPolyline line = cvData[packetId]->blobs[i].blob;
            
            int id  = cvData[packetId]->blobs[i].id;
            
            for (auto & pt : line){
                pt = cvData[0]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
            }
            line.flagHasChanged();
     
            ofPoint vel = cvData[packetId]->blobs[i].avgVelSmoothed;;
            float brightness = ofMap(vel.length(), 0, 2, 0, 1, true);
            float angle = atan2(vel.y, vel.x);
//            
//            ofColor a = colorNames[ (int)(id + floor(ofGetElapsedTimef())) % colorNames.size()*0.5].color;
//            ofColor b = colorNames[ (int)(id + ceil(ofGetElapsedTimef())) % colorNames.size()*0.5].color;
//            float pct = ofGetElapsedTimef() - floor(ofGetElapsedTimef());
//            
//            ofColor c( b.r * pct + a.r * (1-pct),
//                       b.g * pct + a.g * (1-pct),
//                       b.b * pct + a.b * (1-pct));
//            c.setBrightness(brightness * 0.5 + 127);
//            //ofSetColor(c);
            
            if (true){
                ofColor cc(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255), ofRandom(0,200));
                cc.setBrightness(brightness*500);
                ofSetColor(cc);
            } else {
                ofSetColor(colorNames[ (int)(id) % (int)(colorNames.size()*0.5)].color);
            }

//            ofColor c;
//            c.setHsb(ofMap(angle, -PI, PI, 0, 255), 255, brightness*0.5 + 127);
//            ofSetColor(c);
            
            ofPath p;
            
            
            //ofNoFill();
            bool bFirst = true;
            for (auto & pt : line){
                if (bFirst) p.moveTo(pt);
                else p.lineTo(pt);

                    bFirst = false;
            }
            p.close();
            
            ofVboMesh m;
            meshes.push_back(m);
            meshes.back() = p.getTessellation();
            meshes.back().draw();
            //ofEndShape();
        }
    }
    
    ofSetColor(0,0,0);
    ofRect(0, RM->getHeight()-10, RM->getWidth(), 20);
    
    
    //line.draw();
    lineFbo.end();
    
    
    
    lineFbo2.begin();
    
    
    shader.begin();
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniformTexture("tex0",lineFbo, 0 );
    shader.setUniformTexture("tex1",simplexImage.getTextureReference(), 1 );
    shader.setUniformTexture("tex2",simplexImage2.getTextureReference(), 2 );
    shader.setUniformTexture("tex3",rockImage.getTextureReference(), 3 );
    
    ofSetColor(255);
    lineFbo.draw(0,0);
    shader.end();
    
    lineFbo2.end();
    lineFbo2.draw(0,0);
    
    lineFbo.begin();
    lineFbo2.draw(0, 0);
    lineFbo.end();
    
    simplexImage.draw(0,0);
    
    
    for (int i = 0; i < meshes.size(); i++){
        ofSetColor(80);
        meshes[i].draw();
    }
}


void paintScene::blobBorn(int packetId, int id){
    
   
}

void paintScene::blobDied(int packetId, int id){
    
}


void paintScene::start(){
    
}

void paintScene::stop(){
    
    
}
