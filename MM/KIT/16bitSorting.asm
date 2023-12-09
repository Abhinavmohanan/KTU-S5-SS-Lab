org 0400H
MOV BL,[3000H]
DEC BL
outerloop:
MOV CL,[3000H]
DEC CL  
MOV SI,3001H
innerloop: 
MOV AX,[SI]
ADD SI,2
CMP AX,[SI]
JC  noswap
XCHG AX,[SI]
SUB SI,2
XCHG AX,[SI]
ADD SI,2
noswap:
DEC CL
JNZ innerloop
DEC BL
JNZ outerloop
HLT

      


