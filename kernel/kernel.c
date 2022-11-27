#include "chaos-core.h"
#include "printk.h"
#include "idt.h"
#include "test.h"
#include "limine.h"


static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

uint64_t read_cr3() {
    uint64_t ret;
    __asm__ ("mov %%cr3, %0":"=r"(ret)::);
    return ret;
}

void print_memory_map() {
    if(memmap_request.response == NULL || \
     memmap_request.response->entry_count < 1) {
        printk("Could not get memory map. Panic!\n");
        done();
    } 
    struct limine_memmap_entry **entries = memmap_request.response->entries;
    int count = memmap_request.response->entry_count;

    uint64_t usable = 0;
    for(int i = 0 ; i < count ; i++) {
        struct limine_memmap_entry *entry = *(entries + i);
        printk("%p\t\t%p\t\t%d\n", entry->base, entry->length, entry->type);
        if(entry->type == 0) {
            usable += entry->length;
        }
    }
    printk("Usable memory: %p\n", usable);
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

    print_memory_map();
    void* PDBR = (uint64_t *) (read_cr3() >> 12);
    printk("PDBR: %p\n", PDBR);
    load_idt();

    //__asm__ volatile ("1: jmp 1b");
    int foo = *((uint8_t *) 0);
    printk("FOO: %d\n", foo);

    //printk("PML4: %p\n", * (uint64_t *) PDBR + );

    // We're done, just hang...
    done();
}
