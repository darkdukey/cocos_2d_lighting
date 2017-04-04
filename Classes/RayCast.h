//
//  RayCast.hpp
//  2d_lighting
//
//  Created by NiTe Luo on 4/1/17.
//
//

#ifndef RayCast_hpp
#define RayCast_hpp

#include <stdio.h>
#include "cocos2d.h"

float getSlope(float x, float y);
float getDegree(const cocos2d::Vec2& v);
std::vector<cocos2d::Vec2> nt_raycast(cocos2d::Vec2 origin, cocos2d::Vec2 direction, std::vector<std::vector<cocos2d::Vec2>> polygons);

#endif /* RayCast_hpp */
