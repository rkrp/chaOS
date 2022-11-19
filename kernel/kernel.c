#include "chaos-core.h"
#include "printk.h"
#include "test.h"



static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

// The following will be our kernel's entry point.
void _start(void) {
    /*
    // Ensure we got a terminal
    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
    }
    */

    // We should now be able to call the Limine terminal to print out
    // a simple "Hello World" to screen.

#ifdef CHAOS_TEST 
    test_entry();
    done();
#endif
    printk("Kernel loaded at %p\n", &_start);

    // We're done, just hang...
    done();
}
