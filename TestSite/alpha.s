	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z5Func1i              ## -- Begin function _Z5Func1i
	.p2align	4, 0x90
__Z5Func1i:                             ## @_Z5Func1i
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edi
	movl	-4(%rbp), %eax
	subl	$1, %eax
	andl	%eax, %edi
	cmpl	$0, %edi
	setne	%cl
	xorb	$-1, %cl
	andb	$1, %cl
	movzbl	%cl, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z5Func2i              ## -- Begin function _Z5Func2i
	.p2align	4, 0x90
__Z5Func2i:                             ## @_Z5Func2i
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edi
	callq	__ZL4log2IiENSt3__19enable_ifIXsr3std11is_integralIT_EE5valueEdE4typeES2_
	movl	-4(%rbp), %edi
	movsd	%xmm0, -16(%rbp)        ## 8-byte Spill
	callq	__ZL4log2IiENSt3__19enable_ifIXsr3std11is_integralIT_EE5valueEdE4typeES2_
	cvttsd2si	%xmm0, %edi
	cvtsi2sdl	%edi, %xmm0
	movsd	-16(%rbp), %xmm1        ## 8-byte Reload
                                        ## xmm1 = mem[0],zero
	ucomisd	%xmm0, %xmm1
	sete	%al
	setnp	%cl
	andb	%cl, %al
	andb	$1, %al
	movzbl	%al, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function _ZL4log2IiENSt3__19enable_ifIXsr3std11is_integralIT_EE5valueEdE4typeES2_
__ZL4log2IiENSt3__19enable_ifIXsr3std11is_integralIT_EE5valueEdE4typeES2_: ## @_ZL4log2IiENSt3__19enable_ifIXsr3std11is_integralIT_EE5valueEdE4typeES2_
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edi
	cvtsi2sdl	%edi, %xmm0
	callq	_log2
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
