#include "sayhello.h"
#include <ctime>

std::string sayHello() {
    std::time_t now = std::time(nullptr);
    char timestamp[100];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    printf("Hello! Current time is: %s\n", timestamp);
    return "Hello! Current time is: " + std::string(timestamp);
}