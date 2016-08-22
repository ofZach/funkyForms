#include "spring3f.h"

//---------------------------------------------------------------------
spring3f::spring3f(){
	particleA = NULL;
	particleB = NULL;
}

//---------------------------------------------------------------------
void spring3f::update(){
	if ((particleA == NULL) || (particleB == NULL)){
		return;
	}
	
	ofPoint pta = particleA->pos;
	ofPoint ptb = particleB->pos;
	
	float theirDistance = (pta - ptb).length();
	float springForce = (springiness * (distance - theirDistance));
	ofPoint frcToAdd = (pta-ptb).normalized() * springForce;
	
	particleA->addForce(frcToAdd.x, frcToAdd.y, frcToAdd.z);
	particleB->addForce(-frcToAdd.x, -frcToAdd.y, -frcToAdd.z);
}


//---------------------------------------------------------------------
void spring3f::draw(){
	
	if ((particleA == NULL) || (particleB == NULL)){
		return;
	}
	
	ofLine(particleA->pos.x, particleA->pos.y, particleA->pos.z, particleB->pos.x, particleB->pos.y, particleB->pos.z);
}