data segment
    msg2 db 10,13,'number is prime$'
    msg3 db 10,13,'not prime$'     
    number equ 0017h 
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
        mov bx,0002h
        mov AX,number 
        div bx  
        mov cx,ax
        mov bx,0001h
    next: 
        mov dx,0
        mov ax,number
        inc bx
        div bx 
        cmp dx,0
        je notprime
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
