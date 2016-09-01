#include "msp430x16x.h" 
#define   SPinit	0x24FF
 
            ORG 0xFF00
texto       DB "Funciona!!"     ;Se inicializa el string

main        ORG	0x2500				; Dirección de inicio del programa
;-------------------------------------------------------------------------------
RESET	    MOV	#SPinit,SP      	     ; Inicio del Stack
            MOV.W #WDTPW+WDTHOLD,&WDTCTL ; Stop watchdog timer
P1Setup     bis.b #0x010,&P1DIR	; P1.4 output
            bic.b #0x010,&P1OUT  ; Clear Bit
            
            MOV #texto, R10     ; R10 almacena la dirección del array
            push R10            ; se reespalda la direccion

loop0       MOV.b @R10+, R9     ; R9 <- nuevo char
            CMP #0, R9          ; R9 es NULL?
            JEQ break0          ; Si es null se acabó el string
            MOV R9, R12         ; R12 será el argumento de la funcion
            CALL #ContadorBits   ; R12 es la salida (return(c))
            CMP #0x04, R12       ; Condicion para el pin en alto
            JGE setPin
            
clearPin    bic.b #010h,&P1OUT  ; Clear Bit
            JMP loop0
            
setPin      bis.b #010h,&P1OUT  ; Set Bit
            JMP loop0
         
break0      POP R10             ; Se recupera la direccion del texto
            JMP EXIT            ; Final
;-------------------------------------------------------------------------------
ContadorBits:
            
            PUSH R12        ; Se reespalda el char
            CLR R12         ; c <- R12 <- 0
            
loop1       ; v = v & (v-1), v <- R9
            MOV R9, R13     ; R13 auxiliar
            DEC R13         ; v-1
            AND R13, R9     ; v = v & (v-1)
            ;c = c + 1
            INC R12   
            ; v=0?
            CMP #0, R9
            JEQ break1
            JMP loop1       ;sigue el loop
                
break1      POP R9          ; Se recupera el char en R9
            RET
;-------------------------------------------------------------------------------
EXIT        JMP EXIT
;------------------------------------------------------------------------------ 
; Vector de interrupción asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
