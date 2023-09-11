#ifndef CLOG_H
#define CLOG_H

#include <time.h>
#include <stdio.h>

#define CLOG_GRAY   0
#define CLOG_YELLOW 3
#define CLOG_RED    1
#define CLOG_PURPLE 5

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

#ifdef CLOG_IMPLEMENTATION

#define TERMANSI_IMPLEMENTATION
#include "termansi/termansi.h"

void clog_color(int id) {
#ifdef CLOG_TERMCOLOR
    ansi_color_foreground256(id);
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

void clog_write(const char *message, const char *severity, const char *filename, int line) {
    char timestamp_buf[9];
    time_t t = time(0);
    struct tm tm = *localtime(&t);
    sprintf(timestamp_buf, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    timestamp_buf[9] = '\0';

    printf("%s [%s], %s:%d: %s\n", severity, timestamp_buf, filename, line, message);
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
