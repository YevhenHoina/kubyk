#pragma once

#include "core/core.h"
#include "core/nodes/nodes.h"
#include "core/gameWindow/gameWindow.h"


#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <include/GLSW/glfw3.h> 
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif



//namespace kubyk_nodes

    
struct ADDVOXEL_node_body{
    bool isOpen;
    std::string title;
    float position[3];
    float rotation[3];
    float scale[3];
    
};


    

//std::vector<kubyk_nodes::node_body> nodes;

int kubykEngineInit(int argc, char** argv);