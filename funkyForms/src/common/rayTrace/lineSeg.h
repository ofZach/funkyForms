#ifndef LINESEG
#define LINESEG

#include <cmath>
#include "Object.h"
#include "ofMain.h"


int get_line_intersection (float p0_x, float p0_y, float p1_x, float p1_y,
                                      float p2_x, float p2_y, float p3_x, float p3_y, float * i_x, float * i_y)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;
    
    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);
    
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        //if (i_x != NULL)
        *i_x = p0_x + (t * s1_x);
        //if (i_y != NULL)
        *i_y = p0_y + (t * s1_y);
        return 1;
    }
    
    return 0; // No collision
}

inline ofPoint getNormalFacing ( ofPoint const incident, ofPoint const norma, ofPoint const normb){        // assume normalized....
    float a = norma.dot(incident);
    float b = normb.dot(incident);
    if (a < b) return norma;
    else return normb;
}

ofPoint getReflect( ofPoint const incident, ofPoint const norma, ofPoint const normb){     // assume normalized....
    ofPoint normal = getNormalFacing(incident, norma, normb);
    return incident - normal * 2.f * normal.dot(incident);
}

ofPoint getRefract( ofPoint const incident, ofPoint const norma, ofPoint const normb, float eta ){
    
    
    ofPoint normal = getNormalFacing(incident, norma, normb);
    ofPoint negInc = -incident;
    float cosi = negInc.dot(normal);
    float cost2 = 1.0f - eta * eta * (1.0f - cosi*cosi);
    ofPoint t = eta*incident + ((eta*cosi - sqrt(fabs(cost2))) * normal);
    t *= cost2 > 0 ? 1 : 0;
    
    
    return t;
    
    //
    //    ofPoint out;
    //    float N_dot_I = normal.dot(incident);
    //    float k = 1.f - eta * eta * (1.f - N_dot_I * N_dot_I);
    //    if (k < 0.f)
    //        out = ofPoint(0.f, 0.f, 0.f);
    //    else
    //        out = eta * incident - (eta * N_dot_I + sqrtf(k)) * normal;
    //    
    //    return out;
}



//! For the purposes of demonstrating the BVH, a simple sphere
struct lineSeg : public Object {
  Vector3 center; // Center of the sphere
  float r, r2; // Radius, Radius^2
    ofPoint a, b;
    
    ofPoint normA, normB;
    
    ofPoint dirRay;

    lineSeg(ofPoint _a, ofPoint _b){
        //const Vector3& center, float radius)
//    : center(a + b), r(radius), r2(radius*radius) {
        
        a = _a;
        b = _b;
        ofPoint mid = (a + b)/2.0;
        center = Vector3(mid.x, mid.y, mid.z);
        r2 = (mid - a).length();
        r2 = (mid - a).lengthSquared();
        
        normA = (b-a).getNormalized().rotate(90, ofPoint(0,0,1));
        normB = (b-a).getNormalized().rotate(-90, ofPoint(0,0,1));
        
        
    }
    
    
    
    
    

    
    
    

  bool getIntersection(const Ray& ray, IntersectionInfo* I) const {
    
      ofPoint rayOrigin(ray.o.x, ray.o.y, ray.o.z);
      ofPoint rayDir(ray.d.x, ray.d.y, ray.d.z);
      
      ofPoint rayB = rayOrigin + rayDir * 2000;
      
      ofPoint intersection;
      
      
      
      
//      if (ofLineSegmentIntersection(rayOrigin, rayB, a, b, intersection)){
      if (get_line_intersection(rayOrigin.x, rayOrigin.y,
                                rayB.x, rayB.y,
                                a.x, a.y,
                                b.x, b.y,
                                &intersection.x, &intersection.y)){
          I->object = this;
          I->t = (rayOrigin - intersection).length();
          I->hit = Vector3(intersection.x, intersection.y, 0);
          I->dir = rayDir;
          
          //cout << "HIT !! "<< endl;
          return true;
      } else{
          return false;
      }
      
    //Vector3 s = center - ray.o;
    //float sd = s * ray.d;
    //float ss = s * s;

    // Compute discriminant
    //float disc = sd*sd - ss + r2;

    // Complex values: No intersection
    //if( disc < 0.f ) return false;

    // Assume we are not in a sphere... The first hit is the lesser valued
    //I->object = this;
    //I->t = sd - sqrt(disc);
    return true;
  }

  Vector3 getNormal(const IntersectionInfo& I) const {
      ofPoint pt = getReflect( I.dir, normA, normB);
      return Vector3(pt.x, pt.y, 0);//normalize(I.hit - center);
  }
    
    Vector3 getNormal(const IntersectionInfo& I, float index) const {
        ofPoint pt = getRefract( I.dir, normA, normB,  index);
        return Vector3(pt.x, pt.y, 0);//normalize(I.hit - center);
    }

  BBox getBBox() const {
      
      float minX = min(a.x, b.x);
      float minY = min(a.y, b.y);
      float maxX = max(a.x, b.x);
      float maxY = max(a.y, b.y);
      

    return BBox(Vector3(minX, minY, -1), Vector3(maxX, maxY, 1));
  }

  Vector3 getCentroid() const {
    return center;
  }

};

#endif
