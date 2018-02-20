.section .data

#lista:		.int 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, -1

lista:		.int 0xf0000000, 0xe0000000, 0xe0000000, 0xd0000000, 0xf0000000, 0xe0000000, 0xe0000000, 0xd0000000, 0xf0000000, 0xe0000000, 0xe0000000, 0xd0000000, 0xf0000000, 0xe0000000, 0xe0000000, 0xd0000000, 0xf0000000, 0xe0000000, 0xe0000000, 0xd0000000, 0xf0000000, 0xe0000000, 0xe0000000, 0xd0000000, 0xf0000000, 0xe0000000, 0xe0000000, 0xd0000000, 0xf0000000, 0xe0000000, 0xe0000000, 0xd0000000

#lista:		.int 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff

longlista:	.int (.-lista)/4
resultado:	.quad -1

.section .text
_start:	.global _start

	mov    $lista, %ebx
	mov longlista, %ecx
	call suma
	mov %eax, resultado
	mov %edx, resultado+4

	mov $1, %eax
	mov $0, %ebx
	int $0x80

suma:
	push %esi
	push %ecx
	mov $0, %eax
	mov $0, %edx
	mov $0, %esi
	mov $0, %ecx
	mov $0, %edi
bucle:
	mov (%ebx,%esi,4), %eax
	cdq
	add %eax, %edi
	adc %edx, %ecx
	inc       %esi
	cmp %esi, (%esp)
	jne bucle

	mov %edi, %eax
	mov %ecx, %edx
	pop %esi
	pop %ecx
	ret
