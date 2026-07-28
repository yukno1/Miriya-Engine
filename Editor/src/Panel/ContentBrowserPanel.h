#pragma once

#include <filesystem>

namespace Miriya {

class ContentBrowserPanel
{
public:
    ContentBrowserPanel();

    void OnImGuiRender();

private:
    std::filesystem::path m_CurrentDirectory;
};

}   // namespace Miriya