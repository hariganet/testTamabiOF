//
//  Enemy.h
//  testTamabiTadokoro4
//
//  Created by Nobuhiko Asada on 2014/02/05.
//
//

#ifndef __testTamabiTadokoro4__Enemy__
#define __testTamabiTadokoro4__Enemy__

#include "ofMain.h"

class Enemy{
public:
    ofVec2f pos;
    ofVec2f posInit;
    
    float vel;
    
    bool isHit;
    
    float w, h, wInit, hInit;
    
    Enemy();
    ~Enemy();
    
    void update();
    void draw();
    
    void setInitialCondition(float x, float y);
    
    void erasing();
    void checkHit(float x, float y);
    
    void resetInitialCondition();
    
    
};

#endif /* defined(__testTamabiTadokoro4__Enemy__) */
