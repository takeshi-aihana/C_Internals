	.file	"sample09.c"
	.comm	globalVar,4,4
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
	subl	$16, %esp
	movl	$globalVar, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$100, (%eax)
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	f, .-f
	.ident	"GCC: (Ubuntu 4.8.5-4ubuntu8) 4.8.5"
	.section	.note.GNU-stack,"",@progbits
