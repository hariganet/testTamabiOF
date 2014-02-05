//
//  Enemies.cpp
//  testTamabiTadokoro4
//
//  Created by Nobuhiko Asada on 2014/02/06.
//
//

#include "Enemies.h"

Enemies::Enemies(){
    for(int i=0; i<ENEMY_NUM; ++i){
        Enemy e;
        e.setInitialCondition(ofRandom(300, ofGetWidth()-300), ofRandom(0, 200));
        enemies.push_back(e);
    }
}

Enemies::~Enemies(){
    
}

void Enemies::update(){
    vector<Enemy>::iterator enemiesItr = enemies.begin();
    while(enemiesItr != enemies.end()){
        (*enemiesItr).update();
        ++enemiesItr;
    }
}

void Enemies::checkHit(float _x, float _y){
    vector<Enemy>::iterator enemiesItr = enemies.begin();
    while(enemiesItr != enemies.end()){
        (*enemiesItr).checkHit(_x, _y);
        if((*enemiesItr).pos.x * (*enemiesItr).pos.y < 1000){
            enemiesItr = enemies.erase(enemiesItr);
        }else{
            ++enemiesItr;
        }
    }
}

void Enemies::draw(){
    vector<Enemy>::iterator enemiesItr = enemies.begin();
    while(enemiesItr != enemies.end()){
        (*enemiesItr).draw();
        ++enemiesItr;
    }
    
}