.model tiny
.code
org 100h

start:
    mov ah,0
    mov al,11100011b
    mov dx,0
    int 14h
main_loop:
    mov ah,1
    int 16h
    jz main_loop
    mov ah,8
    int 21h
    test al,al
    jnz send_char
    int 21h
    cmp al,2Dh
    jne send_char
    ret
send_char:
    mov ah,1        
    int 14h
    jmp short main_loop
    
end start    