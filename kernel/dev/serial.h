#define COM1_PORT 0x3f8

#define COM1_RECEIVE_BUFFER         (COM1_PORT + 0)
#define COM1_TRANSMIT_BUFFER        (COM1_PORT + 0)
#define COM1_INTERRUPT_ENABLE       (COM1_PORT + 1)
#define COM1_INTERRUPT_ID           (COM1_PORT + 2)
#define COM1_FIFO_CONTROL           (COM1_PORT + 2)
#define COM1_LINE_CONTROL           (COM1_PORT + 3)
#define COM1_MODEM_CONTROL          (COM1_PORT + 4)
#define COM1_LINE_STATUS            (COM1_PORT + 5)
#define COM1_MODEM_STATUS           (COM1_PORT + 6)
#define COM1_SCRATCH_REGISTER       (COM1_PORT + 7)

#define COM1_LSB_DIVISOR            (COM1_PORT + 0)
#define COM1_MSB_DIVISOR            (COM1_PORT + 1)

bool init_com1_port();