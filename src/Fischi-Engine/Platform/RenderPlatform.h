#pragma once

#include "Core/Core.h"

namespace FischiEngine
{
    class FISCHI_API RenderPlatform
    {
    public:
        virtual ~RenderPlatform() = default;

        enum class Type
        {
            None = 0,
            OpenGL,
            Vulkan,
            DX11,
            DX12
        };

        static RenderPlatform* Get(Type type);
        static void OnShutdown();
        
        virtual void Init() = 0;
        virtual void Shutdown() = 0;

        virtual Type GetRenderPlatform() = 0;
        virtual bool IsOpReady() = 0;
    };
}
