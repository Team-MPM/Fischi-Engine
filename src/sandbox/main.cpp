import core;
import std;

int main() {
    DIContainer container;

    auto logger = container.resolve<Logger>();
    logger->info("Hello World!");

    //auto math = container.resolve<Math>();
    //math->add(5, 5);

    App app;

    app.get_event_dispatcher()->registerHandler<TestEvent>([](const TestEvent& e) {
        std::cout << "Button Press Event: button " << (int)e.getType() << "\n";
    });

    app.get_event_queue()->pushEvent<TestEvent>();

    app.run();

    return 0;
}
