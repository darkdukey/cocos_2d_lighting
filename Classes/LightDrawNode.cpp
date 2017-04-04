//
//  LightDrawNode.cpp
//  2d_lighting
//
//  Created by NiTe Luo on 4/2/17.
//
//

#include "LightDrawNode.h"

using namespace std;
using namespace cocos2d;

LightDrawNode* LightDrawNode::create()
{
    LightDrawNode* ret = new (std::nothrow) LightDrawNode();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool LightDrawNode::init()
{
    if (!DrawNode::init()) {
        return false;
    }
    
    setShader("shader/shader_2d_light.vert", "shader/shader_2d_light.frag");
    
    return true;
}

void LightDrawNode::setShader(const std::string& vertShaderPath, const std::string& fragShaderPath)
{    
    setGLProgramState(GLProgramState::getOrCreateWithShaders(vertShaderPath, fragShaderPath, ""));
}

void LightDrawNode::setLightPosition(float x, float y)
{
    Size winSize = Director::getInstance()->getWinSizeInPixels();
    getGLProgramState()->setUniformVec4("u_light_pos", Vec4(x, y, 0.0, 1.0));
    getGLProgramState()->setUniformVec2("window", Vec2(winSize.width, winSize.height));
}
