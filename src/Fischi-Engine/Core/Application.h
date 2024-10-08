﻿#pragma once

#include <filesystem>

#include "Core.h"
#include "Log.h"
#include "Window.h"
#include "Event/EventQueue.h"
#include "Memory/Memory.h"
#include "Platform/RenderPlatform.h"

namespace FischiEngine
{
    struct FISCHI_API ApplicationConfig
    {
        const char* Name = nullptr;
        const char* Version = nullptr;
        bool Standalone;
        RenderPlatform::Type RenderPlatform;
        Log::Level LogLevel;
    };
    
    class FISCHI_API Application
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
        EventQueue& GetEventQueue() { return m_EventQueue; }

        virtual void OnStartup() = 0;
        virtual bool OnEvent(Event* event) = 0;
        virtual void OnUpdate() = 0;
        virtual void OnShutdown() = 0;
        
    private:
        std::filesystem::path DetectEngineInstallation();
    protected:
        Vector<Shared<Window>> m_Windows;
        Shared<Window> m_MainWindow;
    private:
        ApplicationConfig m_Config;
        std::filesystem::path m_EnginePath;
        EventQueue m_EventQueue;
    };
    
}
