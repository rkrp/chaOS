#include "chaos-core.h"
#include "printk.h"
#include "idt.h"
#include "test.h"
#include "limine.h"
#include "dev/serial.h"

int DATAADDR = 0x1ab;

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
        
        if(entry->type == 0) {
            printk("%p\t\t%p\t\t%d\n", entry->base, entry->length, entry->type);
            usable += entry->length;
        }
    }
    printk("Usable memory: %d MiB\n", usable/1024/1024);
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
    
    if(init_com1_port()) {
        printk("COM1 port initialized successfully.\n");
    } else {
        printk("COM1 port initialization failed.\n");
    }

    printk("Kernel loaded at %p\n", &_start);

    print_memory_map();
    void* PDBR = (uint64_t *) (read_cr3() & 0xFFFFFFFFFFFFF000);
    printk("PML4: %p\n", PDBR);
    PDBR = (uint64_t *) ((uint64_t) PDBR + 0x1000);
    printk("PDBR: %p\n", PDBR);
    load_idt();

    printk("TEXT_ADDR : %p\n", &_start);
    printk("DATA_ADDR : %p\n", &PDBR);
    printk("STACK_ADDR: %p\n", &DATAADDR);

    //__asm__ volatile ("1: jmp 1b");
    int foo = *((uint8_t *) 0);
    printk("FOO: %d\n", foo);

    //printk("PML4: %p\n", * (uint64_t *) PDBR + );

    // We're done, just hang...
    done();
}
