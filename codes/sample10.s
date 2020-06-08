	.file	"sample10.c"
	.comm	globalVar,20,4
	.text
	.globl	f
	.type	f, @function
f:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$32, %esp
	movl	$12, globalVar+8
	movl	$3, -20(%ebp)
	movl	$18, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -24(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	f, .-f
	.ident	"GCC: (Ubuntu 4.8.5-4ubuntu8) 4.8.5"
	.section	.note.GNU-stack,"",@progbits
