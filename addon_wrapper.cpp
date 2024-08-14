#include <napi.h>

// Declare the functions from dll_wrapper.cpp
extern bool LoadDLL();
extern int CallDLLFunction();
extern void UnloadDLL();

// Existing sayHello function
Napi::String SayHello(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, "Hello, World!");
}

// New function to call DLL function
Napi::Number CallDLL(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int result = CallDLLFunction();
    return Napi::Number::New(env, result);
}

// Initialize function
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // Load the DLL when the addon is initialized
    if (!LoadDLL()) {
        Napi::Error::New(env, "Failed to load DLL").ThrowAsJavaScriptException();
        return exports;
    }

    exports.Set(Napi::String::New(env, "sayHello"), Napi::Function::New(env, SayHello));
    exports.Set(Napi::String::New(env, "callDLL"), Napi::Function::New(env, CallDLL));
    return exports;
}

NODE_API_MODULE(addon, Init)