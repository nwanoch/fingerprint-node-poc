#include <windows.h>
#include <iostream>
#include <string>

// Function pointer types for the DLL functions
typedef int (*InitFunction)();

// Global variables to hold the DLL handle and function pointers
HMODULE hDLL = NULL;
InitFunction initFunction = NULL;

// Load the DLL and get function pointers
bool LoadDLL() {
    const char* dllPath = "iengine_ansi_iso.dll"; // Use absolute path if needed
    hDLL = LoadLibrary(dllPath);
    if (hDLL == NULL) {
        DWORD error = GetLastError();
        std::cerr << "Failed to load DLL: " << dllPath << ". Error: " << error << std::endl;
        return false;
    }

    initFunction = (InitFunction)GetProcAddress(hDLL, "Init");
    if (initFunction == NULL) {
        DWORD error = GetLastError();
        std::cerr << "Failed to get function address for 'Init'. Error: " << error << std::endl;
        FreeLibrary(hDLL);
        hDLL = NULL;
        return false;
    }

    std::cout << "DLL loaded successfully and Init function found." << std::endl;
    return true;
}

// Wrapper function to call DLL function
int CallDLLFunction() {
    if (initFunction == NULL) {
        std::cerr << "Init function is not loaded." << std::endl;
        return -1;
    }
    std::cout << "Calling Init function..." << std::endl;
    return initFunction();
}

// Clean up
void UnloadDLL() {
    if (hDLL != NULL) {
        FreeLibrary(hDLL);
        hDLL = NULL;
        initFunction = NULL;
        std::cout << "DLL unloaded." << std::endl;
    }
}