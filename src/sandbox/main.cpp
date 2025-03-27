import core;
import std;

int main() {
    App app;
    const auto logger = app.get_service<Logger>();

    app.on_startup([&] {
        logger->info("start");
    });

    app.on_update([&] {
       logger->info("update");
   });

    app.on_shutdown([&] {
       logger->info("off");
   });

    app.run();

    return 0;
}
