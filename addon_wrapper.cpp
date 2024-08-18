#include <napi.h>
#include <iostream>

// Declare the functions from dll_wrapper.cpp
extern bool LoadDLL();
extern int CallDLLFunction();
extern void UnloadDLL();

Napi::Number CallDLL(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    int result = CallDLLFunction();
    return Napi::Number::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    if (!LoadDLL()) {
        Napi::Error::New(env, "Failed to load DLL").ThrowAsJavaScriptException();
        return exports;
    }

    exports.Set(Napi::String::New(env, "callDLL"), Napi::Function::New(env, CallDLL));
    return exports;
}

NODE_API_MODULE(addon, Init)