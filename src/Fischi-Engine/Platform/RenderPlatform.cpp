#include "RenderPlatform.h"

#include <ranges>
#include <unordered_map>

#include "Vulkan/VulkanRenderPlatform.h"

namespace FischiEngine
{
    static std::unordered_map<RenderPlatform::Type, RenderPlatform*> s_RenderPlatforms;

    RenderPlatform* RenderPlatform::Get(const Type type)
    {
        if (s_RenderPlatforms.contains(type))
        {
            if (const auto renderPlatform = s_RenderPlatforms.at(type);
                renderPlatform->IsOpReady() && renderPlatform->GetRenderPlatform() == type)
                return renderPlatform;
            return nullptr;
        }

        switch (type)
        {
        case Type::Vulkan:
            {
                const auto renderPlatform = new VulkanRenderPlatform();
                s_RenderPlatforms[type] = renderPlatform;
                return renderPlatform;
            }
        case Type::OpenGL:
        case Type::DX11:
        case Type::DX12:
        case Type::None:
        default:
            return nullptr;
        }
    }

    void RenderPlatform::OnShutdown()
    {
        for (const auto renderPlatform : s_RenderPlatforms | std::views::values)
            renderPlatform->Shutdown();
    }
}
