#define CLOG_IMPLEMENTATION
#define CLOG_TERMCOLOR
#include "clog.h"

int main() {
    clog_trace("Hello, World!");
    clog_info("This is an info message");
    clog_warn("This is a warning message. Be wary.");
    clog_error("Error");
    clog_fatal("Crash");
}
