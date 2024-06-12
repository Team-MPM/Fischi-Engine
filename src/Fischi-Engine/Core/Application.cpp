#include "Application.h"

#include <filesystem>
#include <iostream>

#include "Log.h"

namespace FischiEngine
{
    std::filesystem::path Application::DetectEngineInstallation()
    {
        bool engineFound = false;
        std::filesystem::path enginePath;
        
        if (!engineFound && std::filesystem::exists("bin"))
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator("bin"))
            {
                if (entry.is_regular_file() &&(entry.path().filename() == "FischiEngine.lib" || entry.path().filename()== "libFischi-Engine.a"))
                {
                    enginePath = std::filesystem::absolute(".");
                    engineFound = true;
                    break;
                }
            }
        }
        
        if (!engineFound && std::filesystem::exists("../../bin"))
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator("../../bin"))
            {
                if (entry.is_regular_file() && (entry.path().filename() == "FischiEngine.lib" || entry.path().filename() =="libFischi-Engine.a"))
                {
                    enginePath = std::filesystem::absolute("../../");
                    engineFound = true;
                    break;
                }
            }
        }

        if (const char* envVarPath = std::getenv("FISCHI_ENGINE_PATH"); envVarPath != nullptr)
        {
            enginePath = std::filesystem::absolute(envVarPath);
            engineFound = true;
        }
        
        if (!engineFound)
        {
            Log::Fatal("Engine installation not found! Exiting...");
            FISCHI_ABORT();
        }

        
        Log::Trace("Engine installation found at: {0}", enginePath.string());

        return enginePath;
    }

    Application::Application(const ApplicationConfig& config, int argc, char** argv)
        : m_Config(config)
    {
        std::cout << "Starting Fischi Engine!\n";
        Log::Init();

        Log::Trace("Detecting Engine Path...");

        if (m_Config.Standalone)
        {
            m_EnginePath = std::filesystem::absolute(argv[0]).parent_path();
            Log::Trace("Loading Standalone Engine at: {0}", m_EnginePath.string());
        }
        else
        {
            m_EnginePath = DetectEngineInstallation();
        }

        Log::Trace("Validation Application config...");
        
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (true)
        {
            
        }
    }
}
