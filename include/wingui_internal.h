#include "wingui.h"
#include <windows.h>

void wingui_internal_gate_set_instance(HINSTANCE inst);
HINSTANCE wingui_internal_gate_get_instance();

void wingui_internal_gate_set_win_count(int count);
void wingui_internal_gate_change_win_count(int d);
int wingui_internal_gate_get_win_count();

WINGUI_EVENT_TYPE wingui_internal_gate_code2event(int code,WINGUI_WIDGET_TYPE type);
WINGUI_WIDGET* wingui_internal_gate_id2widget(WINGUI_WINDOW *window,int id);
