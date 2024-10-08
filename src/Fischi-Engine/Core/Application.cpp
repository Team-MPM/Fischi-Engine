﻿#include "Application.h"

#include <filesystem>
#include <iostream>

#include "Core/Core.h"
#include "Core/Log.h"
#include "Event/EventDefs.h"
#include "Memory/Memory.h"
#include "Platform/Platform.h"
#include "Time/Timer.h"

namespace FischiEngine
{
    static Application* s_ApplicationInstance = nullptr;

    std::filesystem::path Application::DetectEngineInstallation()
    {
        std::filesystem::path enginePath;

        if (std::filesystem::exists("bin"))
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator("bin"))
            {
                if (entry.is_regular_file() && (entry.path().filename() == "Fischi-Engine.dll" || entry.path().
                    filename()
                    == "libFischi-Engine.so"))
                {
                    enginePath = std::filesystem::absolute(".");
                    return enginePath;
                }
            }
        }

        if (std::filesystem::exists("../../bin"))
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator("../../bin"))
            {
                if (entry.is_regular_file() && (entry.path().filename() == "Fischi-Engine.dll" || entry.path().
                    filename()
                    == "libFischi-Engine.so"))
                {
                    enginePath = std::filesystem::absolute("../../");
                    return enginePath;
                }
            }
        }

        if (const char* envVarPath = std::getenv("FISCHI_ENGINE_PATH"); envVarPath != nullptr)
        {
            enginePath = std::filesystem::absolute(envVarPath);
            return enginePath;
        }

        std::cerr << "Engine installation not found! Exiting...\n";
        FISCHI_ABORT();

        return enginePath;
    }

    Application::Application(const ApplicationConfig& config, int argc, char** argv)
        : m_Config(config), m_Windows(Vector<Shared<Window>>())
    {
        s_ApplicationInstance = this;
        std::cout << "Starting Fischi Engine!\n";

        std::cout << "Detecting Engine Path...\n";

#ifdef FISCHI_DIST
        m_Config.Standalone = true;
#endif

        if (m_Config.Standalone)
        {
            m_EnginePath = std::filesystem::absolute(argv[0]).parent_path();
            Log::Trace("Loading Standalone Engine at: {0}", m_EnginePath.string());
        }
        else
        {
            m_EnginePath = DetectEngineInstallation();
        }

        const auto logPath = std::filesystem::path(m_EnginePath).append("logs");
        Log::Init(logPath, m_Config.LogLevel);
        Log::Trace("Engine installation found at: {0}", m_EnginePath.string());
        Log::Trace("Log path set to: {0}", logPath.string());

        Log::Trace("Validation Application config...");
        if (m_Config.Name == nullptr || m_Config.Name[0] == '\0')
        {
            Log::Error("Application name is empty!");
            FISCHI_ABORT();
        }

        if (m_Config.Version == nullptr || m_Config.Version[0] == '\0')
        {
            Log::Error("Application version is empty!");
            FISCHI_ABORT();
        }
        Log::Trace("Successfully validated Application config!");

        Platform::Init();
    }

    Application::~Application()
    {
        Log::Info("Fischi Engine shutting down...");
        RenderPlatform::OnShutdown();
        Platform::Shutdown();
    }

    void Application::Run()
    {
        OnStartup();

        if (m_Windows.empty())
        {
            Log::Error("No windows created! Exiting...");
            FISCHI_ABORT();
            return;
        }

        m_MainWindow = m_Windows[0];

        while (true)
        {
            if (!m_MainWindow->IsOpen())
                break;

            //ScopedTimer timer("Frame");

            for (Event* event = m_EventQueue.begin(); event < m_EventQueue.end(); event +=
                 EventQueue::GetMaxEventSize())
            {
                //Log::Trace("Event: {0}", event->ToString());
                // TODO: Handle default events
                if (OnEvent(event))
                    continue;

                for (const auto window : m_Windows)
                {
                    if (window->OnEvent(event))
                        break;
                }
            }
            m_EventQueue.Clear();

            OnUpdate();

            for (const auto window : m_Windows)
            {
                window->OnUpdate();
            }
        }

        OnShutdown();
    }

    Application* Application::Get()
    {
        return s_ApplicationInstance;
    }
}
