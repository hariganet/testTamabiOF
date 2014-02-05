//
//  Particle.h
//  testTamabiTadokoro4
//
//  Created by Nobuhiko Asada on 2014/02/05.
//
//

#ifndef __testTamabiTadokoro4__Particle__
#define __testTamabiTadokoro4__Particle__

#include "ofMain.h"

class Particle{
public:
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;
    float damping;

    Particle();
    virtual ~Particle(){};
    void resetForce();
    void addForce(float x, float y);
    void addDampingForce();
    void setInitialCondition(float px, float py, float vx, float vy);
    void update();
    void draw();
    
    void bounceOffWalls();
};

#endif /* defined(__testTamabiTadokoro4__Particle__) */
