.model small
.stack 100h
.data
    column_counter dw ?
    row_counter dw ?
    rows_count dw 3
    columns_count dw 2
    matrix_elements_count dw 6

    string_of_numbers_length equ 10
    mul_array             dw 5 dup ('$')
    result_array           dw 5 dup ('$')
    matrix                dw 8 * 8 dup('$')
    string_of_numbers     db string_of_numbers_length dup('$')

    input_matrix_msg db "Input matrix numbers $"
    input_invalid_msg db "Input error! $"
    try_again_msg db "Try again: $"
    input_element_msg db "Input: $"
    overflow_msg db "OVERFLOW $"
    result_msg db "String indexes with biggest mul: $"

    new_line db 13, 10,'$'
    space db " $"
    ten dw 000Ah
    one dw 1
.code

start:
    mov ax, @data
    mov ds, ax
    mov es, ax
    xor ax, ax

    mov [string_of_numbers], string_of_numbers_length
    call input_matrix
    call output_matrix
    call calculate_mul
    call output_mul
    call calculate_mul_maximum
    call output_mul_maximum
    exit:
        mov ax, 4c00h
        int 21h
    ends

input_matrix_elements proc
    call output_new_line
    lea dx, input_element_msg
    call output_string
    input_element:
        lea dx, string_of_numbers
        call input_string
        lea si, string_of_numbers[2]
        call string_to_int   
        jc input_error
        call element_load
        loop input_matrix_elements
        ret
    input_error:
        call output_new_line
        lea dx, input_invalid_msg
        call output_string
        jno try_again
    try_again:
        lea dx, try_again_msg
        call output_string
        jmp input_element
    element_load:
        mov [di], ax
        add di, 2 ; 2 - size of number
        ret
input_matrix_elements endp

string_to_int proc
    xor dx,dx
    xor bx,bx
    xor ax,ax ; result
    xor ch,ch
    jmp number_sign_check
    string_to_int_loop:
        mov bl, [si] ; one number is 1 byte
        jmp is_number
    string_valid:
        sub bl, '0'
        imul ten ; ax * 10
        jo string_invalid ; > 16 bit
        js string_invalid ; > 15 bit
        cmp ch, 1
        je add_negative
        add ax, bx
        js string_invalid
    invalid_check:
        inc si ; si - string address
        jmp string_to_int_loop
    add_negative:  
        ;;;;;;;;;;;;
        sub ax, bx  
        jns string_invalid 
        jmp invalid_check
    is_number:
        cmp bl, 0Dh
        je string_to_int_finish
        cmp bl, '0'
        jl string_invalid
        cmp bl, '9'
        jg string_invalid
        jmp string_valid
    number_sign_check:
        cmp [si], '-'        
        je number_negative
        cmp [si], '+'
        jne string_empty
        inc si
        jmp string_empty
    number_negative:
        mov ch, 1
        inc si
        jmp string_empty
    string_empty:
        cmp [si], 0Dh
        je string_invalid
        jmp string_to_int_loop
    string_invalid:
        xor ch, ch
        stc   ;CF = 1
        ret
    string_to_int_finish:
        clc  ; clear carry flag, cf = 0
        xor ch, ch
        ret
string_to_int endp

int_to_string proc
    push 0
    push 0024h  ;$
    add ax, 0000h
    js number_is_negative
    int_to_string_loop:
        xor dx,dx
        div ten
        add dx, '0'
        push dx
        cmp ax, 0h
        jne int_to_string_loop
    move_number_to_buffer:
        pop ax
        cmp al, '$'
        je int_to_string_finish
        mov [di], al
        inc di
        jmp move_number_to_buffer
    int_to_string_finish:
        pop ax
        mov [di], '$'
        ret
    number_is_negative:
        mov [di], '-'
        inc di
        not ax
        inc ax
        jmp int_to_string_loop
int_to_string endp

input_matrix proc
    call output_new_line
    lea dx, input_matrix_msg
    call output_string
    xor cx, cx
    mov cx, matrix_elements_count
    lea di, matrix
    call input_matrix_elements
    call output_new_line
ret
input_matrix endp

