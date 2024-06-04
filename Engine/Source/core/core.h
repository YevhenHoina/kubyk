#pragma once

//std includes

#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>


#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLSW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <string>

//OpenGL inludes




namespace container
{
    

}

struct COLOR {
    GLclampf R;
    GLclampf G;
    GLclampf B;
    GLclampf A;
};

struct kb_Vector
{
    float X;
    float Y;
    float Z;
};

#include "core/gameWindow/Shader.h"
const glm::vec3 vec3ZERO = glm::vec3(0.0f, 0.0f, 0.0f);



