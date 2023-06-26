ENTRY (_entry);
# Useless for qemu

SECTIONS
{
  . = 0x80000000;
  .text ALIGN(0x1000) : { EXCLUDE_FILE (userproc.o) * (.text) }
  . = ALIGN(0x1000);
  PROVIDE(etext = .);

  .rodata ALIGN(0x1000) : { EXCLUDE_FILE (userproc.o) * (.rodata)}
  . = ALIGN(0x1000);
  PROVIDE(erodata = .);
  
  .data : { EXCLUDE_FILE (userproc.o) * (.data) }
  .bss : { EXCLUDE_FILE (userproc.o) * (.bss) }
  . = ALIGN(0x1000);
  PROVIDE( edata = .);

  .user . : {userproc.o (.text .data .bss .rodata)}
  . = ALIGN(0x1000);
  PROVIDE (end = .);
}