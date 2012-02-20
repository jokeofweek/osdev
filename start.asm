[BITS 32]
[global start]
[extern _kernel_main] ; this is in the c file

start:
  call _kernel_main

  cli  ; stop interrupts
  hlt ; halt the CPU