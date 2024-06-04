#pragma once
#include "core/core.h"

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    void setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setVec3(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
    }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }
    

private:
    GLuint programID;
    GLuint compileShader(GLenum type, const std::string& source);
    GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);
};
