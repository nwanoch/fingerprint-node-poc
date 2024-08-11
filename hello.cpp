#include <napi.h>
#include <iostream>
#include <ctime>

Napi::Value SayHello(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    // Get current time
    std::time_t now = std::time(nullptr);
    char timestamp[100];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    // Print hello message with timestamp
    std::cout << "Hello! Current time is: " << timestamp << std::endl;
    
    // Return a string to Node.js
    return Napi::String::New(env, "Hello function called");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "sayHello"),
                Napi::Function::New(env, SayHello));
    return exports;
}

NODE_API_MODULE(hello, Init)