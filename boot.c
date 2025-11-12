char buffer[32];

void print_char(char c) {
    asm volatile (
        "mov $0x0E, %%ah\n\t" 
        "mov %0, %%al\n\t"
        "int $0x10"
        :
        : "r" (c)
        : "ah", "al"
    );
}

void read_char(char *c) {
    asm volatile (
        "mov $0x00, %%ah\n\t"
        "int $0x16\n\t"
        "mov %%al, %0"
        : "=r" (*c)
        :
        : "ah", "al"
    );
}

void read_string(void) {
    char c;
    unsigned short i = 0;

    while (i < 31) {
        read_char(&c);

        if (c == '\r') {
            break;
        } else if (c == 0x08) {
            if (i > 0) {
                i--;
                print_char(0x08);
                print_char(' ');
                print_char(0x08);
            }
        } else {
            print_char(c);
            buffer[i++] = c;
        }
    }
    buffer[i] = '\0';
    print_char('\n');
    print_char('\r');
    
}

void main_c(void) {
    while (1) {
        print_char('>');
        read_string();
    }
}