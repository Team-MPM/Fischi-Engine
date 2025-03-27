export module core:events;

import std;
import :math;
import :service;

export enum class EventType : uint32_t {
    ButtonPress,
    ButtonRelease,
    KeyPress,
    KeyRelease,
};

export enum class EventCategory : uint32_t {
    None = 0,
    Input = 1 << 0,
    UI = 1 << 1,
};

export constexpr inline EventCategory operator|(EventCategory a, EventCategory b) {
    return static_cast<EventCategory>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

export constexpr inline EventCategory operator&(EventCategory a, EventCategory b) {
    return static_cast<EventCategory>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

export class Event {
public:
    virtual ~Event() = default;
    virtual EventType getType() const = 0;
    virtual EventCategory getCategory() const = 0;
};

export class EventQueue final : public IService {
public:
    template<typename EventT, typename... Args>
    void pushEvent(Args &&...args) {
        static_assert(std::is_base_of_v<Event, EventT>, "EventT must derive from Event");

        m_Events.emplace_back(std::make_unique<EventT>(std::forward<Args>(args)...));
    }

    const std::vector<std::unique_ptr<Event>> &getEvents() const { return m_Events; }

    void clear() { m_Events.clear(); }

private:
    std::vector<std::unique_ptr<Event>> m_Events;
};

export class EventDispatcher final : public IService {
public:
    template<typename EventT>
    void registerHandler(std::function<void(const EventT &)> handler) {
        auto key = EventT::getStaticType();
        m_Handlers[key].push_back([handler](const Event &event) { handler(static_cast<const EventT &>(event)); });
    }

    void processEvents(EventQueue &queue) const {
        for (const auto &eventPtr: queue.getEvents()) {
            auto type = eventPtr->getType();
            auto it = m_Handlers.find(type);
            if (it != m_Handlers.end()) {
                for (const auto &handler: it->second) {
                    handler(*eventPtr);
                }
            }
        }
        queue.clear();
    }

private:
    using HandlerFunc = std::function<void(const Event &)>;
    std::unordered_map<EventType, std::vector<HandlerFunc>> m_Handlers;
};

#define EVENT_TYPE(type)                                                                                               \
    static constexpr EventType getStaticType() { return EventType::type; }                                             \
    EventType getType() const override { return getStaticType(); }

#define EVENT_CATEGORY(category)                                                                                       \
    static constexpr EventCategory getStaticCategory() { return EventCategory::category; }                             \
    EventCategory getCategory() const override { return getStaticCategory(); }

#define EVENT_CLASS(name, type, category)                                                                              \
    export class name final : public Event {                                                                           \
    public:                                                                                                            \
        EVENT_TYPE(type)                                                                                               \
        EVENT_CATEGORY(category)                                                                                       \
    }

#define EVENT_CLASS_DATA(name, type, category, dataType)                                                               \
    export class name final : public Event {                                                                           \
    public:                                                                                                            \
        dataType data;                                                                                                 \
        name(dataType data) : data(data) {}                                                                            \
        EVENT_TYPE(type)                                                                                               \
        EVENT_CATEGORY(category)                                                                                       \
    }

EVENT_CLASS(TestEvent, ButtonPress, Input);
