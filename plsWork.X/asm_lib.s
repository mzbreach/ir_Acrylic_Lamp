.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we will need a .global statement to make available ASM
; functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.



.global _write_0, _write_1, _write_0i, _write_1i, _wait_100us, _wait_1ms, _write_0_p2, _write_1_p2, _write_0_p3, _write_1_p3
_write_0:
    inc LATA
    repeat #4
    nop 
    clr LATA
    repeat #9
    nop
    return
    
_write_1:
    inc LATA
    repeat #11
    nop
    clr LATA
    repeat #2
    nop
    return
    
_write_0_p2:
    mov #2, w0
    mov w0, LATA
    repeat #4
    nop 
    clr LATA
    repeat #9
    nop
    return

_write_1_p2:
    mov #2, w0
    mov w0, LATA
    repeat #11
    nop
    clr LATA
    repeat #2
    nop
    return
    
_write_0_p3:
    mov #16, w0
    mov w0, LATA
    repeat #4
    nop 
    clr LATA
    repeat #9
    nop
    return
    
 _write_1_p3:
    mov #16, w0
    mov w0, LATA
    repeat #11
    nop
    clr LATA
    repeat #2
    nop
    return

_write_0i:
    inc LATA
    repeat #4
    nop 
    clr LATA
    repeat #9
    nop
    return

_write_1i:
    inc LATA
    repeat #11
    nop
    clr LATA
    nop
    return
    
_wait_100us:
    repeat #797
    nop
    return

_wait_1ms:
    repeat #15930
    nop
    return  
