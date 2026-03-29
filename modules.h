/* =================== */
/* ===== helpers ===== */
/* =================== */
#include "scripts.h"

static char *run_script(const char *script, char *buf) {
    /*
     *  This functions lets you run write shell scripts directly here. Check out the `tmux_sessions`
     * */
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "sh -s << 'EOF'\n%s\nEOF", script);
    FILE *f = popen(cmd, "r");
    if (!f) return buf;
    fgets(buf, BUFSIZE, f);
    pclose(f);
    buf[strcspn(buf, "\n")] = '\0';
    return buf;
}

static char *generate_module(const char *script, char *buf) {
    /*
     *  This functions lets you embed scripts found in the `scripts` directory.
     *  Makefile generates `scripts.h` file, which contains all the scripts found in the folder.
     *  Check out ` battery_script`
     * */
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "sh -s << 'EOF'\n%s\nEOF", script);
    FILE *f = popen(cmd, "r");
    if (!f) return buf;
    fgets(buf, BUFSIZE, f);
    pclose(f);
    buf[strcspn(buf, "\n")] = '\0';
    return buf;
}

/* =================== */
/* ===== modules ===== */
/* =================== */

/* ===== datetime ===== */
char *datetime(void) {
    static char buf[BUFSIZE];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    const char *icons[] = {
        "󱑖", "󱑋", "󱑌", "󱑍", "󱑎", "󱑏",
        "󱑐", "󱑑", "󱑒", "󱑓", "󱑔", "󱑕"
    };

    int h = tm->tm_hour % 12;
    strftime(buf, BUFSIZE, "%d %b %Y|", tm);
    strncat(buf, icons[h], BUFSIZE - strlen(buf) - 1);
    char tmp[16];
    strftime(tmp, sizeof(tmp), "%R:%S", tm);
    strncat(buf, tmp, BUFSIZE - strlen(buf) - 1);

    return buf;
}

/* ===== ncs ===== */
extern Display *display;

char *ncs(void) {
    static char buf[BUFSIZE];
    buf[0] = '\0';

    XKeyboardState state;
    XGetKeyboardControl(display, &state);

    unsigned long led = state.led_mask;

    if (led & 1) { strcat(buf, "[CAP]"); }
    if (led & 2) { strcat(buf, "[NUM]"); }
    if (led & 4) { strcat(buf, "[SCR]"); }

    return buf;
}

/* ===== tmux_sessions ===== */
char *tmux_sessions(void) {
    static char buf[BUFSIZE];
    run_script(
        "#!/bin/sh\n"
        "sessions=$(tmux list-sessions 2>/dev/null | wc -l)\n"
        "[ \"$sessions\" -gt 0 ] && printf \" %d\" \"$sessions\"\n",
        buf
    );
    return buf;
}

/* ===== volume ===== */
char *battery_script(void) {
    static char buf[BUFSIZE];
    return generate_module(mb_battery, buf); // scripts/mb-battery
}

/* ===== kblayout ===== */
char *kb_script(void) {
    static char buf[BUFSIZE];
    return generate_module(kblayout, buf);
}

/* ===== cpu ===== */
char *cpu_script(void) {
    static char buf[BUFSIZE];
    return generate_module(cpu, buf);
}

/* ===== volume ===== */
char *volume_script(void) {
    static char buf[BUFSIZE];
    return generate_module(volume, buf);
}


/* ===== net ===== */
char *net_script(void) {
    static char buf[BUFSIZE];
    return generate_module(net, buf);
}

/* ===== mail ===== */
char *mail_script(void) {
    static char buf[BUFSIZE];
    return generate_module(email, buf);
}

/* ===== newsboat ===== */
char *newsboat_script(void) {
    static char buf[BUFSIZE];
    return generate_module(newsboat, buf);
}
