#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wingui.h"
#include "wingui_internal.h"
#include "utils.h"

static HBRUSH g_wingui_brush;

static LRESULT CALLBACK wingui_internal_window_proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){
    WINGUI_WINDOW *window=(WINGUI_WINDOW*)GetWindowLongPtr(hwnd,GWLP_USERDATA);

    switch(msg){
        case WM_COMMAND:{
            int id=LOWORD(wParam);
            int code=HIWORD(wParam);
            WINGUI_WIDGET *widget=wingui_internal_gate_id2widget(window,id);


            if (widget==NULL || widget->on_event==NULL) break;


            widget->on_event(wingui_internal_gate_code2event(code,widget->type),widget,widget->callback_data);

            break;
        }
        case WM_DESTROY:
            wingui_window_destroy(window);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_CTLCOLORSTATIC:{
            return (INT_PTR)g_wingui_brush;
        }
        default:
            return DefWindowProc(hwnd,msg,wParam,lParam);
    }

    return 0;
}

void wingui_init(HINSTANCE hInstance){
    wingui_internal_gate_set_instance(hInstance);
    g_wingui_brush=CreateSolidBrush(RGB(255,255,255));

    WNDCLASS wc={0};
    wc.lpfnWndProc=wingui_internal_window_proc;
    wc.hInstance=hInstance;
    wc.lpszClassName=TEXT("WinGUIWindowClass");
	wc.hbrBackground=CreateSolidBrush(RGB(0,0,0));

    RegisterClass(&wc);
}

void wingui_run(){
    MSG msg;
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void wingui_quit(){
    DeleteObject(g_wingui_brush);
    PostQuitMessage(0);
}
