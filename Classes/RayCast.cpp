//
//  RayCast.cpp
//  2d_lighting
//
//  Created by NiTe Luo on 4/1/17.
//
//

#include "RayCast.h"
#include <algorithm>

using namespace std;
using namespace cocos2d;

float getSlope(float x, float y)
{
    if(x == 0) {
        return FLT_MAX;
    } else {
        return y/x;
    }
}

float getDegree(const Vec2& v)
{
    float deg = CC_RADIANS_TO_DEGREES(v.getAngle());
    if(deg < 0) {
        deg = deg + 360;
    }
    return deg;
}

//r_px+r_dx*T1 = s_px+s_dx*T2
//r_py+r_dy*T1 = s_py+s_dy*T2
vector<Vec2> nt_raycast(Vec2 origin, Vec2 direction, vector<vector<Vec2>> polygons)
{
    float slope_ray = getSlope(direction.x, direction.y);
    float slope_line = 0;
    vector<Vec2> points;
    vector<Vec2> ret;
    Vec2 intersect;
    float min_dis = FLT_MAX;
    int min_dis_index = -1;
    Vec2 p_start;
    Vec2 p_end;
    
    for (auto it = polygons.begin(); it != polygons.end(); ++it) {
        vector<Vec2> p = *it;
        for (int i = 0; i < p.size(); ++i) {
            
            if (i < p.size() - 1) {
                p_start = p[i];
                p_end = p[i+1];
            } else {
                p_start = p[i];
                p_end = p[0];
            }
            
            if ( abs(direction.x) < FLT_EPSILON) {
                direction.x = FLT_EPSILON;
            }
            
            
            slope_line = getSlope(p_end.x - p_start.x, p_end.y - p_start.y);
            
            float s_dx = p_end.x - p_start.x;
            float s_dy = p_end.y - p_start.y;
            float t1 = 0;
            float t2 = 0;
            
            if (abs(slope_ray - slope_line) < FLT_EPSILON) {
                //Parallel
                continue;
            } else {
                // When dx is not 0
                if(abs(direction.x) > 0.00001) {
                    t2 = (direction.x * (p_start.y - origin.y) + direction.y * (origin.x - p_start.x))/(s_dx * direction.y - s_dy * direction.x);
                    t1 = (p_start.x + s_dx * t2 - origin.x)/direction.x;
                } else {
                    t2 = direction.y * (origin.x - p_start.x)/(s_dx * direction.y);
                    t1 = (p_start.y + s_dy * t2 - origin.y)/direction.y;
                }
                
                
                if(t1 > 0 && t2 >= 0 && t2 <= 1) {
                    intersect.x = origin.x + direction.x * t1;
                    intersect.y = origin.y + direction.y * t1;
                    points.push_back(intersect);
                }
            }
        }
    }
    
    for (auto i = 0; i < points.size(); ++i) {
        float dis = origin.distance(points[i]);
        if(dis < min_dis) {
            min_dis = dis;
            min_dis_index = i;
        }
    }
    
    
    if (min_dis_index >= 0) {
        ret.push_back(points[min_dis_index]);
        
        for (auto i = 0; i < points.size(); ++i) {
            if (i != min_dis_index) {
                //TODO: Sort the return value based on distance
                ret.push_back(points[i]);
            }
        }
    }
    
    return ret;
}
