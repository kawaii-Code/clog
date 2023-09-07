#ifndef CLOG_H
#define CLOG_H

#include <time.h>
#include <stdio.h>
#include <assert.h>

#define CLOG_TERMCOLOR
#define CLOG_GRAY   100, 100, 100
#define CLOG_YELLOW 200, 200, 0
#define CLOG_RED    255, 0,   0
#define CLOG_PURPLE 255, 0,   255

#define clog_trace(message) clog_trace_internal(message, __FILE__, __LINE__)
#define clog_info(message)  clog_info_internal(message, __FILE__, __LINE__)
#define clog_warn(message)  clog_warn_internal(message, __FILE__, __LINE__)
#define clog_error(message) clog_error_internal(message, __FILE__, __LINE__)
#define clog_fatal(message) clog_fatal_internal(message, __FILE__, __LINE__)

void clog_trace_internal(const char *message, const char *filename, int line);
void clog_info_internal(const char *message, const char *filename, int line);
void clog_warn_internal(const char *message, const char *filename, int line);
void clog_error_internal(const char *message, const char *filename, int line);
void clog_fatal_internal(const char *message, const char *filename, int line);

#define CLOG_IMPLEMENTATION
#ifdef CLOG_IMPLEMENTATION

#define TERMANSI_IMPLEMENTATION
#include "termansi.h"

void clog_color(int r, int g, int b) {
#ifdef CLOG_TERMCOLOR
    ansi_color_setforeground(r, g, b);
#endif
}

void clog_bold() {
#ifdef CLOG_TERMCOLOR
    ansi_style_bold();
#endif
}

void clog_resetcolor() {
#ifdef CLOG_TERMCOLOR
    ansi_style_reset();
#endif
}

void clog_get_timestamp(char *buf, size_t buf_length) {
    assert(buf_length > 8);

    time_t t = time(0);
    struct tm tm = *localtime(&t);
    sprintf(buf, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    buf[9] = '\0';
}

void clog_write(const char *message, const char *severity, const char *filename, int line) {
    char timestampBuf[9];
    clog_get_timestamp(timestampBuf, 9);

    printf("%s [%s], %s:%d: %s\n", severity, timestampBuf, filename, line, message);
}

void clog_trace_internal(const char *message, const char *filename, int line) {
    clog_color(CLOG_GRAY);
    clog_write(message, "TRACE", filename, line);
    clog_resetcolor();
}

void clog_info_internal(const char *message, const char *filename, int line) {
    clog_write(message, "INFO ", filename, line);
}

void clog_warn_internal(const char *message, const char *filename, int line) {
    clog_color(CLOG_YELLOW);
    clog_write(message, "WARN ", filename, line);
    clog_resetcolor();
}

void clog_error_internal(const char *message, const char *filename, int line) {
    clog_color(CLOG_RED);
    clog_bold();
    clog_write(message, "ERROR", filename, line);
    clog_resetcolor();
}

void clog_fatal_internal(const char *message, const char *filename, int line) {
    clog_color(CLOG_PURPLE);
    clog_write(message, "FATAL", filename, line);
    clog_resetcolor();
}

#endif // CLOG_IMPLEMENTATION

#endif // CLOG_H
