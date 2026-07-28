#pragma once

#include <filesystem>

#include "Miriya/Renderer/Texture.h"

namespace Miriya {

class ContentBrowserPanel
{
public:
    ContentBrowserPanel();

    void OnImGuiRender();

private:
    std::filesystem::path m_CurrentDirectory;

    Ref<Texture2D> m_DirectoryIcon;
    Ref<Texture2D> m_FileIcon;
};

}   // namespace Miriya