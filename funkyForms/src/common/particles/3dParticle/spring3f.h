#pragma once

#include "ofMain.h"

#include "particle3f.h"

class spring3f {

	public:

		spring3f();
		
		particle3f * particleA;
		particle3f * particleB;
		
		float distance;
		float springiness;	 // this is the k, springiness constant
	
		void update();
		void draw();
	
	
};
