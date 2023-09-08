#define CLOG_IMPLEMENTATION
#include "clog.h"

int main() {
    clog_trace("Hello, World!");
    clog_info("This is an info message");
    clog_warn("This is a warning message. Be wary.");
    clog_error("ERROR!");
    clog_fatal("Crash. :(");
}
