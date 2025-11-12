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

void print_string(const char *s) {
    while (*s) {
        if (*s == '\n')
            print_char('\r');
        print_char(*s);
        s++;
    }
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

void read_string(char *buffer) {
    unsigned short i = 0;
    char c;
    read_char(&c);
    print_char(c);
    
    while (c != '\r') {
        buffer[i++] = c;
        read_char(&c);
        print_char(c);
        if (i >= 64)
            break;
    }
    print_char('\n');
    print_char('\r');
}

void main_c(void) {
    char buffer[64];

    print_string("Loaded\n");
    while (1) {
        read_string(buffer);
    }
}