#include <windows.h>
#include <stdio.h>

__declspec(thread) int tls_var = 0; // ép hệ thống phải gọi DLL_THREAD_ATTACH

void Log(const char* msg)
{
    char buf[256];
    sprintf_s(buf, "[DLL] %s\n", msg);
    OutputDebugStringA(buf); // an toàn trong DllMain
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Log("PROCESS_ATTACH");
        break;
    case DLL_THREAD_ATTACH:
        Log("THREAD_ATTACH");
        break;
    case DLL_THREAD_DETACH:
        Log("THREAD_DETACH");
        break;
    case DLL_PROCESS_DETACH:
        Log("PROCESS_DETACH");
        break;
    }
    return TRUE;
}
