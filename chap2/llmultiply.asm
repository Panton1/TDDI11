;
;  Test cases. All numbers are in hex.
;
;      111122223333 *     555566667777 =          5B061D958BF0ECA7C0481B5
;  3456FEDCAAAA1000 * EDBA00112233FF01 = 309A912AF7188C57E62072DD409A1000
;  FFFFEEEEDDDDCCCC * BBBBAAAA99998888 = BBBB9E2692C5DDDCC28F7531048D2C60
;  FFFFFFFFFFFFFFFF * FFFFFFFFFFFFFFFF = FFFFFFFFFFFFFFFE0000000000000001
;  00000001FFFFFFFF * 00000001FFFFFFFF = 0000000000000003FFFFFFFC00000001
;  FFFEFFFFFFFFFFFF * FFFF0001FFFFFFFF = FFFE0002FFFDFFFE0001FFFE00000001
;

;  void llmultiply(unsigned long long int l1,
;                  unsigned long long int l2,
;                  unsigned char *result);
        
;  a = AH * (2 << 32) + AL
;  b = BH * (2 << 32) + BL
;        
;  a * b = (AH * BH            * (2 << 64)) +
;          (AH * BL + AL * BH) * (2 << 32)  +
;           AL * BL

; For more infromation, see the lab manual!
        	
SECTION .data

	SECTION .text
	ALIGN	16
	BITS	32

	;; To access parameter BH on the stack you do
	;;   MOV EAX, [EBP + 20]
	;; Replace the zero below with the correct value to be able
	;; to write your assembly code a little bit more readable: 
	;;   MOV EAX, [EBP + BH_OFF]
AL_OFF	EQU     8	; Offset from EBP to low  bits of a (AL)
AH_OFF	EQU     12	; Offset from EBP to high bits of a (AH)
BL_OFF	EQU     16	; Offset from EBP to low  bits of b (BL)
BH_OFF	EQU     20	; Offset from EBP to high bits of b (BH)
RES_OFF	EQU     24	; Offset from EBP to result array pointer
	
	;;    ^^^^^ Replace 0 with correct values above
        
	GLOBAL llmultiply

Main:

	
	
	;; register etc innan	
	;; load offset
First4B:	
	MOV ESI, AL_OFF 
	MOV EDI, BL_OFF
	CALL llmultiply		//EDX:EAX   motsvarar nu (AL*BL)
	MOVE EBX, EAX		//  lagrar (AL*BL)L i EBX
	
	
Second4B:
	
	MOV ESI, AL_OFF
	MOV EDI, BL_OFF
	CALL llmultiply
	MOV EBX, EDX  		// EBX motsvar nu (AL*BL)H

	MOV ESI, AL_OFF
	MOV EDI, BH_OFF
	CALL llmultiply
	MOV ECX, EAX		// EXC motsvarar nu (AL*BH)L
	CALL add4B              //ECX:EBX  motsvarar nu  (ECX+EBX)

	CMP //vilka register har vi tillgång till?  (EAX,EDX används till matte,  ECX och EBX till temp lagring, ESP och ESI till pekare)
	
	CALL add4B


	

	
	RET

add4B:
	PUSH EBP
	MOV EBP,ESP

	ADD EBX,ECX  //sätts carry flagga här om båda full?
	ADC ECX
	
	POP EBP
	RET

	
llmultiply:
	PUSH EBP	
	MOV EBP, ESP
	MOV EDC,0
	
	MOV BL,0
	MOV EXC,0
loop1:	

	MOV EDC, [EBP+(ESI+BL)] //räknas BL som bit eller byte

	ADD EDX, EDC
	
	inc BL
	CMP BL,4
	JNE


	
	MOV EAX,[EBP+EDI]
	MUL EAX
	
	POP EBP				; restore EBP reg
	RET				;  return
	
store4B:
	push EBP
	MOV EBP, ESP

	MOV [RESULT+ESI],EAX 

	pop EBP
	RET
	

	
	
	;; EDX motsvarar (AL * BL)H  vill lagra (AL*BH)L + (AH*BL)L + (AL * BL)H  i [RESULT+4]
	;; hur kan ADC användas för summera med carry?
	MOV EAX,[EBP+BH_OFF]
	MUL EAX, EBX		; ECX= AL EAX=BH
	ADC EAX, EDX 		;(AL*BH)L+ (AL * BL)H
	MOV EAX, EBX  		;lagra delresult i EBX


	
	MOV 
	
	ADC EDX,[ 
	

	;; MOV [RESULT+4],



	
	MOV EAX,

	
	;; Put your implementation here


	POP EBP				; restore EBP reg
	RET				;  return
