                               org 100h
.model tiny
.stack 100h
.data
msgHello    db  "1 - start resident",10,13,"$"
BLACK       equ 00010000b       ;������� ������ - ������ ����� �� ����� ����
GREEN         equ 00010010b       ;������� ������ - ������� ����� �� ����� ����
.code
mov ah,09h
lea dx,msgHello
int 21h
mov ah,07h
int 21h
cmp al,'1'
je  setInterrupts
IRQ0:                           ;���������� IRQ0 - ���������� ���������� �������
    int 50h
    int 8h
    iret 
IRQ1:                           ;���������� IRQ1 - ���������� ����������
    int 50h
    int 09h    
    iret
IRQ2:                           ;���������� IRQ2 - ���������� ��� �������� �����������
    int 50h
    int 0Ah
    iret
IRQ3:                           ;���������� IRQ3 - ���������� COM2
    int 50h
    int 0Bh
    iret
IRQ4:                           ;���������� IRQ4 - ���������� COM1
    int 50h
    int 0Ch
    iret
IRQ5:                           ;���������� IRQ5 - ���������� ����������� �������� �����
    int 50h
    int 0Dh
    iret
IRQ6:                           ;���������� IRQ6 - ���������� ����������� ������-�����
    int 50h
    int 0Eh
    iret
IRQ7:                           ;���������� IRQ7 - ���������� ��������
    int 50h
    int 0Fh
    iret
IRQ8:                           ;���������� IRQ8 - ���������� RTC
    int 50h
    int 70h
    iret
IRQ9:                           ;���������� IRQ9 - ���������� ����������� EGA
    int 50h
    int 71h
    iret
IRQ10:                          ;���������� IRQ10 - ����������������
    int 50h
    int 72h
    iret
IRQ11:                          ;���������� IRQ11 - ���������������
    int 50h
    int 73h
    iret
IRQ12:                          ;���������� IRQ12 - ���������������
    int 50h
    int 74h
    iret
IRQ13:                          ;���������� IRQ13 - ���������� ��������������� ������������
    int 50h
    int 75h
    iret
IRQ14:                          ;���������� IRQ14 - ���������� ����������� �������� �����
    int 50h
    int 76h
    iret
IRQ15:                          ;���������� IRQ15 - ���������������
    int 50h
    int 77h
    iret
DISPLAY:                        ;���������� INT15 - ����� �������� ��������� ����������� ����������
pusha
    push es                     ;����� �����������
    mov ax,0B800h
    mov es,ax                   ;� es
    mov cx,8
    xor di,di
    mov di,0
    xor bx,bx                   ;����� ���������
    bufferOutput:
    mov al,cs:[buffer+bx]
    mov es:[di],al
    inc bx
    inc di
    mov al,BLACK
    mov es:[di],al
    inc di
    loop bufferOutput        
    in al,21h                   ;��������� �������� �������� ����� �������� �����������
    mov cs:[registers+0],al
    in al,0A1h                  ;��������� �������� �������� ����� �������� �����������
    mov cs:[registers+3],al
    mov al,00001011b            ;������� OCW3
                                ;0XXXXXXX - ����
                                ;X00XXXXX - �� �������� ����� ������������
                                ;XXX01XXX - ������� OCW3
                                ;XXXXX0XX - �� ����� ������
                                ;XXXXXX11 - ������� ������� ������������� ����������
    out 20h,al
    in  al,20h
    mov cs:[registers+2],al
    mov al,00001011b            ;������� OCW3                                        
                                ;0XXXXXXX - ����                                     
                                ;X00XXXXX - �� �������� ����� ������������           
                                ;XXX01XXX - ������� OCW3                             
                                ;XXXXX0XX - �� ����� ������                          
                                ;XXXXXX11 - ������� ������� ������������� ����������    
    out 0A0h,al
    in  al,0A0h
    mov cs:[registers+5],al
    mov al,00001010b            ;������� OCW3                                       
                                ;0XXXXXXX - ����                                    
                                ;X00XXXXX - �� �������� ����� ������������          
                                ;XXX01XXX - ������� OCW3                            
                                ;XXXXX0XX - �� ����� ������                         
                                ;XXXXXX11 - ������� ������� �������� �� ����������
    out 20h,al
    in  al,20h
    mov cs:[registers+1],al
    mov al,00001010b            ;������� OCW3                                     
                                ;0XXXXXXX - ����                                  
                                ;X00XXXXX - �� �������� ����� ������������        
                                ;XXX01XXX - ������� OCW3                          
                                ;XXXXX0XX - �� ����� ������                       
                                ;XXXXXX11 - ������� ������� �������� �� ����������
    
    out 0A0h,al
    in  al,0A0h
    mov cs:[registers+4],al
    mov cx,6                    ;���� �� ������ ��������� ����� �����������
    registersOutput:
        mov dx,cx
        mov bx,6
        sub bx,dx
        mov al,cs:[registers+bx];��������� �������� �������� �� ������
        lea bx,cs:[temp]        ;��������� ����� ��� ������
        push cx
        mov cx,8
        btbs_lp:                ;������� ����� � �������� ���
            rol al,1            ;����������� ����� al ����� �� 1 ���
            jc btbs_1           ;���� ���������� ��� = 1, �� �������
            mov cs:[bx],'0'     ;���������� ������� '0' � ������
            jmp btbs_end
        btbs_1:
            mov cs:[bx],'1'     ;���������� ������� '1' � ������
        btbs_end:
            inc bx              ;��������� di
            loop btbs_lp        ;������� �����
        mov cx,8
        xor bx,bx
        registerOutput:         ;���� �� ������ ������
            mov al,cs:[temp+bx]
            mov es:[di],al
            inc di
            inc bx
            mov al,GREEN
            mov es:[di],al
            inc di
        loop registerOutput
        mov al, ' '              ;�������� ������ ����� ������
        mov es:[di],al
        inc di      
        mov al,GREEN
        mov es:[di],al
        inc di
        
        pop cx
    loop registersOutput
    pop es
    popa
    iret
    buffer  db  "IRQ:    "      ;����� ��� ���������
    temp    db  8  dup ('6')    ;����� ��� ��������� � ������ �������� �������� 
    registers db 6 dup (?)      ;������ ���������
