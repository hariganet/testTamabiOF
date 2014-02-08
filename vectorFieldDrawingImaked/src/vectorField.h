//
//  vectorField.h
//  VectorField
//
//  Created by Nobuhiko Asada on 2014/02/06.
//
//

#ifndef __VectorField__vectorField__
#define __VectorField__vectorField__

#include "ofMain.h"

class vectorField{
public:
    //ベクトル場のグリッドの数を指定
    int fieldWidth;
    int fieldHeight;
    //ベクトルの数
    int fieldSize;
    //ベクトル場が描画される画面の大きさ
    int externalWidth;
    int externalHeight;
    //ベクトルの配列
    vector<ofVec2f> field;
    
    vectorField();
    virtual ~vectorField();
    //ベクトル場の初期化
    void setupField(int innerW, int innerH, int outerW, int outerH);
    //消去
    void clear();
    //徐々にベクトル場に関わる力が弱まるようにする
    void fadeField(float fadeAmount);
    //すべてのベクトルをランダムに生成
    void randomizeField(float scale);
    //ベクトル場の様子を描画
    void draw();
    //座標を指定して、その地点でのベクトル場から受ける力を算出
    ofVec2f getForceFromPos(float xpos, float ypos);
    //外向きの力を加える（噴出）
    void addOutwardCircle(float x, float y, float radius, float strength);
    //内向きの力を加える（吸引）
    void addInwardCircle(float x, float y, float radius, float strength);
    //時計回りの渦巻き
    void addClockwiseCircle(float x, float y, float radius, float strength);
    //反時計回りの渦巻き
    void addCounterClockwiseCircle(float x, float y, float radius, float strength);
    //円形の力を加える
    void addVectorCircle(float x, float y, float vx, float vy, float radius, float strength);
};

#endif /* defined(__VectorField__vectorField__) */
