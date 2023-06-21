ENTRY (_entry)

SECTIONS
{
  . = 0x80000000;
  .text : { *(.text) }
  
  . = ALIGN(0x1000);
  PROVIDE(etext = .);

  .data : { *(.data) }
  .bss : { *(.bss) }

  . = ALIGN(0x1000);
  PROVIDE (end = .);
}