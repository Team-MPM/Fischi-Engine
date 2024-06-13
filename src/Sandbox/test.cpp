#include "Core/Application.h"

using namespace FischiEngine;

int main(int argc, char** argv) {
   ApplicationConfig config = {
       "Sandbox",
       "0.0.1",
       false
   };

    Application app(config, argc, argv);
    app.Run();
    
   return 0;
}