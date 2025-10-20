#include <windows.h>
#include <iostream>

int main() {
    // Tải DLL A, sẽ trigger DllMain và gây deadlock
    HMODULE hDll = LoadLibraryA("C:\\Users\\learn\\source\\dll\\deadlock\\dllA\\x64\\Release\\dllA.dll");
    if (hDll == NULL) {
        std::cout << "Failed to load DLL" << std::endl;
    }
    else {
        std::cout << "DLL loaded successfully" << std::endl;
    }
    return 0;
}