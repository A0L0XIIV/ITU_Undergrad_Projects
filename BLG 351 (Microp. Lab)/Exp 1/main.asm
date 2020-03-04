;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
SetupP1		bis.b	#0FFh,&P1DIR			;P1's all pins are output
			bic.b	#0FFh,&P1OUT			;Clearing all bits of outputs P1
			xor.b	#080h,&P1OUT			;Toggle P1.7

L1			clrc
			rrc.b 	&P1OUT
			jc		CLR1
			jmp 	Wait1

Wait1		mov.w	#050000,R15				;Delay to R15
L3			dec.w	R15						;Decrement R15
			jnz		L3						;Delay over?
			jmp 	L1						;

L2
			clrc
			rlc.b	&P1OUT
			jc		CLR2
			jmp		Wait2

CLR1		rlc.b	&P1OUT
			clrc
			jmp		L2
CLR2		rrc.b	&P1OUT
			clrc
			jmp		L1

Wait2		mov.w	#050000,R14				;Delay to R15
L4			dec.w	R14						;Decrement R15
			jnz		L4						;Delay over?
			jmp 	L2						;

;-------------------------------------------------------------------------------



;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
