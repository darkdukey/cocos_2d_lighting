//
//  LightingScene.hpp
//  2d_lighting
//
//  Created by NiTe Luo on 4/1/17.
//
//

#ifndef LightingScene_hpp
#define LightingScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "LightDrawNode.h"

enum EdgeType {
    EDGE_LEFT,
    EDGE_RIGHT
};

struct Edge {
    cocos2d::Vec2 dir;
    cocos2d::Vec2 pos;
    EdgeType edge;
};

class LightingScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    virtual void update(float dt) override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(LightingScene);
    
    void calcEdge(cocos2d::Vec2 direction);
    
private:
    cocos2d::DrawNode* _drawNode;
    LightDrawNode* _lightNode;
    std::vector<std::vector<cocos2d::Vec2>> _polies;
    std::vector<std::vector<cocos2d::Vec2>> _world;
    cocos2d::Vec2 _dir;
    cocos2d::Vec2 _center;
    cocos2d::Vec2 _light_pos;
    std::vector<Edge> _edges;
    float _angle;
};

#endif /* LightingScene_hpp */
