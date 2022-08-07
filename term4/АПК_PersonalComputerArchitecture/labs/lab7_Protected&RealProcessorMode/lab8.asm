.386P

descr	struc		; ��������� �����������
    lim	dw 0		    ;������ 
    base_1	dw 0		;������� ����� 
    base_m	db 0		;������� ����� 
    attr_1	db 0		;������� 1 
    attr_2	db 0		;������� 2 
    base_h	db 0		;������� ����� 
descr	ends

gate	struc		; ��������� �����
    offs_1	dw 0		;�������� ������� ����� 
    sel	dw 16		    ;�������� �������� 
    cntr	db 0		;������� 
    dtype	db 8Eh		;������� 
    offs_h	dw 0		;�������� 
gate ends

data 	segment use16
; gdt - ���������� ������� ������������
    gdt_null descr <0, 0, 0, 0, 0, 0>               ;���������� ��������� �������
    gdt_data descr <data_size - 1, 0, 0, 92h, 0, 0> ;���������� �������� ������
    gdt_code descr <code_size - 1, 0, 0, 98h, 0, 0> ;���������� �������� ������
    gdt_stack descr <255,,, 92h,,>                  ;���������� �������� �����
    gdt_screen descr <3999, 8000h, 0Bh, 92h, 0, 0>  ;���������� ��� �������� ��������
    gdt_size = $ - gdt_null

; idt - ������� ������������ ����������
    idt label word
        db 32 dup ( 8 dup (0))
        gate <new_08,,8Eh>	; irq0
        gate <new_09,,8Eh>	; irq1
        idt_size=$-idt

    pdescr	df 0            ;�������������� ���� �� 6 ���� ����������� � gdt
        sym 	db 1
        attr 	db 1Eh
        master	db 0
        slave	db 0
        count	db 0
        time	dw 0
        
    time_msg db 'T', 4Fh, 'i', 4Fh, 'm', 4Fh, 'e', 4Fh, ':', 4Fh, ' ', 4Fh
    time_buffer db  '0', 4Fh, '0', 4Fh, '0', 4Fh, '0', 4Fh, '0', 4Fh
    time_buffer_line_size equ 11
    time_buffer_pos dw 800
    scan_msg db 'S', 4Fh, 'c', 4Fh, 'a', 4Fh, 'n', 4Fh, ':', 4Fh, ' ', 4Fh
    scan_buffer db  '0', 4Fh, '0', 4Fh
    scan_buffer_line_size equ 8
    scan_buffer_pos dw 640
    scancode db 0A9h
    sixteen db 16
    ten	dw 10
    sign dw ?
    videobuffer_line_size db 160
    quit_flag db 0
    num_err_msg db 0Dh,0Ah,"Imput is incorrect. Try again",0Dh,0Ah,'$'
    
    msg db "Return!",0Dh,0Ah,'$'
    data_size = $ - gdt_null
data	ends

text 	segment use16
	assume CS:text, DS:data
textseg	label word
; ������ irq0
new_08	proc			
	inc 	count
	cmp 	count, 20
	jne 	end_irq1
	mov 	count, 0
	dec 	time
	cmp 	time, 0
	jne 	not_quit
	mov 	quit_flag, 1
not_quit:
	push 	offset time_buffer + 8
	call 	puttime
	mov 	cx, time_buffer_line_size 
	mov 	di, time_buffer_pos
	mov 	si, offset time_msg
reder:
	lodsw
	stosw
	loop 	reder
	
end_irq1:
	; eoi
	mov 	al, 20h
	out	20h, al
	db	66h
	iret
new_08	endp

; ���������� irq1
new_09	proc
	in 	al, 60h
	cmp 	al, 01h
	jne 	nqu
	mov 	quit_flag, 1
nqu:	
	mov 	scancode, al
	mov 	di, offset scan_buffer
	call 	putscan
	mov 	cx, 8
	mov 	di, 640
	mov 	si, offset scan_msg
render:
	lodsw
	stosw
	loop 	render
	; eoi
	mov 	al, 20h
	out 	20h, al
	db	66h
	iret
new_09	endp

