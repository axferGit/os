ENTRY (_entry)

SECTIONS
{
  . = 0x80000000;
  .text : { *(.text) }
  . = 0x81000000;
  .data : { *(.data) }
  . = 0x82000000;
  .bss : { *(.bss) }
}