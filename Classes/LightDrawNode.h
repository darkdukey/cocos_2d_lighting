//
//  LightDrawNode.hpp
//  2d_lighting
//
//  Created by NiTe Luo on 4/2/17.
//
//

#ifndef LightDrawNode_hpp
#define LightDrawNode_hpp

#include <stdio.h>
#include "cocos2d.h"

class LightDrawNode: public cocos2d::DrawNode {
    //
    
public:
    static LightDrawNode* create();
    
    virtual bool init() override;
    void setShader(const std::string& vertShaderPath, const std::string& fragShaderPath);
    void setLightPosition(float x, float y);
};

#endif /* LightDrawNode_hpp */
