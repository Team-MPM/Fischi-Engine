import core;
import std;

int main() {
    DIContainer container;

    auto logger = container.resolve<Logger>();
    logger->info("Hello World!");

    auto math = container.resolve<Math>();
    math->add(5, 5);

    return 0;
}