main 	proc

	xor	eax, eax
	mov	ax, data
	mov 	ds, ax
	
	; ���� �������
	push 	dx
	call 	getnum
	mov 	time, dx
	pop 	dx
	
	; ���-�� � ������
	mov 	al, 00110110b 	;  1  ����� ����� 2 (������������)
	out 	43h, al
	mov 	ax, 59659 	;  20 �� 1193180 / 59659
	out 	40h, al
	shr 	ax, 8
	out 	40h, al

	; ���������� gdt_data
	xor	eax, eax
	mov	ax, data

	shl	eax, 4
	mov	ebp, eax
	mov 	bx, offset gdt_data
	mov 	[bx].base_1, ax
	shr	eax, 16
	mov	[bx].base_m, al

	; ���������� gdt_code
	xor 	eax, eax
	mov	ax, cs
	shl	eax, 4
	mov	bx, offset gdt_code
	mov	[bx].base_1, ax
	shr 	eax, 16
	mov 	[bx].base_m, al
	
	; ���������� gdt_stack
	xor	eax, eax
	mov	ax, ss
	shl	eax, 4
	mov 	bx, offset gdt_stack
	mov 	[bx].base_1, ax
	shr	eax, 16
	mov	[bx].base_m, al

	mov 	dword ptr pdescr+2, ebp		    ; �������������� �������� ��� �������� � gdt
	mov 	word ptr pdescr, gdt_size-1 	; ��������� �� ������ gdt
	lgdt	pdescr				            ; ��������� gdt

	; ������ ��������� ���������� �����������
	cli

	; ��������� ����� ����������??
	in	al, 21h				
	mov	master, al
	in	al, 0A1h
	mov	slave, al
	
    	; ��������������� ���������� �� ������ �������
    	mov	al, 11h				
    	out	20h, al
    	mov	al, 20h				;
    	out	21h, al
    	mov al, 4h				; 
    	out	21h, al
    	mov	al, 1h				; 
    	out	21h, al
    	mov	al, 0FCh			; 
    	out	21h, al
    
    	mov	al, 0FFh			; 
    	out	0A1h, al
	
	; �������� idt
	mov	word ptr pdescr, idt_size-1
	xor	eax, eax
	mov	ax, offset idt
	add	eax, ebp
	mov	dword ptr pdescr+2, eax
	lidt	pdescr

	; ������� ��������������� � ���������� ����� 
	mov 	eax, cr0
	or	eax, 1                   ;������ ����� ������������ � ���������� �����
	mov 	cr0, eax             ;��������� � cr0 ���� 0
	
	; ������� �������� ��������. �������� cs � ip, ������� ������� ������ � ����� ����������� ������
	db 0EAh
	dw offset continue
	dw 16
continue:
	; ��������� ���������� ���������
	;�������� ��������� � ds
	mov 	ax, 8
	mov 	ds, ax
	;�������� ��������� � ss
	mov 	ax, 24
	mov 	ss, ax
	;�������� ��������� � es
	mov 	ax, 32
	mov 	es, ax
	;���������� ��������� ����������� ����������
	sti

	mov	sp, 100h

wait:
	cmp quit_flag, 1
	jne wait
	; ������ �������� ���������� ����������
	cli
	; ��������� ���� ������� ��������� � ������������ � ������������ ��������� ������
	mov	gdt_data.lim, 0FFFFh
	mov	gdt_code.lim, 0FFFFh
	mov	gdt_stack.lim, 0FFFFh
	mov	gdt_screen.lim, 0FFFFh
	push 	ds
	pop	ds
	push	ss
	pop	ss
	push 	es
	pop	es
	; ������� �������� ��������, �������� cs
	db 0EAh
	dw offset go
	dw 16
go:	
	; ������� � �������� �����
	mov	eax, cr0
	and	eax, 0FFFFFFFEh
	mov	cr0, eax
	; ������� �������� ��������
	db	0EAh
	dw	offset return
	dw 	text
