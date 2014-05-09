#ifndef _Main_h
#define _Main_h
#include <FL/Fl_Widget.H>

class DrawingArea : public Fl_Widget{
public:
    DrawingArea(int X,int Y,int W,int H);
    void draw_callback( void (*Function) (Fl_Widget* w, void* data), void* Data);
    void mouse_callback( void (*Function) (Fl_Widget* w, void* data), void* Data);
    void keyboard_callback( void (*Function) (Fl_Widget* w, void* data), void* Data);

private :
    void draw();
    int handle(int event);

    void (*_draw_callback_function) ( Fl_Widget* w, void* data);
    void* _draw_callback_data;

    void (*_mouse_callback_function) ( Fl_Widget* w, void* data);
    void* _mouse_callback_data;

    void (*_keyboard_callback_function) ( Fl_Widget* w, void* data);
    void* _keyboard_callback_data;
};
#endif
