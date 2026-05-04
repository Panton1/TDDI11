		SECTION	.data
		EXTERN	inbound_queue	; (defined in main.C)
data		DB	0		; put rcvd byte here

		SECTION	.text
		ALIGN	16
		BITS	32

BASE_PORT	EQU	3F8h		; we have this in our lab

LSR_PORT	EQU	BASE_PORT+5
RBR_PORT	EQU	BASE_PORT
THR_PORT	EQU	BASE_PORT

; ---------------------------------------------------------------------
; void SerialPut(char ch)
; ---------------------------------------------------------------------
; This function uses programmed waiting loop I/O
; to output the ASCII character 'ch' to the UART.

		GLOBAL	SerialPut

SerialPut:

end:
		mov dx,LSR_PORT
		in al,dx
		SHR al,5
		and al,1
		Jz end

		mov dx, THR_PORT
		mov al,[esp+4]	
		out dx, al
ret
; 
; void interrupt SerialISR(void)
; ---------------------------------------------------------------------
; This is an Interrupt Service Routine (ISR) for
; serial receive interrupts.  Characters received
; are placed in a queue by calling Enqueue(char).

		GLOBAL	SerialISR
		EXTERN	QueueInsert	; (provided by LIBPC)

SerialISR:	STI             	; Enable (higher-priority) IRQs 
				; (1) Preserve all registers
                pusha

; (2) Get character from UART
		mov dx,LSR_PORT
		in al,dx
		and al,1
		Jz _Eoi

		mov dx, RBR_PORT
		in al, dx
		mov [data],al ; nått åt det hålet??

	
		MOV edx, [inbound_queue]
		push data
		push edx	; 
		CALL	QueueInsert
        	ADD	ESP,8
		; <your code here>	; (3) Put character into queue 
		; <your code here>	; Param #2: address of data
		; <your code here>	; Param #1: address of queue

		

	
_Eoi:		; <your code here>	; (4) Enable lower priority interrupts

	
		mov al,0x20
		out 0x20,al
        	popa
iret
