.file	"stats.c"
	.text
	.globl	mean_squared_error
	.type	mean_squared_error, @function
mean_squared_error:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movsd	%xmm0, -56(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	-44(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	jmp	.L2
.L3:
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	subsd	-56(%rbp), %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	mulsd	%xmm0, %xmm0
	movsd	-8(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	addq	$4, -40(%rbp)
.L2:
	movq	-40(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jb	.L3
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-44(%rbp), %xmm1
	movsd	-8(%rbp), %xmm0
	divsd	%xmm1, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	mean_squared_error, .-mean_squared_error
	.globl	sum
	.type	sum, @function
sum:
.LFB7:
	.cfi_startproc
	#pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	#movq	%rsp, %rbp
    .cfi_def_cfa_register 6
	
    #movq	%rdi, -24(%rbp)         # old: store ref to vals	
    #movl	%esi, -28(%rbp)         # old: store num locally
	#movq	%rdx, -40(%rbp)         # old: store mean pointer locally
	#movq	$0, -8(%rbp)            # old: initialize sum to 0
    
    movq    $0, %r8                  # initialize r8 to 0	

	#movl	-28(%rbp), %eax         # old: load num from local
	#movl	44(%rbp), %eax          # load num directly from main's frame
    movl    -36(%rbp), %eax              # accessing num from the register

	cltq
	leaq	0(,%rax,4), %rdx

	#movq	-24(%rbp), %rax         # old: load val from local
    movq    %rdi, %rax              # use RDI directly

    addq	%rdx, %rax                 
	#movq	%rax, -16(%rbp)         # old: make stack space for end
    movq    %rax, %r9               # move data to r9 instead
	jmp	.L6
.L7:
	#movq	-24(%rbp), %rax         # old: load val from local
    #movq    %rdi, %rax              # load val direct from RDI
	#movl	(%rax), %eax
    movl    (%rdi), %eax            # new: experiment

	cltq
	#addq	%rax, -8(%rbp)          # old: move rax to result
    addq    %rax, %r8               # move rax to r8

	#addq	$4, -24(%rbp)           # old: add 4 to local val
    addq    $4, %rdi                # add 4 to val from main

.L6:
	#movq	-24(%rbp), %rax         # old: load val from local
    movq    %rdi, %rax              # use rdi directly    

	#cmpq	-16(%rbp), %rax         # old: using the stack reference
    #cmpq    %r9, %rax               # using r9
    cmpq    %r9, %rdi               # r9 with rdi

	jb	.L7
	pxor	%xmm0, %xmm0
	#cvtsi2sdq	-8(%rbp), %xmm0    # old:
	cvtsi2sdq   %r8, %xmm0         # new

    pxor	%xmm1, %xmm1

	#cvtsi2sdl	-28(%rbp), %xmm1     # old: load num from local
	cvtsi2sdl	-36(%rbp), %xmm1      # load num directly from main's frame
    #cvtsi2sdl    %esi, %xmm1           # new: use num parameter directly

	divsd	%xmm1, %xmm0

	#movq	-40(%rbp), %rax         # old: load mean pointer from local
	#leaq	32(%rbp), %rax          # load address of mean directly from main's frame
    leaq    -48(%rbp), %rax

	movsd	%xmm0, (%rax)
	
    #movq	-8(%rbp), %rax          # old: move result to return register
    #movq    %r8, %rax               # old: move r8 to return register
    #movq    %r8, 56(%rbp)          # new: store result directly to main's stack frame
    movq    %r8, -24(%rbp)	

    #popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	sum, .-sum
	.section	.rodata
	.align 8
.LC1:
	.string	"How many integer values will you enter?"
.LC2:
	.string	"> "
.LC3:
	.string	"%d"
.LC4:
	.string	"Please enter %d integers.\n"
.LC5:
	.string	"Sum: %ld\n"
.LC6:
	.string	"Mean: %f\n"
.LC7:
	.string	"Mean squared error: %f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movl	$.LC1, %edi
	call	puts
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leaq	-36(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-36(%rbp), %eax
	cltq
	movl	$4, %esi
	movq	%rax, %rdi
	call	calloc
	movq	%rax, -16(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	addl	$1, -4(%rbp)
.L10:
	movl	-36(%rbp), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L11
	#movl	-36(%rbp), %ecx         # old: creation of variable
	#leaq	-48(%rbp), %rdx         # old: creation of variable
	movq	-16(%rbp), %rax
	#movl	%ecx, %esi
	movq	%rax, %rdi
	call	sum
    #movq	%rax, -24(%rbp)         # old: moved result to the spot in rbp
	movq	-48(%rbp), %rcx
	movl	-36(%rbp), %edx
	movq	-16(%rbp), %rax
	movq	%rcx, %xmm0
	movl	%edx, %esi
	movq	%rax, %rdi
	call	mean_squared_error
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movq	-48(%rbp), %rax
	movq	%rax, %xmm0
	movl	$.LC6, %edi
	movl	$1, %eax
	call	printf
	movq	-32(%rbp), %rax
	movq	%rax, %xmm0
	movl	$.LC7, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.4.1 20231218 (Red Hat 11.4.1-3)"
	.section	.note.GNU-stack,"",@progbits	
