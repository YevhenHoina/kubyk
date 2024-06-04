#pragma once




namespace kubyk_voxel
{
    
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

    std::vector<voxel*> VOXELS;

    void addVoxel(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f))
    {
        kubyk_voxel::voxel* buffer_voxel = new kubyk_voxel::voxel("testCube", pos, rot, scl);
        kubyk_voxel::VOXELS.push_back(buffer_voxel);
    }
    void addVoxelPYTHON(float pos[3], float rot[3], float scl[3])
    {
        glm::vec3 cpp_pos = glm::vec3(pos[0], pos[1], pos[2]);
        glm::vec3 cpp_rot = glm::vec3(rot[0], rot[1], rot[2]);
        glm::vec3 cpp_scl = glm::vec3(scl[0], scl[1], scl[2]);

        addVoxel(cpp_pos, cpp_rot, cpp_scl);
    }
}