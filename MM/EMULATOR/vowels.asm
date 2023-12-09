data SEGMENT  
    msg1 db 10,13,"Enter String : $"
    msg2 db 10,13,"No. of characters in string : $"
    msg3 db 10,13,"No. of vowels : $" 
    msg4 db "AEIOUaeiou$"
data ENDS


display MACRO MSG
    MOV AH,9
    LEA DX,MSG
    INT 21H
ENDM

printno MACRO num
    mov ah,02h
    mov dl,num
    add dl,48
    int 21h
ENDM

readline MACRO 
    mov ah,01h
    int 21h
ENDM

ASSUME CS:code,DS:data

code SEGMENT
    start: 
        mov ax,data
        mov ds,ax
        mov bl,0h
        mov cl,0h
        display msg1  
    while:
        mov si,offset msg4
        readline
        cmp al,0DH
        je endwhile
        inc bl
        jmp count 
        
        
    count:
        mov ah,[si]
        inc si
        cmp ah,'$'
        je while
        cmp al,[si]
        jne count
        inc cl
        jmp while
        
    endwhile:
        display msg2
        printno bl
        display msg3
        printno cl
    mov ah,4ch
    int 21h  
    
code ENDS
end start