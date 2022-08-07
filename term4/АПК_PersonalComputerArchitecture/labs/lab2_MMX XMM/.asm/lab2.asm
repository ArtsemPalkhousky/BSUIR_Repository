.model small
 
.stack 100h
 
.data
        CrLf    db      0Dh, 0Ah, '$'
        M       equ     4
        N       equ     7
 
        A       dw      -100, 123, 777, -561, 891, -222, -99
                dw       147, 564, -85, -753, 243,  478, 557
                dw        72,  64,  11,   88, -49,   69,  57
                dw       951, -22, -33, -210,  79,  111, 232
        B       dw         1,   2,   3,    5,   4,    7,   9
                dw        -4,  -8, 100, -645, 555, -222,  88
                dw        36,  36, -36,  366, 362,  542,  36
                dw       -77, 444, 333, -111, -54,  444, 361
        C       dw      M*N dup(?)
 
        String  db      256 dup(?)
        Pads    db      10 dup(' ')     ;������� ��� ����������� ��������� �����
        RPad    equ     7               ;������������ ����� ������ �� 7 �������
.code
 
main    proc
        mov     ax,     @data
        mov     ds,     ax
 
        lea     si,     A
        lea     di,     B
        lea     bx,     C
        mov     cx,     M*N
ForIJ:
        mov     ax,     [si]
        sub     ax,     [di]
        mov     [bx],   ax
        add     si,     2
        add     di,     2
        add     bx,     2
        loop    ForIJ
 
        lea     dx,     C
        call    ShowMatrix
 
        mov     ax,     4C00h
        int     21h
main    endp
 
; ����������� ����� �� �������� AX � ������
; ������� ������:
; ax - ����� ��� �����������
; ds:dx - ����� ��� �������������� ������ Pascal ����
Int16ToStr      proc
        push    ax
        push    bx
        push    cx
        push    dx
        push    di
        push    si
 
        mov     si,     dx
        mov     [si],   byte ptr 0      ;������� ����� ������ ����� 0
 
        mov     cx, 10
        xor     di, di          ; di - ���. ���� � �����
 
        ; ���� ����� � ax �������������, ��
        ;1) ��������� ����� ������ �� 1
        ;2) ������ ������ � ������ '-'
        ;3) ������� ax �������������
        or      ax, ax
        jns     @@Conv
        inc     byte ptr [si]
        mov     [si+1], byte ptr '-'
 
        neg     ax
 
@@Conv:
        xor     dx, dx
        div     cx              ; dl = num mod 10
        add     dl, '0'         ; ������� � ���������� ������
        inc     di
        push    dx              ; ���������� � ����
        or      ax, ax
        jnz     @@Conv
        ; ������� �� ����� � ������
        mov     ax,     0
        mov     al,     [si]    ;� ������ � ������ ���������� ����� ������
        add     [si],   di      ;� ������ ���������� ������� �����
        inc     si              ;������������� ��������� �� ������ ��������� ������
        add     si,     ax
@@Show:
        pop     dx              ; dl = ��������� ������
        mov     [si],   dl
        inc     si
        dec     di              ; ��������� ���� di<>0
        jnz     @@Show
 
        pop     si
        pop     di
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
Int16ToStr      endp
 
; �� �����
;m     - ���������� �����
;n     - ���������� ��������
;ds:dx - ����� ������� ����
ShowMatrix PROC
        push    ax
        push    bx
        push    cx
        push    dx
        push    si
        push    di
 
        mov     si, 0  ; ������
        mov     di, 0  ; �������
        mov     cx, dx
 
@@ShowRow:
        mov     dx, 0
        mov     ax, n*2
        mul     si
        mov     bx, ax
        add     bx, cx
 
        mov     ax, [bx+di]
 
        push    si
        push    cx
        ;�������������� ����� � ������
        lea     dx, String
        call    Int16ToStr
        ;����� ������������� ��������
        mov     cl, RPad
        sub     cl, [String]
        mov     ch, 0
        lea     si, Pads
        call    ShowSubStr
        ;����� ������ � ������
        lea     si, String+1
        mov     cl, String
        mov     ch, 0
        call    ShowSubStr
        pop     cx
        pop     si
 
        add     di, 2
 
        cmp     di, n*2
        jb      @@ShowRow
 
        lea     dx, CrLf
        mov     ah, 09h
        int     21h
 
        mov     di, 0
 
        inc     si
 
        cmp     si, m
        jb      @@ShowRow
 
        pop     di
        pop     si
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
ShowMatrix ENDP
 
;��������� ������ ���������
;�� �����:
;  ds:si - ����� ������� ������� ���������
;  cx    - ����� ��������� ���������
ShowSubStr      proc
        push    ax
        push    bx
        push    cx
        push    dx
        mov     ah,     40h     ;����� � ����
        mov     bx,     1       ;���� - �������
        mov     cx,     cx      ;���������� ��������
        mov     dx,     si      ;����� ������� �������
        int     21h
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
ShowSubStr      endp
 
end     main