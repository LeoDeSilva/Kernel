# Kernel

A C kernel and bootloader extending on the book "Writing an Operating System from Scratch". An exploration for a project that will ultimately become my NEA (Non Exam Assessment) for Computer Science A Level.

## Keyboard Driver

Event polling as an additional to interrupts, requires global EventHandler state that can be accessed throughout the kernel & struct polymorphism / interhitance. Contain eventHandler constructs and defenitions inside "libc/events.h".

```c
typedef struct {
  enum EventType {
    KEY_UP,
    QUIT,
  } type;
  union {
    struct KeyUpEvent {
      int keycode;
    } keyup;
    struct QuitEvent {
      int reason;
    } quit;
  } data;
} Event;

Event events[MAX_EVENTS];

Event event;
event.type = KEY_UP;
event.data.keyup.keycode = VK_UP;
event.data.keyup.scancode = VK_UP;
events[0] = event;
```


```c
/*** event.c ***/
struct Event {
    type: char[];
}

struct KeyDown : Event {
    scancode: scancode,
    key:  char;
}

/*** keyboard.c ***/

static void keyboard_callback(registers_t regs) {
    events.append(KeyDown { scancode: scancode, key: ch })
    UNUSED(regs);
}

/*** io.c ***/

void readline(char *o_buf) {
    char *i_buf;

    whlie (1) {
        event = event.next();
        if (event.scancode == ENTER) { 
            kprint('\n');
            break;
        } else if (event.scancode == BACKSPACE) {
            kprint_backspace();
            buf.pop();
        }

        i_buf.append(event.key);
        kprint(event.key);
    }

    memcpy(i_buf, o_buf);
}

/*** kernel.c ***/

int update() {
    while (1) {
        event = events.next();
        switch (event.type) {
            case KEY_DOWN:
                kprint(event.key);
                break;
        }
    }
}

int kernel() {
    char *cmd_buf;
    while (1) {
        kprint(">>");
        readline(cmd_buf);
    
        [...]
    }
}
```
