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

int kubykEngineInit(int argc, char** argv, bool is_game);


class saveFile
{
public:
    std::vector<addVoxel*> saved_addVoxel_nodes;
    char* saveName;

    saveFile(std::vector<addVoxel*> n, char* s) : saved_addVoxel_nodes(n), saveName(s) {}

    void save(const std::string& filename) {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        size_t nameLength = strlen(saveName);
        outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        outFile.write(saveName, nameLength);

        size_t vectorSize = saved_addVoxel_nodes.size();
        outFile.write(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));
        for (const auto& voxel : saved_addVoxel_nodes) {
            outFile.write(reinterpret_cast<const char*>(voxel->nodePos), sizeof(voxel->nodePos));
            outFile.write(reinterpret_cast<const char*>(voxel->position), sizeof(voxel->position));
            outFile.write(reinterpret_cast<const char*>(voxel->rotation), sizeof(voxel->rotation));
            outFile.write(reinterpret_cast<const char*>(voxel->scale), sizeof(voxel->scale));
        }
    }

    void load(const std::string& filename) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
            return;
        }

        size_t nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        saveName = new char[nameLength + 1];
        inFile.read(saveName, nameLength);
        saveName[nameLength] = '\0';

        size_t vectorSize;
        inFile.read(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));
        saved_addVoxel_nodes.resize(vectorSize);

        for (auto& voxel : saved_addVoxel_nodes) {
            voxel = new addVoxel();
            inFile.read(reinterpret_cast<char*>(voxel->nodePos), sizeof(voxel->nodePos));
            inFile.read(reinterpret_cast<char*>(voxel->position), sizeof(voxel->position));
            inFile.read(reinterpret_cast<char*>(voxel->rotation), sizeof(voxel->rotation));
            inFile.read(reinterpret_cast<char*>(voxel->scale), sizeof(voxel->scale));
        }
    }
};