return:
    ;��������� ���������� ���������
	mov 	ax, data
	mov	ds, ax
	mov	ax, stk
	mov 	ss, ax
	mov 	sp, 256
		
	; ��������� idt
	mov	ax, 3FFh
	mov	word ptr pdescr, ax
	mov	eax, 0
	mov	dword ptr pdescr+2, eax
	lidt	pdescr

    	; ��������������� ���������� �� ������ �������
    	mov	al, 11h
    	out	20h, al
    	mov	al, 8
    	out	21h, al
    	mov al, 4
    	out	21h, al
    	mov	al, 1
    	out	21h, al
    	mov	al, 0fCh
    	out	21h, al

	;���������� ����������� ����������
	mov	al, master
	out	21h, al
	mov al, slave
	out	0A1h, al
	sti

	mov 	ah, 09h
	mov	dx, offset msg
	int 	21h

	; �����
	mov	ax, 4C00h
	int 	21h
main 	endp


putscan		proc  ; ����� �������� � hex
		pusha
		xor ah, ah
            	mov al, scancode
		div sixteen
	
		mov cx, 2
hex:		cmp al, 10
		jl digit
		sub al, 10
		add al, 'A'
		jmp ins
digit:
		add al, '0'
ins:
		mov [di], al
             	add di, 2
		mov al, ah
		loop hex
		popa
		ret 
putscan		endp


getnum 	proc		; ���� ����� ��� �������

		push ax
		push bx
		push cx

skip_spaces:
		call getchar 
		cmp al, ' '
		je skip_spaces
		cmp al, 0Dh
		je skip_spaces
		cmp al, 08h
		je backspace
		cmp al, '-'
		jne positive_num
		mov sign, -1
		call getchar
		mov dx, 0	
		jmp start_getnum
positive_num:
		mov sign, 1
		mov dx, 0
start_getnum:
		cmp al, 08h
backspace:
		jne digit_check
		push dx
		mov  ah,03h            ;�������� ������� ������� 
       		int  10h           ;  
        	push dx            ; 
        	push ' '
		call putchar
        	pop  dx            ;���������� ������
       		mov  ah,02h        
        	int  10h
		pop dx
		mov ax, dx
		mov dx, 0
		div ten
		mov dx, ax
		cmp dx, 0
		jz skip_spaces
		jmp getsymb
digit_check:
		cmp al, '0'
		jb num_error
		cmp al, '9'
		ja num_error
		push ax
		mov ax, dx
		mul ten
		mov dx, ax
		pop ax
		jo num_error
		mov ah, 0 
		sub ax, '0'
		add dx, ax
		mov ax, dx
		jo num_error
getsymb:
		call getchar 
		cmp al, ' '
		jz end_getnum
		cmp al, 0Dh
		jz end_getnum
		jmp start_getnum

num_error:
		cmp ax, -32768
		je minimal_num
		
		push offset num_err_msg
		call putstr 
		jmp skip_spaces

minimal_num:
		xor ax, ax
		cmp sign, -1
		jne num_error
		mov sign, 1
		jmp getsymb

end_getnum:
		cmp sign, -1
		jne get_stack
		neg dx


get_stack:
		pop cx
		pop bx
		pop ax

		ret

check_min:
		cmp sign, -1
		jne num_error
		mov ax, dx
		imul sign
		mov dx, ax
		sub dx, ten
		jmp get_stack
endp

puttime	proc			;putnum(num)
		push bp
		mov bp, sp
		push ax
		push cx
		push dx
                push di
                mov di, [bp + 4]
                mov ax, time
start_putnum:
		mov dx, 0
		div ten
                add dx, '0'
		mov [di], dl
             
                sub di, 2
		cmp ax, 0
		jnz start_putnum
		mov 	dl, '0'
		mov [di], dl
                pop di
		pop dx
		pop cx
		pop ax

		mov sp, bp
		pop bp
		ret 2
endp

putstr proc				; ����� ������
str equ [bp + 4]

		push bp
		mov bp, sp
		push ax
		push dx
		mov ah, 09h
		mov dx, str
		int 21h
		pop dx
		pop ax

;		mov sp, bp
		pop bp
		ret 2
endp

putchar proc			; ����� �������
symbol equ [bp + 4]

		push bp
		mov bp, sp

		push ax
		push dx

		mov ah, 06h
		mov dx, symbol
		int 21h

		pop dx
		pop ax

;		mov sp, bp
		pop bp
		ret 2
endp

getchar proc			; ���� �������
		mov ah, 01h
		int 21h
		ret	
endp

code_size = $ - textseg
text	ends

stk	segment stack use16
	db 256 dup ('^')
stk	ends
	end main
