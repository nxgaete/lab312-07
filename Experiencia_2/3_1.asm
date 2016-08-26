#include "msp430x16x.h" 
#define		SPinit	0x24FF			// Ubicación en la RAM
#define		op1	R15					// ¿qué se define? dónde?
#define		op2	R14					// ¿qué se define? dónde?

#define		i	R10			// se define i en r10

main
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Dirección de inicio del programa
;-------------------------------------------------------------------------------
RESET	        MOV	#SPinit,SP      	; Inicio del Stack
SetupP1			bis.b #001h,&P1DIR	; P1.0 output
				bic.b #001h,&P1OUT  ; Clear Bit
                MOV	#0xFFFF,op1 		;MOV	#0x02,op1
                MOV	#0x01,op2
		CLR	i
                CALL	#OPERACION		; Se realiza operación. ¿Dónde queda el resultado? en R15 
                BR      #EXIT			; Reemplace toda la instrucción por RET. ¿Qué ocurre? muere
;-------------------------------------------------------------------------------
OPERACION       
                ADD	op2,op1         ; ¿Qué operacion se realiza? un add sobre el segundo registro dado
		xor.b   #001h,&P1OUT
		INC	i
		CMP	#0x05 , i
		JL	OPERACION
                RET
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ; ¿Qué realiza esta instrucción?
;------------------------------------------------------------------------------ 
; Vector de interrupción asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 
