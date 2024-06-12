#include <string>
#include "Fischi-Engine/Core/Log.h"

using namespace FischiEngine;
using namespace FischiEngine::Core;

int main(void) {
   Log::Init();
   Log::Trace("Hello world! My number is {}", 42);
   Log::Debug("Hello world! My number is {}", 42);
   Log::Info("Hello world! My number is {}", 42);
   Log::Warn("Hello world! My number is {}", 42);
   Log::Error("Hello world! My number is {}", 42);
   Log::Fatal("Hello world! My number is {}", 42);
   return 0;
}