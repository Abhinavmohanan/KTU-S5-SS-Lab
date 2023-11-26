data segment
    msg db 10,13,'Enter string to continue : $'
    msg2 db 10,13,'String is not palindrome $' 
    msg3 db 10,13,'String is palindrome $'
    str db 50 dup(0)
data ends


ASSUME CS:code,DS:data

code segment   
start:
    mov ax,data
    mov ds,ax
    mov di,offset str
    mov si,offset str
    lea dx,msg  
    mov ah,9
    int 21h 
    mov ah,1
    int 21h 
read:
    mov [di],al
    inc di
    mov ah,1
    int 21h
    cmp al,0DH
    JNE read
    dec di
check:
    mov al,[si]
    mov bl,[di]           
    cmp al,bl
    jne notpalindrome 
    inc si
    dec di
    cmp si,di 
    jl check
palindrome:
    lea dx,msg3
    mov ah,9
    int 21h
    jmp term
notpalindrome:
    lea dx,msg2
    mov ah,9
    int 21h
term:
    mov ah,4ch
    int 21h
code ends  
end start