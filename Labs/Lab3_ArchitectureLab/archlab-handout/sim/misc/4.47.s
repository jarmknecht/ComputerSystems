
4.47.o:	file format Mach-O 64-bit x86-64

Disassembly of section __TEXT,__text:
_BubblePtr:
       0:	55 	pushq	%rbp
       1:	48 89 e5 	movq	%rsp, %rbp
       4:	48 89 7d f8 	movq	%rdi, -8(%rbp)
       8:	48 89 75 f0 	movq	%rsi, -16(%rbp)
       c:	48 c7 45 e8 00 00 00 00 	movq	$0, -24(%rbp)
      14:	48 c7 45 e0 00 00 00 00 	movq	$0, -32(%rbp)
      1c:	48 8b 75 f0 	movq	-16(%rbp), %rsi
      20:	48 83 ee 01 	subq	$1, %rsi
      24:	48 89 75 e0 	movq	%rsi, -32(%rbp)
      28:	48 8b 45 e0 	movq	-32(%rbp), %rax
      2c:	48 3b 45 f8 	cmpq	-8(%rbp), %rax
      30:	0f 86 7d 00 00 00 	jbe	125 <_BubblePtr+0xB3>
      36:	48 8b 45 f8 	movq	-8(%rbp), %rax
      3a:	48 89 45 e8 	movq	%rax, -24(%rbp)
      3e:	48 8b 45 e8 	movq	-24(%rbp), %rax
      42:	48 3b 45 e0 	cmpq	-32(%rbp), %rax
      46:	0f 83 51 00 00 00 	jae	81 <_BubblePtr+0x9D>
      4c:	48 8b 45 e8 	movq	-24(%rbp), %rax
      50:	48 8b 40 08 	movq	8(%rax), %rax
      54:	48 8b 4d e8 	movq	-24(%rbp), %rcx
      58:	48 3b 01 	cmpq	(%rcx), %rax
      5b:	0f 8d 26 00 00 00 	jge	38 <_BubblePtr+0x87>
      61:	48 8b 45 e8 	movq	-24(%rbp), %rax
      65:	48 8b 40 08 	movq	8(%rax), %rax
      69:	48 89 45 d8 	movq	%rax, -40(%rbp)
      6d:	48 8b 45 e8 	movq	-24(%rbp), %rax
      71:	48 8b 00 	movq	(%rax), %rax
      74:	48 8b 4d e8 	movq	-24(%rbp), %rcx
      78:	48 89 41 08 	movq	%rax, 8(%rcx)
      7c:	48 8b 45 d8 	movq	-40(%rbp), %rax
      80:	48 8b 4d e8 	movq	-24(%rbp), %rcx
      84:	48 89 01 	movq	%rax, (%rcx)
      87:	e9 00 00 00 00 	jmp	0 <_BubblePtr+0x8C>
      8c:	48 8b 45 e8 	movq	-24(%rbp), %rax
      90:	48 83 c0 08 	addq	$8, %rax
      94:	48 89 45 e8 	movq	%rax, -24(%rbp)
      98:	e9 a1 ff ff ff 	jmp	-95 <_BubblePtr+0x3E>
      9d:	e9 00 00 00 00 	jmp	0 <_BubblePtr+0xA2>
      a2:	48 8b 45 e0 	movq	-32(%rbp), %rax
      a6:	48 83 c0 f8 	addq	$-8, %rax
      aa:	48 89 45 e0 	movq	%rax, -32(%rbp)
      ae:	e9 75 ff ff ff 	jmp	-139 <_BubblePtr+0x28>
      b3:	5d 	popq	%rbp
      b4:	c3 	retq
