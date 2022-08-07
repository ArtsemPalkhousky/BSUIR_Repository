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
        Pads    db      10 dup(' ')     ;пробелы дл€ выравнивни€ выводимых чисел
        RPad    equ     7               ;выравнивание чисел вправо на 7 позиций
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
 
; преобразует число из регистра AX в строку
; входные данные:
; ax - число дл€ отображени€
; ds:dx - адрес дл€ результирующей строки Pascal типа
Int16ToStr      proc
        push    ax
        push    bx
        push    cx
        push    dx
        push    di
        push    si
 
        mov     si,     dx
        mov     [si],   byte ptr 0      ;текуща€ длина строки равна 0
 
        mov     cx, 10
        xor     di, di          ; di - кол. цифр в числе
 
        ; если число в ax отрицательное, то
        ;1) увеличить длину строки на 1
        ;2) первый символ в строке '-'
        ;3) сделать ax положительным
        or      ax, ax
        jns     @@Conv
        inc     byte ptr [si]
        mov     [si+1], byte ptr '-'
 
        neg     ax
 
@@Conv:
        xor     dx, dx
        div     cx              ; dl = num mod 10
        add     dl, '0'         ; перевод в символьный формат
        inc     di
        push    dx              ; складываем в стек
        or      ax, ax
        jnz     @@Conv
        ; выводим из стека в строку
        mov     ax,     0
        mov     al,     [si]    ;в €чейку с длиной записываем длину строки
        add     [si],   di      ;с учЄтом возможного символа знака
        inc     si              ;устанавливаем указатель на первую свободную €чейку
        add     si,     ax
@@Show:
        pop     dx              ; dl = очередной символ
        mov     [si],   dl
        inc     si
        dec     di              ; повтор€ем пока di<>0
        jnz     @@Show
 
        pop     si
        pop     di
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
Int16ToStr      endp
 
; Ќа входе
;m     - количество строк
;n     - количество столбцов
;ds:dx - адрес матрицы слов
ShowMatrix PROC
        push    ax
        push    bx
        push    cx
        push    dx
        push    si
        push    di
 
        mov     si, 0  ; строка
        mov     di, 0  ; столбец
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
        ;преобразование числа в строку
        lea     dx, String
        call    Int16ToStr
        ;вывод выравнивающих пробелов
        mov     cl, RPad
        sub     cl, [String]
        mov     ch, 0
        lea     si, Pads
        call    ShowSubStr
        ;вывод строки с числом
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
 
;процедура вывода подстроки
;на входе:
;  ds:si - адрес первого символа подстроки
;  cx    - длина выводимой подсторки
ShowSubStr      proc
        push    ax
        push    bx
        push    cx
        push    dx
        mov     ah,     40h     ;вывод в файл
        mov     bx,     1       ;файл - консоль
        mov     cx,     cx      ;количество символов
        mov     dx,     si      ;адрес первого символа
        int     21h
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
ShowSubStr      endp
 
end     main