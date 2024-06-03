#pragma once
#include "core/core.h"


namespace kubyk_render
{
    class OpenGL_VertexIndexBuffer : public VertexIndexBuffer
    {
    public:
        OpenGL_VertexIndexBuffer() : VertexIndexBuffer()
        {}

        void create_buffers(const std::vector<nelems::VertexHolder>& vertices, const std::vector<unsigned int>& indices) override;

        void delete_buffers();
    };
}