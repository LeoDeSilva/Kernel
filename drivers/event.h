#ifndef EVENT_H
#define EVENT_H

#define MAX_EVENTS 256
#define BACKSPACE 0x0E
#define ENTER 0x1C


typedef struct {
    enum EventType {
        KEY_DOWN,
        NIL,
    } type;

    union {
        struct KeyDownEvent {
            int keycode;
            int scancode;
        } keydown;
    } data;
} Event;

Event pop_event();
void push_event(Event e);

#endif
