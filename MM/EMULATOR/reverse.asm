data segment
    msg db 10,13,'Enter string to reverse: $'  
    msg2 db 10,13,'Reverse String: $'
    str db 100 dup($)
    rev db 100 dup($)
data ends

            
ASSUME CS:code,DS:data 

display macro msg
    lea dx,msg
    mov ah,09h
    int 21h
endm

read macro
    mov ah,01h
    int 21h
endm

code segment  
start:     
    mov ax,data
    mov ds,ax
    mov di,offset rev
    add di,100;
    mov [di],'$'
    dec di 
    display msg
    read 
    
next:      
    mov [di],al
    dec di
    read
    cmp al,0DH
    jne next 
    
    inc di
    display msg2
    display di
    mov ah,4ch
    int 21h
code ends
end start
    
    