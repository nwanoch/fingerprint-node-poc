#include <napi.h>
#include "sayhello.h"

Napi::String SayHelloWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string result = sayHello();
    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "sayHello"),
                Napi::Function::New(env, SayHelloWrapper));
    return exports;
}

NODE_API_MODULE(addon, Init)