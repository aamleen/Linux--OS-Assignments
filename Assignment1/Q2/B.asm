extern C    ;makes the C function visible

section .data
    text db "In function B", 10   ;This line will be printed to mark the location, 10 will add a new line

section .bss
    num resq 1  ;reserves an 8 byte storage to store the passed no.

section .text
    global B

B:
    mov [num], rdi  ;moving the value passed using rdi, to num variable
    call _printLocation     ;calling to print the text declared earlier
    call _printNum  ; prints the no. passed (internally converted to 8 byte ASCII string)
    call _manageStack   ;manages the stack so that when return is called, B moves to C
    ret ;returning or moving to C

_printLocation:
    mov rax, 1  ;arguments passed for write syscall
    mov rdi, 1
    mov rsi, text   ;passing the text as argument to write
    mov rdx, 14 ;length of the text is 14 bytes
    syscall
    ret

_printNum:
    mov rax, 1
    mov rdi, 1
    mov rsi, num    ;passing the number as argument to write, it will automatically be printed byte-wise
    mov rdx, 8  ;size of the passed number is 8-bytes
    syscall
    ret

_manageStack:
    push rbp    ;pushing the base pointer on the stack
    mov rbp, rsp    ;moving the value of stack pointer to stack base pointer
    lea rbx, [C]    ;extracting and storing the address of function C in rbx
    push rbx    ;pushing the address of C on the stack
    
    
