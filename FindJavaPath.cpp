#include <iostream>
#include <string>
#include <windows.h>

std::string GetJavaPathFromRegistry() {
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\JavaSoft\\Java Runtime Environment", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        char javaHome[MAX_PATH];
        DWORD bufferSize = sizeof(javaHome);
        if (RegGetValueA(hKey, nullptr, "JavaHome", RRF_RT_REG_SZ, nullptr, javaHome, &bufferSize) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            std::string javaPath(javaHome);
            return javaPath + "\\bin\\java.exe";
        }
        RegCloseKey(hKey);
    }

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\JavaSoft\\Java Development Kit", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        char javaHome[MAX_PATH];
        DWORD bufferSize = sizeof(javaHome);
        if (RegGetValueA(hKey, nullptr, "JavaHome", RRF_RT_REG_SZ, nullptr, javaHome, &bufferSize) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            std::string javaPath(javaHome);
            return javaPath + "\\bin\\java.exe";
        }
        RegCloseKey(hKey);
    }

    return "";
}

int retJava() {
    std::string javaExePath = GetJavaPathFromRegistry();

    if (javaExePath.empty()) {
        std::cout << "Java path not found." << std::endl;
        return false;
    }

    std::cout << "Java path: " << javaExePath << std::endl;

    return 0;
}
