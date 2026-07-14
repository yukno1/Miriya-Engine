#include "mirpch.h"
#include "OpenGLBuffer.h"

#include <glad/gl.h>

namespace Miriya {

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Vertex Buffer ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
    MIR_PROFILE_FUNCTION();

    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    // static draw means we don't need to update the buffer
    // not streaming
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    MIR_PROFILE_FUNCTION();

    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLVertexBuffer::Bind() const
{
    MIR_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBuffer::Unbind() const
{
    MIR_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Index Buffer /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    : m_Count(count)
{
    MIR_PROFILE_FUNCTION();

    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    MIR_PROFILE_FUNCTION();

    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLIndexBuffer::Bind() const
{
    MIR_PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBuffer::Unbind() const
{
    MIR_PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}   // namespace Miriya
