#include <napi.h>
#include <iostream> // For debugging output

// Declare the functions from dll_wrapper.cpp
extern bool LoadDLL();
extern int CallDLLFunction();
extern void UnloadDLL();

// Function to say hello (existing function)
Napi::String SayHello(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, "Hello, World!");
}

// New function to call the DLL function
Napi::Number CallDLL(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    // Attempt to call the function from the DLL
    int result = CallDLLFunction();

    // Return the result to JavaScript
    return Napi::Number::New(env, result);
}

// Initialize function
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // Attempt to load the DLL when the addon is initialized
    if (!LoadDLL()) {
        // If DLL loading fails, throw a JavaScript exception
        Napi::Error::New(env, "Failed to load DLL").ThrowAsJavaScriptException();
        return exports;
    }

    // Export the sayHello function
    exports.Set(Napi::String::New(env, "sayHello"), Napi::Function::New(env, SayHello));

    // Export the CallDLL function
    exports.Set(Napi::String::New(env, "callDLL"), Napi::Function::New(env, CallDLL));

    return exports;
}

// Define the module
NODE_API_MODULE(addon, Init)
