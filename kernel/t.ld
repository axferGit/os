# ENTRY (_entry);
# Useless for qemu

SECTIONS
{
  . = 0x80000000;
  .text ALIGN(0x1000) : { 
    EXCLUDE_FILE (user/userproc.o user/userlib.o) * (.text)
    * (.kernelvec)
    . = ALIGN(0x1000);
    PROVIDE(trampoline = .);
    *(.trampoline)
  }
  . = ALIGN(0x1000);
  PROVIDE(etext = .);
  

  .rodata ALIGN(0x1000) : { EXCLUDE_FILE (user/userproc.o user/userlib.o) * (.rodata)}
  . = ALIGN(0x1000);
  PROVIDE(erodata = .);
  
  .data : { EXCLUDE_FILE (user/userproc.o user/userlib.o) * (.data) }
  .bss : { EXCLUDE_FILE (user/userproc.o user/userlib.o) * (.bss) }
  . = ALIGN(0x1000);
  PROVIDE(edata = .);

  .user_text ALIGN(0x1000) : {user/userproc.o(.text) user/userlib.o(.text)}
  . = ALIGN(0x1000);
  PROVIDE(euser_text = .);

  .user_data ALIGN(0x1000) : {user/userproc.o(.data)}
  . = ALIGN(0x1000);
  PROVIDE(euser_data = .);

  .user_rodata ALIGN(0x1000) : {user/userproc.o(.rodata.str1.8)}
  . = ALIGN(0x1000);
  PROVIDE(euser_rodata = .);

  .user_bss ALIGN(0x1000) : {user/userproc.o(.bss)}
  . = ALIGN(0x1000);
  PROVIDE(euser_bss = .);

  PROVIDE (end = .);
}