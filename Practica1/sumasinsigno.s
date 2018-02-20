.section .data
#L1:		.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
#L2:		.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
#L3:		.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
#L4:		.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff

#L1:		.int 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000
#L2:		.int 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000
#L3:		.int 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000
#L4:		.int 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000, 0x08000000

#L1:		.int 1, 2, 3, 4, 1, 2, 3, 4
#L2:		.int 1, 2, 3, 4, 1, 2, 3, 4
#L3:		.int 1, 2, 3, 4, 1, 2, 3, 4
#L4:		.int 1, 2, 3, 4, 1, 2, 3, 4

L1:		.int 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
L2:		.int 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
L3:		.int 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
L4:		.int 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x10000000, 0x20000000, 0x40000000, 0x8000000
	
longlista:	.int 8
resultado:	.quad -1

.section .text
_start:	.global _start

	mov $L1, %ebx
	mov longlista, %ecx
	mov $0, %eax
	mov $0, %edx
	call suma
	mov $L2, %ebx
	call suma
	mov $L3, %ebx
	call suma
	mov $L4, %ebx
	call suma
	mov %eax, resultado
	mov %edx, resultado+4

	mov $1, %eax
	mov $0, %ebx
	int $0x80

suma:
	push %esi
	mov $0, %esi
	
bucle:
	add (%ebx,%esi,4), %eax
	adc $0, %edx
	inc       %esi
	cmp  %esi,%ecx
	jne bucle

	pop %esi
	ret
