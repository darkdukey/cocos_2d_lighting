//
//  LightingScene.cpp
//  2d_lighting
//
//  Created by NiTe Luo on 4/1/17.
//
//

#include "LightingScene.h"
#include "RayCast.h"
#include <algorithm>

USING_NS_CC;
using namespace std;

static bool compareEdge(Edge a, Edge b)
{
    float d_a = getDegree(a.dir);
    float d_b = getDegree(b.dir);
    return  d_a < d_b;
}

Scene* LightingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LightingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LightingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _center = Vec2(visibleSize.width/2, visibleSize.height/2);
    _dir = Vec2(1,0);
    _angle = 0;
    
    _drawNode = DrawNode::create();
    addChild(_drawNode);
    
    _lightNode = LightDrawNode::create();
    _lightNode->setLightPosition(_center.x, _center.y);
    addChild(_lightNode);
    
    vector<Vec2> poli1 = {{40,150},{90,180},{120,140}};
    _polies.push_back(poli1);
    
    vector<Vec2> poli2 = {{130,250},{180,280},{210,240},{170,220}};
    _polies.push_back(poli2);
    
    vector<Vec2> poli3 = {{300,170},{350,200},{380,160}};
    _polies.push_back(poli3);
    
    vector<Vec2> poli4 = {{180,90},{230,120},{260,80},{220,50}};
    _polies.push_back(poli4);
    
    for (auto it = _polies.begin(); it != _polies.end(); ++it) {
        vector<Vec2> p = *it;
        _drawNode->drawSolidPoly(&p[0], (unsigned int)p.size(), Color4F::GREEN);
    }
    
    _world = _polies;
    vector<Vec2> screen = {{origin.x,origin.y},
        {origin.x,visibleSize.height + origin.y},
        {visibleSize.width + origin.x, visibleSize.height + origin.y },
        {visibleSize.width + origin.x, origin.y}};
    
    _world.push_back(screen);
    
    //Construct ray from center of screen to each vertex
    for (auto it = _polies.begin(); it != _polies.end(); ++it) {
        vector<Vec2> p = *it;
        for (auto it2 = p.begin(); it2 != p.end(); ++it2) {
            Vec2 direction = *it2 - _center;
            calcEdge(direction);
        }
    }
    
    calcEdge(origin - _center);
    calcEdge(Vec2(origin.x, visibleSize.height + origin.y) - _center);
    calcEdge(Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y) - _center);
    calcEdge(Vec2(visibleSize.width + origin.x, origin.y) - _center);
    
    sort(_edges.begin(), _edges.end(), compareEdge);

    if (_edges.size() > 0 && _edges[0].edge == EDGE_RIGHT) {
        _edges.push_back(_edges[0]);
        _edges.erase(_edges.begin());
    }
    
    vector<vector<Vec2>> light_poly;
    for (int i = 0; i < _edges.size(); i+=2) {
        vector<Vec2> mesh;
        mesh.push_back(_center);
        mesh.push_back(_edges[i].pos);
        mesh.push_back(_edges[i+1].pos);
        
        light_poly.push_back(mesh);
    }
    
    for (auto it = light_poly.begin(); it != light_poly.end(); ++it) {
        vector<Vec2> p = *it;
        _lightNode->drawSolidPoly(&p[0], (unsigned int)p.size(), Color4F::RED);
    }
    
    return true;
}

void LightingScene::calcEdge(Vec2 direction)
{
    Vec2 dir_1 = direction.rotateByAngle(Vec2::ZERO, FLT_EPSILON);
    Vec2 dir_2 = direction.rotateByAngle(Vec2::ZERO, -FLT_EPSILON);
    
    vector<Vec2> cast_1 = nt_raycast(_center, dir_1, _world);
    vector<Vec2> cast_2 = nt_raycast(_center, dir_2, _world);
    
    //left edge
    _drawNode->drawLine(_center, cast_1[0], Color4F::RED);
    _edges.push_back({dir_1, cast_1[0], EDGE_LEFT});
    
    //right edge
    _drawNode->drawLine(_center, cast_2[0], Color4F::RED);
    _edges.push_back({dir_2, cast_2[0], EDGE_RIGHT});
}
