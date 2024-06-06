#pragma once
#include "node.h"

class addVoxel :
    public node
{

public:
    float position[3] = { 0.0f, 0.0f, 0.0f };
    float rotation[3] = { 0.0f, 0.0f, 0.0f };
    float scale[3] = { 1.0f, 1.0f, 1.0f };

    bool leftConnection = false, righrConnection = false;

    addVoxel(float x = 350.0f, float y = 500.0f) : node(x, y) {};
    

    virtual void nodeAction() override {

    };

    
};

