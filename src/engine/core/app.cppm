export module core:app;

import :logger;
import :di;
import :events;

export struct AppConfig {
    bool UseRendering;
};

export class App final : public IService {
public:
    explicit App(const AppConfig config = {})
        : m_IsRunning(false), m_Config(config)
    {
        m_Services.registerService(this);
        m_Services.registerService(&m_EventDispatcher);
        m_Services.registerService(&m_EventQueue);
    }

    template<typename Service>
    Service* get_service() {
        return m_Services.resolve<Service>();
    }

    void run() {
        m_IsRunning = true;
        if (m_StartupCallback)
            m_StartupCallback();
        while (m_IsRunning) {
            if (m_UpdateCallback)
                m_UpdateCallback();
            update();
        }
        if (m_ShutdownCallback)
            m_ShutdownCallback();
    }

    bool is_running() const {
        return m_IsRunning;
    }

    void stop() {
        m_IsRunning = false;
    }

    const AppConfig& get_config() const {
        return m_Config;
    }

    DIContainer& get_services() {
        return m_Services;
    }

    void on_startup(std::function<void()> callback) {
        m_StartupCallback = std::move(callback);
    }

    void on_shutdown(std::function<void()> callback) {
        m_ShutdownCallback = std::move(callback);
    }

    void on_update(std::function<void()> callback) {
        m_UpdateCallback = std::move(callback);
    }

private:
    void update() {
        m_EventDispatcher.processEvents(m_EventQueue);
    }
public:

private:
    DIContainer m_Services{};
    bool m_IsRunning;
    AppConfig m_Config;
    EventQueue m_EventQueue{};
    EventDispatcher m_EventDispatcher{};
    std::function<void()> m_StartupCallback{};
    std::function<void()> m_ShutdownCallback{};
    std::function<void()> m_UpdateCallback{};
};