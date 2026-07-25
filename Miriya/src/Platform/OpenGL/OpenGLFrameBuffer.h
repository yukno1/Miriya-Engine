#pragma once

#include "Miriya/Renderer/Framebuffer.h"

namespace Miriya {

class OpenGLFramebuffer : public Framebuffer
{
public:
    OpenGLFramebuffer(const FramebufferSpecification& spec);
    virtual ~OpenGLFramebuffer();

    void Invalidate();

    void Bind() override;
    void Unbind() override;

    void Resize(uint32_t width, uint32_t height) override;

    uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override
    {
        MIR_CORE_ASSERT(index < m_ColorAttachments.size(), "Color attachment index out of range");
        return m_ColorAttachments[index];
    }

    const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

private:
    uint32_t                 m_RendererID = 0;
    FramebufferSpecification m_Specification;

    std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
    FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

    std::vector<uint32_t> m_ColorAttachments;
    uint32_t              m_DepthAttachment = 0;
};

}   // namespace Miriya