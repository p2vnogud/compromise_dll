// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

DWORD WINAPI ThreadProc(LPVOID lpParam) {
    Sleep(2000);  // Delay để thread chạy và gây contention
    LoadLibraryA("nonexistent.dll");  // Yêu cầu Loader Lock, nhưng bị block
    return 0;
}
HANDLE hThread;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        //LoadLibraryA("C:\\Users\\learn\\source\\dll\\deadlock\\dllB\\x64\\Release\\dllB.dll");
        // Gây deadlock: Tạo thread và wait cho nó
        hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
        if (hThread) {
            WaitForSingleObject(hThread, INFINITE);  // Wait → deadlock vì new thread cần lock
            CloseHandle(hThread);
        }
        break;
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

