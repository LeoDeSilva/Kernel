#include "event.h"

int n = 0;
Event events[MAX_EVENTS];

Event pop_event() {
    if (n == 0) {
        Event nil_event;
        nil_event.type = NIL;
        return nil_event;
    }

    Event tail = events[n-1];
    n--;
    return tail;
}

void push_event(Event e) {
    events[n] = e; 
    n++;
};