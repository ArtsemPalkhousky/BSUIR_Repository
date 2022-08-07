.model tiny
.code
org 100h

start:
    mov ah,0
    mov al,11100011b
    mov dx,0
    int 14h

main_loop:
    mov ah,2
    int 14h
    test ah,ah
    jz main_loop
    int 29h
    jmp main_loop

exit:
    cmp al,'0'
    jne main_loop
    mov ax,4C00h
    int 21h
        
end start    