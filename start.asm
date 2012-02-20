[BITS 32]
[global start]
[extern _kernel_main] ; this is in the c file

start:
  call _kernel_main

  cli  ; stop interrupts
  hlt ; halt the CPU
  
;[global _gdt_flush]
;[extern _gp]
;_gdt_flush:
	;lgdt [_gp]		; Load the GDT with our _gp, which is a special pointer
	;mov ax, 0x10	; 0x0 is the offset in the GDT to our data segment
	;mov ds, ax
	;mov es, ax
	;mov fs, ax
	;mov gs, ax
	;mov ss, ax
	;jmp 0x08:flush2	; 0x08 is the offset to our code segment.
;flush2:
	;ret				; Return to C
	