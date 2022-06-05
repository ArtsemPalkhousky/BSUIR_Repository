.model tiny
.code
org 100h

jmp start

size equ 10h
str db size dup (?)
symb db ?
 
get_symb_echo macro
    mov ah, 1h
    int 21h
endm
 
get_str macro str
    lea dx, str
    mov offset str, size
    mov ah, 0Ah
    int 21h
endm

print_symb macro symb
    mov dl, symb  
    mov ah, 06h
    int 21h    
endm

print_str macro str
    lea dx, str  
    mov ah, 09h
    int 21h    
endm

start:
    lea dx, str
    mov offset str, size
    mov ah, 0Ah
    int 21h
    ;get_str str 
    
    print_symb 0Ah
    print_symb 0Dh
        
    lea bx, str
    inc bx
    output:
        inc bx
        mov dx, [bx]
        print_symb dl
        cmp dl, 0Dh
        jne output
        
    print_symb 0Ah
    print_symb 0Dh
    xor ax, ax   
    get_symb_echo
    mov symb, al
    mov bl, al
     
    print_symb 0Ah
    print_symb 0Dh
    
    mov al, bl
    lea di, str 
    inc di
    find:
        inc di
        mov bx, [di]
        cmp bl, al
        jne find
    
    mov bx, di
    output1:
        inc bx
        mov dx, [bx]
        print_symb dl
        cmp dl, 0Dh
        jne output1
ret  

end start