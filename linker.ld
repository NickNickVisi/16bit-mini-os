ENTRY(start)
OUTPUT_FORMAT(binary)

SECTIONS
{
    . = 0x7C00;

    .text :
    {
        boot.o(.text)
        *(.text)
        *(.data)
        *(.rodata)
    }
    . = 0x7C00 + 510;

    .sig :
    {
        SHORT(0xAA55)
    }
}