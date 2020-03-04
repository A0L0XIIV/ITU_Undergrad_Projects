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
Setup	bis.b	#0FFh,&P1DIR
		bis.b	#0FFh,&P2DIR

inLCD	call	#Delay		;1
		mov		#030h,&P1OUT;2
		call	#TriEN
		call	#Delay
		mov		#030h,&P1OUT;3
		call	#TriEN
		call	#Delaym
		;4
		mov		#030h,&P1OUT
		call	#TriEN
		call	#Delaym
		;5
		mov		#020h,&P1OUT
		call	#TriEN
		call	#Delaym
		;6
		mov		#020h,&P1OUT
		mov		#080h,&P1OUT
		call	#TriEN
		call	#Delaym
		;7
		mov		#000h,&P1OUT
		mov		#080h,&P1OUT
		call	#TriEN
		call	#Delaym
		;8
		mov		#000h,&P1OUT
		mov		#010h,&P1OUT
		call	#TriEN
		call	#Delay
		;9
		mov		#000h,&P1OUT
		mov		#060h,&P1OUT
		call	#TriEN
		call	#Delaym
		;11
		mov		#000h,&P1OUT
		mov		#0C0h,&P1OUT
		call	#TriEN
		call	#Delaym
		mov.b	#040h,&P1OUT
		call	#TriEN
		mov.b	#010h,&P1OUT
		call	#TriEN
sCMD	bic.b	#080h,&P2OUT
		mov		#000h,&P1OUT
		call 	#TriEN
		bic.b	#080h,&P2OUT
		mov		#007h,&P1OUT
		call 	#TriEN
sDATA	bis.b	#080h,&P2OUT
		mov		#'a',&P1OUT
		call 	#TriEN
		bis.b	#080h,&P2OUT
		mov		#007h,&P1OUT
		call 	#TriEN
TriEN	bis.b	#040h,&P2OUT
		call 	#Delaym
		bic.b	#040h,&P2OUT
		ret
Delay   mov.w	#19100d, R14 ;more than 100ms delay
Lb2     dec.w	R14
        jnz 	Lb2
        ret


Delaym  mov.w	#20d, R14 ;more than 100us delay
Lb2m    dec.w 	R14
        jnz 	Lb2m
        ret

		.data
string 	.byte	"ITU",0Dh,"COMPUTER SC.",00h
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
            
