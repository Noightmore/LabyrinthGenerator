global rnd_by_seed

;------------------------------------------
; return random number by seed value
; @param rdi seed value (unsigned 64bit integer)
; @return rax random number (64bit unsigned)
rnd_by_seed:
    push rbp
    mov rbp, rsp

    ; allocate space on stack for seed value
    sub rsp, 16
    mov [rsp+8], qword rdi

    ;
    ;	P2|P1|P0 := (S1|S0) * A
    ;
    mov	eax, dword [rsp+8] ; load low order word of seed
    mov	ebx, 16807 ; ¯\_(ツ)_/¯
    mul	ebx
    mov	esi, edx ;	si := pp01  (pp = partial product)
    mov	edi, eax ;	di := pp00 = P0
    mov	eax, dword [rsp+4] ; load high order word of seed
    mul	ebx ;	ax := pp11
    add	eax, esi ;	ax := pp11 + pp01 = P1
    adc	edx, 0 ;	dx := pp12 + carry = P2

    ;
    ;	P2|P1:P0 = p * 2**31 + q, 0 <= q < 2**31
    ;
    ;	p = P2 SHL 1 + sign bit of P1 --> dx
    ;		(P2:P1|P0 < 2**46 so p fits in a single word)
    ;	q = (P1 AND 7FFFh)|P0 = (ax AND 7fffh) | di
    ;
    shl	eax, 1
    rcl	edx, 1
    shr	eax, 1
    ;
    ;	dx:ax := p + q
    ;
    add	edx, edi ;	dx := p0 + q0
    adc	eax, 0 ;	ax := q1 + carry
    xchg eax, edx
    ;
    ;	if p+q < 2**63 then p+q is the new seed; otherwise whack
    ;	  off the sign bit and add 1 and THATs the new seed
    ;
    test edx, 80000000h
    jz	Store
    and	edx, 7fffffffh ;	whack off the sign bit
    add	eax, 1 ;		inc doesn't set carry bit
    adc	edx, 0

    Store:

	mov	dword [rsp+4], edx
	mov	dword [rsp+8], eax

	mov	rax, qword [rsp+8] ; load new random value into rax

    ; free space on stack
    add rsp, 16
leave
ret