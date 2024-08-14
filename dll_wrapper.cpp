#include <napi.h>
#include <windows.h>
#include <iostream>

// Function pointer types for the DLL functions
typedef int (*DLLFunction)();

// Global variables to hold the DLL handle and function pointers
HMODULE hDLL = NULL;
DLLFunction dllFunction = NULL;

// Load the DLL and get function pointers
bool LoadDLL() {
    // You can try both with a relative path and an absolute path
    hDLL = LoadLibrary("C:\\Users\\emman\\OneDrive\\Desktop\\fingerprint-node-poc\\Innovatrics.Sdk.commons.dll");
    if (hDLL == NULL) {
        std::cerr << "Failed to load DLL. Error: " << GetLastError() << std::endl;
        return false;
    }
    
    dllFunction = (DLLFunction)GetProcAddress(hDLL, "SomeFunctionName");
    if (dllFunction == NULL) {
        std::cerr << "Failed to get function address. Error: " << GetLastError() << std::endl;
        return false;
    }

    return true;
}

// Wrapper function to call DLL function
int CallDLLFunction() {
    if (dllFunction == NULL) return -1;
    return dllFunction();
}

// Clean up
void UnloadDLL() {
    if (hDLL != NULL) {
        FreeLibrary(hDLL);
        hDLL = NULL;
        dllFunction = NULL;
    }
}
