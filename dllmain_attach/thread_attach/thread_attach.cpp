#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    printf("[EXE] Thread started: %lu\n", GetCurrentThreadId());
    Sleep(1000);
    return 0;
}

int main()
{
    printf("[EXE] Main thread id: %lu\n", GetCurrentThreadId());

    // Load DLL trước khi tạo thread
    HMODULE h = LoadLibraryA("dll_thread_attach.dll");
    if (!h) {
        printf("LoadLibrary failed: %lu\n", GetLastError());
        return 1;
    }

    // Tạo 3 thread mới
    for (int i = 0; i < 3; i++) {
        HANDLE th = CreateThread(NULL, 0, ThreadProc, 0, 0, 0);
        CloseHandle(th);
    }

    Sleep(2000);
    FreeLibrary(h);
    printf("[EXE] Done.\n");
    return 0;
}
