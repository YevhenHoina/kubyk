#pragma once

#include "core/core.h"

class voxel
	{
    public:
        std::string ID = "trashVoxel";
		glm::mat4 model;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

    public:
        //position, roatation, scale
        
        voxel(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f))
            : position(pos), rotation(rot), scale(scl) {
            updateModelMatrix();
        }

        voxel(std::string id, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f))
            : ID(id), position(pos), rotation(rot), scale(scl) {
            updateModelMatrix();
        }

        // Method to update the model matrix
        void updateModelMatrix() {

            model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, scale);
        }
        
	};




 

   
