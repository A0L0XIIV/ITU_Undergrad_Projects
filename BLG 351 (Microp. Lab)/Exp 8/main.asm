
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
;-------------------------------------------------------------------------------

			clr.b &P2SEL
			clr.b &P2SEL2
Setup   	mov.b #11111111b,&P1DIR
			mov.b #11111111b,&P2DIR

			call #Delay
;mov.b #10000000b, &P2OUT
			call #initLCD

			mov.w #string, r11

printSCR
upline		mov.w #8000h, R5
jmp1		bit.w R5, &lineA
			jz shift
			mov.b #0FCh, r10
			call #sendDATA
			clrc
			rrc.w R5
			jmp jmp1

dwline		call #sendCMD
			mov.w #8000h, R5
jmp2		bit.w R5, &lineB
			jz shift1
			mov.b #0FCh, r10
			call #sendDATA
			clrc
			rrc.w R5
			jmp jmp2
player		mov.b #0F7h, r10
			call #sendDATA
			jmp	finish
shift		clrc
			rrc.w R5
			mov.b #020h, r10
			call #sendDATA
			cmp #0001h, R5
			jz player
			cmp #0000h, R5
			jz dwline
			jmp jmp1

shift1		clrc
			rrc.w R5
			mov.b #020h, r10
			call #sendDATA
			cmp #0001h, R5
			jz player
			jmp jmp2

triggerEN 	mov.b #01000000b, &P2OUT
			mov.b #00000000b, &P2OUT
			call #Delay
			ret

triggerEEN	mov.b #11000000b, &P2OUT
			mov.b #10000000b, &P2OUT
			call #Delay
			ret

Delay 		mov.w #02h,R14 ; Delay to R14
L2 			mov.w #00500h,R15
L1 			dec.w R15 ; Decrement R15
			jnz L1
			dec.w R14
			jnz L2
			ret

sendCMD 	mov.b #00000000b, &P2OUT
			mov.b #0c0h, r10
			mov.b #0c0h, &P1OUT
			call #triggerEN
			rla.b r10
			rla.b r10
			rla.b r10
			rla.b r10
			mov.b r10, &P1OUT
			call #triggerEN
			ret

sendDATA	mov.b #10000000b, &P2OUT
			mov.b r10, &P1OUT
			call #triggerEEN
			rlc.b r10
			rlc.b r10
			rlc.b r10
			rlc.b r10
			mov.b r10, &P1OUT
			call #triggerEEN
			ret

finish 		jmp finish
initLCD 	mov.b #00110000b, &P1OUT
			call #triggerEN

			mov.b #00110000b, &P1OUT
			call #triggerEN

			mov.b #00110000b, &P1OUT
			call #triggerEN

			;4
			mov.b #00100000b, &P1OUT
			call #triggerEN


			;5 FUNCTION NF
			mov.b #00100000b, &P1OUT
			call #triggerEN
			;6
			mov.b #10000000b, &P1OUT ;NF**
			call #triggerEN

			mov.b #00000000b, &P1OUT
			call #triggerEN
			mov.b #10000000b, &P1OUT
			call #triggerEN

			mov.b #00000000b, &P1OUT
			call #triggerEN
			mov.b #00010000b, &P1OUT
			call #triggerEN

			mov.b #00000000b, &P1OUT
			call #triggerEN

			mov.b #01100000b, &P1OUT ;I/D S
			call #triggerEN


			;init end
			mov.b #00000000b, &P1OUT
			call #triggerEN

			mov.b #11100000b, &P1OUT
			call #triggerEN
			ret


			.data
string .byte 0FCh,0Dh,0F7h,00h
			.data
string1 .byte 020h
;		.data
;string .byte " Game " ,0Dh ," Over !!! " ,00h
tpos .byte 00h ; 0 represents the bottom line , 1 rep the upper line
lineA .word 1802h ; obstacle bit -map of the upper
;line
lineB .word 8010h
;timerC .byte 00h

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
            

