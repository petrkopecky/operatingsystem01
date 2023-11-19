/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
#include "../drivers/display.h"
#include "util.h"

void print() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
    char* video_memory2 = (char*) 0xb8002;
    *video_memory2 = 'X';
}

void main() {
    clear_screen();
    print_string("Installing interrupt service routines (ISRs).\n");
    isr_install();
    
    print_string("Enabling external interrupts.\n");
    asm volatile("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

}

void execute_command(char *input) {
    if (compare_string(input, "EXIT") == 0) {
        print_string("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    print_string("Unknown command: ");
    print_string(input);
    print_string("\n> ");
}
