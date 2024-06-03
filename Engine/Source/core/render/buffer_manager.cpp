#include "buffer_manager.h"

namespace kubyk_render
{
    void OpenGL_VertexIndexBuffer::create_buffers(const std::vector<nelems::VertexHolder>& vertices, const std::vector<unsigned int>& indices)
    {
        glGenVertexArrays(1, &mVAO);

        glGenBuffers(1, &mIBO);
        glGenBuffers(1, &mVBO);

        glBindVertexArray(mVAO);

        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(nelems::VertexHolder), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nelems::VertexHolder), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(nelems::VertexHolder), (void*)offsetof(nelems::VertexHolder, mNormal));

        glBindVertexArray(0);

    }

    void OpenGL_VertexIndexBuffer::delete_buffers()
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &mIBO);
        glDeleteBuffers(1, &mVBO);
        glDeleteVertexArrays(1, &mVAO);
    }
}