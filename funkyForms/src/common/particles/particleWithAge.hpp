//
//  particleWithAge.hpp
//  funkyForms
//
//  Created by Gordey on 8/21/16.
//
//

#ifndef particleWithAge_hpp
#define particleWithAge_hpp

#include "particle.h"

class particleWithAge : public particle{
    
public:
    int id;
    int radius;
    float age;
    float ageMax;
    
} ;

#endif /* particleWithAge_hpp */
