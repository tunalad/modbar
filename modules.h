extern Display *display;

char *ncs(void) {
    static char buf[BUFSIZE];
    buf[0] = '\0';

    XKeyboardState state;
    XGetKeyboardControl(display, &state);

    unsigned long led = state.led_mask;
    int any = 0;

    if (led & 1) { strcat(buf, "[CAP]"); any = 1; }
    if (led & 2) { strcat(buf, "[NUM]"); any = 1; }
    if (led & 4) { strcat(buf, "[SCR]"); any = 1; }
    if (any)     { strcat(buf, "|"); }

    return buf;
}
