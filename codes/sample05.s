	.file	"sample05.c"
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
	movl	$4, -12(%ebp)
	movl	$8, -8(%ebp)
	movl	$0, -4(%ebp)
	movl	-12(%ebp), %eax
	cmpl	-8(%ebp), %eax
	jle	.L2
	movl	$1, -4(%ebp)
	jmp	.L1
.L2:
	movl	$2, -4(%ebp)
.L1:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	fun, .-fun
	.ident	"GCC: (Ubuntu 4.8.5-4ubuntu8) 4.8.5"
	.section	.note.GNU-stack,"",@progbits
