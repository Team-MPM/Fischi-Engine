export module core:app;

import :logger;
import :di;
import :events;

export struct AppConfig {
    bool UseRendering;
};

export class App {
public:
    explicit App(const AppConfig config = {})
        : m_Services({}), m_IsRunning(false), m_Config(config)
    {
    }

    template<typename Service>
    Service* get_service() {
        return m_Services.resolve<Service>();
    }

    void run() {
        m_IsRunning = true;
        while (m_IsRunning) {
            update();
        }
    }

    bool is_running() const {
        return m_IsRunning;
    }

    void stop() {
        m_IsRunning = false;
    }

    EventQueue* get_event_queue() {
        return &eventQueue;
    }

    EventDispatcher* get_event_dispatcher() {
        return &dispatcher;
    }

private:
    void update() {
        dispatcher.processEvents(eventQueue);
    }
public:

private:
    DIContainer m_Services{};
    bool m_IsRunning;
    AppConfig m_Config;
    EventQueue eventQueue;
    EventDispatcher dispatcher;
};