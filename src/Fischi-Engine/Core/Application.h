#pragma once

#include <filesystem>

#include "Core.h"

namespace FischiEngine
{
    struct ApplicationConfig
    {
        const char* Name = nullptr;
        const char* Version = nullptr;
        bool Standalone;
    };
    
    class Application
    {
    public:
        explicit Application(const ApplicationConfig& config, int argc, char** argv);
        ~Application();

        void Run();

        static Application* Get();

        const char* GetName() const { return m_Config.Name; }
        const char* GetVersion() const { return m_Config.Version; }

        std::filesystem::path GetEnginePath() const { return m_EnginePath; }
    private:
        std::filesystem::path DetectEngineInstallation();
    private:
        ApplicationConfig m_Config;
        std::filesystem::path m_EnginePath;
    };
    
}
