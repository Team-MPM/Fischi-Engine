#pragma once

#include <filesystem>

#include "Core.h"
#include "Window.h"
#include "Event/EventQueue.h"
#include "Memory/Memory.h"

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
        virtual ~Application();

        void Run();

        static Application* Get();

        const char* GetName() const { return m_Config.Name; }
        const char* GetVersion() const { return m_Config.Version; }

        std::filesystem::path GetEnginePath() const { return m_EnginePath; }
        const ApplicationConfig& GetConfig() const { return m_Config; }
        const EventQueue& GetEventQueue() const { return m_EventQueue; }

        virtual void OnStartup() = 0;
        virtual bool OnEvent(Event* event) = 0;
        virtual void OnUpdate() = 0;
        
    private:
        std::filesystem::path DetectEngineInstallation();
    protected:
        Vector<Shared<Window>> m_Windows;
    private:
        ApplicationConfig m_Config;
        std::filesystem::path m_EnginePath;
        EventQueue m_EventQueue;
    };
    
}