setInterrupts:                  ;��������� ��������� ������������ ���������� ���������� � ����������������� �����������
    mov ah,0h                   ;��������� �����������
    mov al,3h                   ;�������, 16 ������, 80*25 ��������,
    int 10h                     ;���������� ����� �����
    push ds
    push cs
    pop  ds
    mov ax,2560h                ;������������� �������� ���������� 60h-6Fh
    mov dx, offset IRQ0
    int 21h
    mov ax,2561h
    mov dx, offset IRQ1
    int 21h
    mov ax,2562h
    mov dx, offset IRQ2
    int 21h
    mov ax,2563h
    mov dx, offset IRQ3
    int 21h
    mov ax,2564h
    mov dx, offset IRQ4
    int 21h
    mov ax,2565h
    mov dx, offset IRQ5
    int 21h
    mov ax,2566h
    mov dx, offset IRQ6
    int 21h
    mov ax,2567h
    mov dx, offset IRQ7
    int 21h
    mov ax,2568h
    mov dx, offset IRQ8
    int 21h
    mov ax,2569h
    mov dx, offset IRQ9
    int 21h
    mov ax,256Ah
    mov dx, offset IRQ10
    int 21h
    mov ax,256Bh
    mov dx, offset IRQ11
    int 21h
    mov ax,256Ch
    mov dx, offset IRQ12
    int 21h
    mov ax,256Dh
    mov dx, offset IRQ13
    int 21h
    mov ax,256Eh
    mov dx, offset IRQ14
    int 21h
    mov ax,256Fh
    mov dx, offset IRQ15
    int 21h
    mov ax,2550h
    mov dx, offset DISPLAY
    int 21h
    cli                         ;������ ���������� ����������
        mov al, 11h             ;ICW1 - ������ ������������� ������������
                                ;0001XXXX - ������� ICW1
                                ;XXXX0XXX - ������������ �� �������� �������
                                ;XXXXX1XX - ������ ������� ����������
                                ;XXXXXX0X - ��������� ����������� ������������
                                ;XXXXXXX0 - ����� ������� ICW4
        out 20h, al             ;������������� �������� �����������
        out 0A0h, al            ;������������� �������� �����������
        mov al, 60h             ;ICW2 - ������� ������ ������� ���������� �������� �����������
        out 21h, al
        mov al, 68h             ;ICW2 - ������� ������ ������� ���������� �������� �����������
        out 0A1h, al
        mov al, 04h             ;ICW3 - ������� ���������� ��������� � 3 �����
        out 21h, al       
        mov al, 02h             ;ICW3 - ������� ���������� ��������� � 3 �����
        out 0A1h, al      
        mov al, 11h             ;ICW4 - ����� ����������� ������ ����������� ��� �������� �����������
        out 21h, al        
        mov al,01h              ;ICW4 - ����� ������� ������ ����������� ��� �������� �����������
        out 0A1h, al       
    sti
lea dx,setInterrupts            ;�������� ��������� �����������
int 27h
ret
ends code