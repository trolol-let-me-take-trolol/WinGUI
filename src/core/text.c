#include <windows.h>
#include "wingui.h"

SIZE wingui_text_get_size(TCHAR *text,int length){
    SIZE invalid={-1,-1};
    if (text==NULL) return invalid;
    HDC dc=GetDC(NULL);
    if (dc==NULL) return invalid;
    SIZE size;
    BOOL result=GetTextExtentPoint32(dc,text,length,&size);
    ReleaseDC(NULL,dc);
    if (result)
        return size;
    return invalid;
}

long wingui_text_get_width(TCHAR *text,int length){
    if (text==NULL) return -1;
    return wingui_text_get_size(text,length).cx;
}

long wingui_text_get_height(TCHAR *text,int length){
    if (text==NULL) return -1;
    return wingui_text_get_size(text,length).cy;
}
