/* =================== */
/* ===== helpers ===== */
/* =================== */
#include "scripts.h"

static char *generate_module(const char *script, char *buf) {
    /*
     *  This function lets you embed scripts as modules.
     *  Makefile generates `scripts.h` file, which contains all the scripts.
     *  You can embed them either by adding the script inside the `scripts` directory (see `battery_script`)
     *  Or by directly writing the script in a function (see `tmux_sessions`)
     * */
    char tmpfile[] = "/tmp/modbar_XXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd < 0) return buf;
    write(fd, script, strlen(script));
    close(fd);

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "sh %s", tmpfile);
    FILE *f = popen(cmd, "r");
    if (!f) { unlink(tmpfile); return buf; }
    fgets(buf, BUFSIZE, f);
    pclose(f);
    unlink(tmpfile);

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
    static const char script[] =
        "#!/bin/sh\n"
        "sessions=$(tmux list-sessions 2>/dev/null | wc -l)\n"
        "[ \"$sessions\" -gt 0 ] && printf \" %d\" \"$sessions\"\n";
    return generate_module(script, buf);
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
