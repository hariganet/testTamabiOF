//
//  Enemies.h
//  testTamabiTadokoro4
//
//  Created by Nobuhiko Asada on 2014/02/06.
//
//

#ifndef __testTamabiTadokoro4__Enemies__
#define __testTamabiTadokoro4__Enemies__

#include <vector>
#include "Enemy.h"

class Enemies{
public:
    const int ENEMY_NUM = 10;
    std::vector<Enemy> enemies;
    
    Enemies();
    ~Enemies();
    
    void update();
    void checkHit(float _x, float _y);
    void draw();
    
};

#endif /* defined(__testTamabiTadokoro4__Enemies__) */
