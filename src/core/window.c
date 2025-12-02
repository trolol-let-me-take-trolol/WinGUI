#include <windows.h>
#include "wingui.h"
#include "wingui_internal.h"
#include "utils.h"

WINGUI_WINDOW* wingui_window_create(const TCHAR *title,int width,int height){
    HWND hwnd=CreateWindow(TEXT("WinGUIWindowClass"),
                           title,
                           WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT,CW_USEDEFAULT,
                           width,height,
                           NULL,NULL,wingui_internal_gate_get_instance(),NULL);
    if (hwnd==NULL) return NULL;
    WINGUI_WINDOW *window=malloc(sizeof(WINGUI_WINDOW));
    if (window==NULL) return NULL;
    List *widgets=list_create(16);
    if (widgets==NULL) return NULL;

    window->hwnd=hwnd;
    window->title=title;
    window->widgets=widgets;

    SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)window);

    wingui_internal_gate_change_win_count(1);
    wingui_label_create(window,"",0,0,width,height,NULL,NULL);
    return window;
}

void wingui_window_show(WINGUI_WINDOW *window,int type){
    if (window==NULL || window->hwnd==NULL) return;
    ShowWindow(window->hwnd,type);
}

void wingui_window_destroy(WINGUI_WINDOW *window) {
    if (window==NULL) return;

    if (window->widgets) {
        for (int i=0;i<window->widgets->count;i++) {
            WINGUI_WIDGET *w=window->widgets->items[i];
            if (w){
                DestroyWindow(w->hwnd);
                free(w);
            }
        }
        list_free(window->widgets);
    }

    free(window);
    wingui_internal_gate_change_win_count(-1);
    if (wingui_internal_gate_get_win_count()==0) wingui_quit();
}
