org 100h

jmp start

size equ 5h
mas db size dup (?)
 
 
get_symb_echo macro
    mov ah, 1h
    int 21h
endm

get_symb_noecho macro
    mov ah, 7h 
    int 21h
endm

print_symb macro symb
    mov dl, symb  
    mov ah, 06h
    int 21h    
endm

start:
    mov cx, 0
    init:
        ;get_symb_echo
        get_symb_noecho
        
        ;mov bx, offset mas
        lea bx, mas
        
        add bx, cx
        mov [bx], al 
        inc cx
        cmp cx, size
        jne init 
    
    print_symb 0Ah
    print_symb 0Dh
    
    output:
        ;mov bx, offset mas 
        lea bx, mas
        
        mov ax, size
        sub al, cl
        add bx, ax
        ;mov dx, [bx]
        ;mov ah, 06h
        ;int 21h 
        print_symb [bx]
        loop output
ret