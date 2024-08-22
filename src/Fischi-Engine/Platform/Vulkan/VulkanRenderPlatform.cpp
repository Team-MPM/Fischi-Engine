#include "VulkanRenderPlatform.h"

#include "Core/Application.h"
#include "Core/Log.h"

#ifdef FISCHI_PLATFORM_WINDOWS
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif

namespace FischiEngine
{
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        const auto messageTemplate = "[VkValidationLayer] {0}";
        switch (messageSeverity)
        {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            Log::Trace(messageTemplate, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            Log::Info(messageTemplate, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            Log::Warn(messageTemplate, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
            Log::Error(messageTemplate, pCallbackData->pMessage);
            break;
        }
        return VK_FALSE;
    }

    void VulkanRenderPlatform::Init()
    {
        Log::Info("Initializing Vulkan...");

        const auto config = Application::Get()->GetConfig();

        vk::ApplicationInfo applicationInfo = {};
        applicationInfo.pApplicationName = config.Name;
        applicationInfo.pEngineName = "Fischi Engine";
        applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
        applicationInfo.apiVersion = VK_API_VERSION_1_3;

        const auto availableExtensions = vk::enumerateInstanceExtensionProperties();

        Log::Trace("Available Vulkan extensions:");
        for (const auto& extension : availableExtensions)
            Log::Trace("\t{0}", static_cast<const char*>(extension.extensionName));

        const auto availableLayers = vk::enumerateInstanceLayerProperties();

        Log::Trace("Available Vulkan layers:");
        for (const auto& layer : availableLayers)
            Log::Trace("\t{0}", static_cast<const char*>(layer.layerName));

        const std::initializer_list extensions = {
            VK_KHR_SURFACE_EXTENSION_NAME,
#ifndef FISCHI_DIST
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
#ifdef FISCHI_PLATFORM_WINDOWS
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
        };

        const std::initializer_list layers = {
#ifndef FISCHI_DIST
            "VK_LAYER_KHRONOS_validation"
#endif
        };

        Log::Trace("Enabled Vulkan extensions:");
        for (const auto& extension : extensions)
            Log::Trace("\t{0}", extension);

        Log::Trace("Enabled Vulkan layers:");
        for (const auto& layer : layers)
            Log::Trace("\t{0}", layer);

        vk::InstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.pApplicationInfo = &applicationInfo;
        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        instanceCreateInfo.ppEnabledExtensionNames = extensions.begin();
        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        instanceCreateInfo.ppEnabledLayerNames = layers.begin();

        m_Instance = vk::createInstance(instanceCreateInfo);
        Log::Info("Vulkan instance created");

        m_DispatchLoaderDynamic = vk::DispatchLoaderDynamic(m_Instance, vkGetInstanceProcAddr);

#ifndef FISCHI_DIST
        vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
        debugCreateInfo.messageSeverity =
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose;
        debugCreateInfo.messageType =
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
            vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
            vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
        debugCreateInfo.pfnUserCallback = debugCallback;
        debugCreateInfo.pUserData = nullptr;

        m_DebugMessenger = m_Instance.createDebugUtilsMessengerEXT(debugCreateInfo, nullptr, m_DispatchLoaderDynamic);
#endif
    }

    void VulkanRenderPlatform::Shutdown()
    {
        Log::Info("Shutting down Vulkan...");

#ifndef FISCHI_DIST
        m_Instance.destroyDebugUtilsMessengerEXT(m_DebugMessenger, nullptr, m_DispatchLoaderDynamic);
#endif
        m_Instance.destroy();
        Log::Info("Vulkan instance destroyed");
    }

    RenderPlatform::Type VulkanRenderPlatform::GetRenderPlatform()
    {
        return Type::Vulkan;
    }

    bool VulkanRenderPlatform::IsOpReady()
    {
        return m_OpReady;
    }
}
