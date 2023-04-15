// klanklank.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "interception.h"
#include "scancodes.h"
#include <windows.h>

enum GlobalModes
{
    ModePass,
    ModeKlank,
};

struct State
{
    InterceptionContext intercepion_ctx;
    InterceptionDevice device;
    GlobalModes global_mode;
    bool is_esc_down;
    bool galt_down;
    bool caps_down;
    bool need_exit;
    bool cursor_mode_on;
    bool cursor_toggle_mode_on;
    bool cursor_toggle_on;
    bool cursor_mode;
    bool alt_remap_enabled;
};

typedef uint16_t ushort;
typedef uint32_t uint;

struct Stroke
{
    ushort code;
    bool is_down;
    bool e0;
};

static State _state;

char flag(int i)
{
    return i ? 'x' : '-';
}

void send_stroke(ushort code, bool is_down)
{
    InterceptionKeyStroke ik = { code, is_down ? 0 : INTERCEPTION_KEY_UP , 0 };
    interception_send(_state.intercepion_ctx, _state.device, (InterceptionStroke*)&ik, 1);
}

struct RemapElement
{
    ushort in_code;
    ushort out_code;
};

RemapElement _arrow_remap[] = 
{
    {SC_L, SC_LEFT},
    {SC_APOS, SC_RIGHT},
    {SC_P, SC_UP},
    {SC_SEMI, SC_DOWN},
    {SC_LBRACK, SC_PGUP},
    {SC_RBRACK, SC_PGDOWN},
    {SC_O, SC_HOME},
    {SC_K, SC_END},
    {SC_NOP}
};

RemapElement _arrow_remap_alt[] =
{
    {SC_K, SC_LEFT},
    {SC_SEMI, SC_RIGHT},
    {SC_O, SC_UP},
    {SC_L, SC_DOWN},
    {SC_P, SC_PGUP},
    {SC_LBRACK, SC_PGDOWN},
    {SC_I, SC_HOME},
    {SC_J, SC_END},
    {SC_NOP}
};


bool update(InterceptionKeyStroke istroke)
{
    Stroke s = {istroke.code, (istroke.state & INTERCEPTION_KEY_UP)== 0, (istroke.state & INTERCEPTION_KEY_E0) != 0 };
    if(s.code == SC_ESCAPE)
    {
        _state.is_esc_down = s.is_down;
    }
    else if(s.code == SC_LALT && s.e0)
    {
        if (_state.cursor_toggle_mode_on)
        {
            if(s.is_down && !_state.galt_down)
            {
                _state.cursor_mode = !_state.cursor_mode;
                printf("Cursor mode: %s\n", _state.cursor_mode ? "ON" : "OFF");
            }
        }
        else
        {
            _state.cursor_mode = s.is_down;
        }
;        _state.galt_down = s.is_down;

        return false;
    }
    else if(s.code == SC_LALT)
    {
        _state.caps_down = s.is_down;
        send_stroke(SC_LCTRL, s.is_down);
        return false;
    }
    else if(s.code == SC_LCTRL)
    {
        send_stroke(SC_LALT, s.is_down);
        return false;
    }
    
    if(_state.is_esc_down && s.is_down)
    {
        if(s.code == SC_X)
        {
            _state.need_exit = true;
            return false;
        }
        if(s.code == SC_1)
        {
            _state.global_mode = ModePass;
            printf("Passtrough mode\n");
            return false;
        }
        if(s.code == SC_2)
        {
            _state.global_mode = ModeKlank;
            printf("Klank mode\n");
            return false;
        }
        if(s.code == SC_F1)
        {
            _state.cursor_toggle_mode_on = !_state.cursor_toggle_mode_on;
            printf("Cursor toggle mode: %s\n", _state.cursor_toggle_mode_on ? "ON" : "OFF");
            return false;
        }
        if(s.code == SC_N)
        {
            send_stroke(SC_NUMLOCK, true);
            send_stroke(SC_NUMLOCK, false);
        }
        if(s.code == SC_A)
        {
            _state.alt_remap_enabled = !_state.alt_remap_enabled;
        }
    }

    if(_state.global_mode == ModePass)
        return true;

    //KLANK mode
    if(s.code == SC_CAPS)
    {
        send_stroke(SC_LALT, s.is_down);
        return false;
    }

    if(_state.alt_remap_enabled)
    {
        //block printscreen in alt mode
        if(s.code == 0x37 && s.e0)
            return false;
    }

    if(_state.cursor_mode)
    {
        auto r = _state.alt_remap_enabled ? _arrow_remap_alt : _arrow_remap;
        for(; r->in_code != SC_NOP; ++r)
        {
            if(r->in_code == s.code)
                break;
        }
        if(r->in_code != SC_NOP)
        {
            printf("Send %x instead of %x\n", r->out_code, r->in_code);
            send_stroke(r->out_code, s.is_down);
            return false;                  
        }
    }

    return true;
}

int main()
{
    InterceptionDevice device;
    InterceptionKeyStroke stroke;

    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

    memset(&_state, 0, sizeof(_state));
    _state.global_mode = ModeKlank;
    _state.intercepion_ctx = interception_create_context();

    interception_set_filter(_state.intercepion_ctx, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP | INTERCEPTION_FILTER_KEY_E0 | INTERCEPTION_FILTER_KEY_E1);

    while (interception_receive(_state.intercepion_ctx, device = interception_wait(_state.intercepion_ctx), (InterceptionStroke *)&stroke, 1) > 0)
    {
        printf("Raw event: code=%x info=%x state=%u up=%c e0=%c e1=%c\n", stroke.code, stroke.information, stroke.state,
            flag(stroke.state & INTERCEPTION_KEY_UP),
            flag(stroke.state & INTERCEPTION_KEY_E0),
            flag(stroke.state & INTERCEPTION_KEY_E1));


        _state.device = device;
        if(update(stroke))
        {
            interception_send(_state.intercepion_ctx, device, (InterceptionStroke *)&stroke, 1);
        }

        if(_state.need_exit)
            break;
    }

    interception_destroy_context(_state.intercepion_ctx);

    return 0;
}

