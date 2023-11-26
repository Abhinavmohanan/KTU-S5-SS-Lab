data segment
    msg2 db 10,13,'number is prime$'
    msg3 db 10,13,'not prime$'     
    number equ 0Ah 
data ends
    
display macro msg
    mov ah,09h
    lea dx,msg
    int 21h
endm   

code segment            
    assume cs:code ds:data
    start:
        mov ax,data
        mov ds,ax
        mov bl,02h
        mov al,number   
        mov ah,0
        div bl
        mov cl,al
        mov bl,01h
    next:
        inc bl
        mov al,number 
        mov ah,0
        div bl
        cmp ah,00h
        jz notprime
        loop next

    prime:
        display msg2
        jmp xx

    notprime:
        display msg3
        jmp xx
    xx:
        mov ah,4ch
        int 21h
 code ends
 end start
