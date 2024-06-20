#pragma once
#include <filesystem>
#include <string>

#include "Event/Event.h"
#include "Memory/Memory.h"

namespace FischiEngine
{
    class Window
    {
    public:
        struct Spec
        {
            std::wstring WTitle = L"Fischi Engine";
            std::string Title = "Fischi Engine";
            uint32_t Width = 480, Height = 270;
            uint32_t X = 100, Y = 100;
            std::filesystem::path Icon = L"Resources/Icons/Icon.ico";
            bool Decorated = true, Fullscreen = false, Maximized = false, Minimized = false, VSync = false;
        };

        virtual ~Window() = default;

        static Shared<Window> Create(const Spec& spec);

        virtual void OnUpdate() = 0;
        virtual bool OnEvent(Event* event) = 0;
        
        virtual bool OnEventHandler(Event* event);

        virtual bool IsOpen() const = 0;
        virtual void Close() = 0;
        virtual void Minimize() = 0;
        virtual void Maximize() = 0;
        virtual void SetFullscreen(bool fullscreen) = 0;
        
        virtual std::pair<uint32_t, uint32_t> GetSize() const = 0;
		virtual std::pair<uint32_t, uint32_t> GetPos() const = 0;

        const Spec& GetSpec() const { return m_Spec; }
    protected:
        explicit Window(const Spec& spec);
        Spec m_Spec;
    };
}
