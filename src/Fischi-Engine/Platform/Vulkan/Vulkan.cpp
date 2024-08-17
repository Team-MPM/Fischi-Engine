#include "vulkan/vulkan.hpp"

#include "Core/Core.h"
#include "Core/Log.h"


void init_vulkan_test()
{
    auto appInfo = vk::ApplicationInfo("Fischi-Engine", 1, "Fischi-Engine", 1, VK_API_VERSION_1_3);
    auto instance = vk::createInstance(vk::InstanceCreateInfo({}, &appInfo));

    FischiEngine::Log::Info("Vulkan initialized! {}", instance.enumeratePhysicalDevices()[0].getFeatures().depthBounds);
}
