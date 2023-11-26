data segment
    str1 db 'ABDCAADEFG$'
    substr db 'DEF$' 
    sublen equ $-substr
    msg1 db 10,13,'Substring found at : $' 
    msg2 db 10,13,'Substring not found$'
data ends


ASSUME CS:code,DS:data,ES:extra 

display MACRO MSG
    MOV AH,9
    LEA DX,MSG
    INT 21H
ENDM

code segment   
start:
    mov ax,data
    mov ds,ax  
    mov es,ax
    lea si,str1
reset:
    lea di,substr
    
find_first:
    mov al,[si]
    cmp al,'$'
    je notfound 
    cmp al,[di]
    je check_string
    inc si
    jmp find_first

check_string: 
    inc si
    inc di
    mov al,[di]
    mov bl,[si]
    cmp al,bl
    je check_string
    cmp al,'$'
    je found
    jne reset 
    
found:
    display msg1
    mov dx,si
    sub dx,sublen
    add dx,31h
    mov ah,2
    int 21h
    jmp finish   
    
notfound:
    display msg2 
    
finish:
    mov ah,4ch
    int 21h
      
code ends  
end start