output_matrix proc
    mov column_counter, 0000h
    mov row_counter, 0000h
    lea si, matrix
    jmp loop_external
    loop_internal:
        lea dx, new_line
        call output_string
        mov row_counter, 0000h
        inc column_counter
        mov cx, column_counter
        cmp cx, columns_count
        je loop_return
    loop_external:
        mov ax, [si]
        add si, 2 ; 2 - size of number

        lea di, string_of_numbers[2]
        call int_to_string
        lea dx, string_of_numbers[2]
        call output_string
        lea dx, space
        call output_string
        inc row_counter
        mov cx, row_counter
        cmp cx, rows_count
        jne loop_external
        jmp loop_internal
    loop_return:
        ret
output_matrix endp

calculate_mul proc
    lea di, mul_array
    lea si, matrix
    lea bx, result_array
    mov column_counter, 0000h
    mov row_counter, 0000h
    xor ax, ax
    inc ax
    jmp mul_loop_external
    mul_loop_internal:
        mov [di], ax
        add di, 2 ; 2 - size of number
        add bx, 2 ; 2 - size of number
        xor ax, ax
        inc ax
        mov row_counter, 0000h
        inc column_counter
        mov cx, column_counter
        cmp cx, columns_count
        je mul_loop_internal_return
    mul_loop_external:
        imul one, [si]
        jo mul_overflow
    mul_after_overflow:
        add si, 2 ; 2 - size of number
        inc row_counter
        mov cx, row_counter
        cmp cx , rows_count
        jne mul_loop_external
        jmp mul_loop_internal
    mul_loop_internal_return:
        ret
calculate_mul endp

output_mul proc
    call output_new_line
    lea si, mul_array
    lea bx, result_array
    mov column_counter, 0000h
    output_mul_external_loop:
        cmp [bx], 0
        je output_overflow
        mov ax, [si]

        lea di, string_of_numbers[2]
        call int_to_string

        lea dx, string_of_numbers[2]
        call output_string
        call output_new_line
    output_mul_internal_loop:
        inc column_counter
        add si, 2 ; 2 - size of number
        add bx, 2 ; 2 - size of number
        mov cx, column_counter
        cmp cx, columns_count
        jne output_mul_external_loop
        ret
output_mul endp

output_overflow:
    lea dx, overflow_msg
    call output_string
    call output_new_line
    jmp output_mul_internal_loop

mul_overflow:
    mov word ptr [bx], 0
    jmp mul_after_overflow

calculate_mul_maximum proc
    lea si, result_array
    lea di, mul_array
    mov column_counter, 0001h
    jmp check_mul_overflow

    calculate_mul_maximum_loop:
        mov cx, column_counter
        cmp cx, columns_count
        je calculate_mul_maximum_end
        inc column_counter
        add si, 2 ; 2 - size of number
        add di, 2 ; 2 - size of number
        cmp [si], 0
        je calculate_mul_maximum_loop

        cmp bx, [di]
        jl temporary_mul_greater
    greater_fount:
        mov cx, column_counter
        cmp cx, columns_count
        jle calculate_mul_maximum_loop
    calculate_mul_maximum_end:
        ret
calculate_mul_maximum endp

check_mul_overflow:
    cmp [si], 0
    je check_mul_overflow_equals
    mov bx, [di]
    jmp calculate_mul_maximum_loop
check_mul_overflow_equals:
    inc column_counter
    add si, 2 ; 2 - size of number
    add di, 2 ; 2 - size of number
    jmp check_mul_overflow
temporary_mul_greater:
    mov bx, [di]
    jmp greater_fount

output_mul_maximum proc
    call output_new_line
    lea si, mul_array
    lea dx, result_msg
    call output_string
    mov column_counter, 0000h
    output_mul_maximum_loop:
        cmp bx, [si]
        je output_column
    output_mul_maximum_next:
        add si, 2 ; 2 - size of number
        inc column_counter
        mov cx, column_counter
        cmp cx, columns_count
        jne output_mul_maximum_loop
        ret
output_mul_maximum endp

output_column:
    mov ax, column_counter
    lea di, string_of_numbers[2]
    call int_to_string

    lea dx, string_of_numbers[2]
    call output_string
    lea dx, space
    call output_string
    jmp output_mul_maximum_next

output_new_line proc
    lea dx, new_line
    call output_string
ret
output_new_line endp

output_string proc
    mov ah, 09h
    int 21h
ret
output_string endp

input_string proc
    mov ah, 0Ah
    int 21h
    ret
input_string endp

end start