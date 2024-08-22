#pragma once
#include "Platform/RenderPlatform.h"

#include <vulkan/vulkan.hpp>

namespace FischiEngine
{
    class VulkanRenderPlatform : public RenderPlatform
    {
    public:
        void Init() override;
        void Shutdown() override;
        Type GetRenderPlatform() override;
        bool IsOpReady() override;

    private:
        bool m_OpReady = false;
        vk::Instance m_Instance = {};
        vk::DispatchLoaderDynamic m_DispatchLoaderDynamic = {};
        vk::DebugUtilsMessengerEXT m_DebugMessenger = {};
    };
    
}
