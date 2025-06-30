#include "chaos-core.h"
#include "serial.h"



bool init_com1_port()
{
    // Disable interrupts
    outb(COM1_INTERRUPT_ENABLE, 0x00);

    // Set DLAB
    outb(COM1_LINE_CONTROL, 1 << 7);

    // Set baud rate to 38400 (divisor 3)
    outb(COM1_LSB_DIVISOR, 0x03); // LSB of divisor
    outb(COM1_MSB_DIVISOR, 0x00); // MSB of divisor

    // Set 8 data bits, no parity, 1 stop bit
    outb(COM1_LINE_CONTROL, 0x03);

    // Enable FIFO, clear them, and set trigger level to 14 bytes
    outb(COM1_FIFO_CONTROL, 0xC7);

    outb(COM1_MODEM_CONTROL, 0x0B); 

    // Set to loopback mode for testing
    outb(COM1_MODEM_CONTROL, 0x1E);

    outb(COM1_PORT, 0xfe);

    if(inb(COM1_PORT) != 0xfe) {
        // If we cannot read back the value, initialization failed
        return false;
    }

    // Clear the loopback mode
    outb(COM1_MODEM_CONTROL, 0x0B);
    return true;
}
