MOV SI,3000H
MOV DI,4000H
MOV AX,[SI]
ADD SI,2
MOV BX,[SI]
CMP AX,BX
jnc notless
XCHG AX,BX
SUB AX,BX
MOV [DI],0001H
jmp end
notless:
SUB AX,BX
MOV [DI],0000H 
end:     
INC DI
MOV [DI],AX
HLT
