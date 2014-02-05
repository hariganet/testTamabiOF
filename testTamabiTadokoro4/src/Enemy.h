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

    Enemy();
    ~Enemy();
    
    void update();
    void draw();
    
    void setInitialCondition(float x, float y);
    
};

#endif /* defined(__testTamabiTadokoro4__Enemy__) */
