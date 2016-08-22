#include "particle3f.h"
#include "ofMain.h"

//------------------------------------------------------------
particle3f::particle3f(){
	setInitialCondition(0,0,0,0, 0, 0);
	damping = 0.25f;
	bFixed = false;
}

//------------------------------------------------------------
void particle3f::resetForce(){
    // we reset the forces every frame
    frc.set(0,0, 0);
}

//------------------------------------------------------------
void particle3f::addForce(float x, float y, float z){
    // add in a fofPointorce in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
    frc.z = frc.z + z;
}

//------------------------------------------------------------
void particle3f::addRepulsionForce(float x, float y, float z, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofPoint posOfForce;
	posOfForce.set(x,y, z);
	
	// ----------- (2) calculate the difference & length 
	
	ofPoint diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
        frc.z = frc.z + diff.z * scale * pct;
    }
}

//------------------------------------------------------------
void particle3f::addAttractionForce(float x, float y, float z, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofPoint posOfForce;
	posOfForce.set(x,y,z );
	
	// ----------- (2) calculate the difference & length 
	
	ofPoint diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
        frc.z = frc.z - diff.z * scale * pct;
    }
}

//------------------------------------------------------------
void particle3f::addRepulsionForce(particle3f &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle3f p is: 
	ofPoint posOfForce;
	posOfForce.set(p.pos.x,p.pos.y, p.pos.z);
	
	// ----------- (2) calculate the difference & length 
	
	ofPoint diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
        frc.z = frc.z + diff.z * scale * pct;
        
		p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
        p.frc.z = p.frc.z - diff.z * scale * pct;
    }
}

//------------------------------------------------------------
void particle3f::addAttractionForce(particle3f & p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle3f p is: 
	ofPoint posOfForce;
	posOfForce.set(p.pos.x,p.pos.y, p.pos.z);
	
	// ----------- (2) calculate the difference & length 
	
	ofPoint diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
        frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
        frc.z = frc.z + diff.z * scale * pct;
        
        p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
        p.frc.z = p.frc.z - diff.z * scale * pct;
    }
	
}

//------------------------------------------------------------
void particle3f::addClockwiseForce(particle3f &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle3f p is: 
	ofPoint posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofPoint diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.y * scale * pct;
        frc.y = frc.y + diff.x * scale * pct;
		p.frc.x = p.frc.x + diff.y * scale * pct;
        p.frc.y = p.frc.y - diff.x * scale * pct;
    }
}

//------------------------------------------------------------
void particle3f::addCounterClockwiseForce(particle3f &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle3f p is: 
	ofPoint posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofPoint diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.y * scale * pct;
        frc.y = frc.y - diff.x * scale * pct;
		p.frc.x = p.frc.x - diff.y * scale * pct;
        p.frc.y = p.frc.y + diff.x * scale * pct;
		
    }
}


//------------------------------------------------------------
void particle3f::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
    frc.z = frc.z - vel.z * damping;
}

//------------------------------------------------------------
void particle3f::setInitialCondition(float px, float py, float pz, float vx, float vy, float vz){
    pos.set(px,py, pz);
	vel.set(vx,vy, vz);
}

//------------------------------------------------------------
void particle3f::update(){	
	if (bFixed == false){
		vel = vel + frc;
		pos = pos + vel;
	}
}

//------------------------------------------------------------
void particle3f::draw(){
    ofCircle(pos.x, pos.y, pos.z,  3);
}


//------------------------------------------------------------
void particle3f::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x > maxx){
		pos.x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (pos.y > maxy){
		pos.y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}
