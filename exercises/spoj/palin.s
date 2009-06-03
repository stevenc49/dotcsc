	.file	"palin.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "%d\0"
LC1:
	.ascii "%d\12\0"
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	call	__alloca
	call	___main
	movl	%esp, -20(%ebp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_scanf
	movl	-16(%ebp), %eax
	sall	$2, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	call	__alloca
	leal	8(%esp), %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -24(%ebp)
	movl	$0, -4(%ebp)
L2:
	movl	-4(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jge	L3
	leal	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_scanf
	movl	-4(%ebp), %edx
	movl	-8(%ebp), %eax
	movl	-24(%ebp), %ecx
	movl	%eax, (%ecx,%edx,4)
	leal	-4(%ebp), %eax
	incl	(%eax)
	jmp	L2
L3:
	movl	$0, -4(%ebp)
L5:
	movl	-4(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jge	L6
	movl	-4(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	(%edx,%eax,4), %eax
	movl	%eax, -8(%ebp)
	leal	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	_incUntilNextPalin
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	leal	-4(%ebp), %eax
	incl	(%eax)
	jmp	L5
L6:
	movl	-20(%ebp), %esp
	movl	$0, %eax
	leave
	ret
.lcomm num_ary.0,1000000
.globl _isPalin
	.def	_isPalin;	.scl	2;	.type	32;	.endef
_isPalin:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC0, 4(%esp)
	movl	$num_ary.0, (%esp)
	call	_sprintf
	movl	$num_ary.0, -4(%ebp)
	movl	$num_ary.0, (%esp)
	call	_strlen
	movl	%eax, %edx
	movl	$num_ary.0, %eax
	decl	%eax
	leal	(%edx,%eax), %eax
	movl	%eax, -8(%ebp)
L9:
	movl	-4(%ebp), %eax
	movl	-8(%ebp), %edx
	movzbl	(%eax), %eax
	cmpb	(%edx), %al
	jne	L12
	jmp	L11
L12:
	movl	$0, -12(%ebp)
	jmp	L8
L11:
	movl	-8(%ebp), %ecx
	leal	-8(%ebp), %eax
	decl	(%eax)
	movl	-4(%ebp), %edx
	leal	-4(%ebp), %eax
	incl	(%eax)
	cmpl	%ecx, %edx
	ja	L10
	jmp	L9
L10:
	movl	$1, -12(%ebp)
L8:
	movl	-12(%ebp), %eax
	leave
	ret
.globl _incUntilNextPalin
	.def	_incUntilNextPalin;	.scl	2;	.type	32;	.endef
_incUntilNextPalin:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_isPalin
	cmpl	$1, %eax
	jne	L16
	movl	8(%ebp), %eax
	incl	(%eax)
L16:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_isPalin
	testl	%eax, %eax
	jne	L17
	movl	8(%ebp), %eax
	incl	(%eax)
	jmp	L16
L17:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leave
	ret
	.def	_strlen;	.scl	3;	.type	32;	.endef
	.def	_sprintf;	.scl	3;	.type	32;	.endef
	.def	_printf;	.scl	3;	.type	32;	.endef
	.def	_incUntilNextPalin;	.scl	3;	.type	32;	.endef
	.def	_scanf;	.scl	3;	.type	32;	.endef
