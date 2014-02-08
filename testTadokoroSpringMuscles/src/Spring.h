//
//  Spring.h
//  testTamabiTadokoro5
//
//  Created by Nobuhiko Asada on 2014/02/06.
//
//

#ifndef __testTamabiTadokoro5__Spring__
#define __testTamabiTadokoro5__Spring__

#include "ofMain.h"
#include "Particle.h"

class spring{
public:
    spring();
    
    particle* particleA;
    particle* particleB;
    
    float distance;
    float springiness;
    
    void update();
    void draw();
};


#endif /* defined(__testTamabiTadokoro5__Spring__) */
