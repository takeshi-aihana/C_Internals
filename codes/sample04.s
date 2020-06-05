	.file	"sample04.c"
	.text
	.globl	fun
	.type	fun, @function
fun:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$4, -16(%ebp)
	movl	$8, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	-16(%ebp), %edx
	orl	%edx, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	-12(%ebp), %edx
	andl	%edx, %eax
	movl	%eax, -4(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	fun, .-fun
	.ident	"GCC: (Ubuntu 4.8.5-4ubuntu8) 4.8.5"
	.section	.note.GNU-stack,"",@progbits
