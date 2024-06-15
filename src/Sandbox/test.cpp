#include "Core/Application.h"
#include "Platform/Windows/WindowWindow.h"

using namespace FischiEngine;

class Sandbox : public Application
{
public:
    Sandbox(const ApplicationConfig& config, int argc, char** argv)
        : Application(config, argc, argv)
    {
    }

    void OnStartup() override
    {
        Window::Spec spec;
        m_Windows.push_back(Window::Create(spec));
    }
    
    bool OnEvent(Event* event) override
    {
        return false;
    }
    
    void OnUpdate() override
    {
        
    }
};

int main(int argc, char** argv) {
   ApplicationConfig config = {
       "Sandbox",
       "0.0.1",
       false
   };

    Sandbox app(config, argc, argv);
    app.Run();
    
   return 0;
}