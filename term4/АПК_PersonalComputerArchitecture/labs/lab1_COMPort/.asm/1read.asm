.model tiny

org 100h   

.data
    errormsg db "Error occured",0Dh,0Ah,'$'        
.code
       
    mov ah,0        ;initializing   
    mov al,11100011b;9600/8n1   
    mov dx,1        ;com1   
    int 14h

    mov dx,1
    mov ah,2
    int 14h
    test ah,80h
    jnz SerialError
    ret
        
SerialError:
    mov ah,9h
    lea dx,errormsg
    int 21h
    ret
    
    ret
end