
farm.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <start_farm>:
   0:	b8 01 00 00 00       	mov    $0x1,%eax
   5:	c3                   	retq   

0000000000000006 <getval_222>:
   6:	b8 48 89 c7 c3       	mov    $0xc3c78948,%eax
   b:	c3                   	retq   

000000000000000c <setval_212>:
   c:	c7 07 48 89 c7 c3    	movl   $0xc3c78948,(%rdi)
  12:	c3                   	retq   

0000000000000013 <getval_214>:
  13:	b8 58 91 90 90       	mov    $0x90909158,%eax
  18:	c3                   	retq   

0000000000000019 <setval_252>:
  19:	c7 07 48 89 c7 91    	movl   $0x91c78948,(%rdi)
  1f:	c3                   	retq   

0000000000000020 <setval_495>:
  20:	c7 07 40 89 c7 c3    	movl   $0xc3c78940,(%rdi)
  26:	c3                   	retq   

0000000000000027 <getval_153>:
  27:	b8 d8 90 c3 24       	mov    $0x24c390d8,%eax
  2c:	c3                   	retq   

000000000000002d <addval_157>:
  2d:	8d 87 ed a5 58 90    	lea    -0x6fa75a13(%rdi),%eax
  33:	c3                   	retq   

0000000000000034 <setval_451>:
  34:	c7 07 af 9d 58 c3    	movl   $0xc3589daf,(%rdi)
  3a:	c3                   	retq   

000000000000003b <mid_farm>:
  3b:	b8 01 00 00 00       	mov    $0x1,%eax
  40:	c3                   	retq   

0000000000000041 <add_xy>:
  41:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax
  45:	c3                   	retq   

0000000000000046 <setval_289>:
  46:	c7 07 99 c1 90 90    	movl   $0x9090c199,(%rdi)
  4c:	c3                   	retq   

000000000000004d <setval_478>:
  4d:	c7 07 89 ca c3 e3    	movl   $0xe3c3ca89,(%rdi)
  53:	c3                   	retq   

0000000000000054 <addval_483>:
  54:	8d 87 81 d6 38 d2    	lea    -0x2dc7297f(%rdi),%eax
  5a:	c3                   	retq   

000000000000005b <addval_178>:
  5b:	8d 87 89 c1 08 db    	lea    -0x24f73e77(%rdi),%eax
  61:	c3                   	retq   

0000000000000062 <getval_101>:
  62:	b8 ba 48 89 e0       	mov    $0xe08948ba,%eax
  67:	c3                   	retq   

0000000000000068 <addval_216>:
  68:	8d 87 89 d6 84 c0    	lea    -0x3f7b2977(%rdi),%eax
  6e:	c3                   	retq   

000000000000006f <addval_304>:
  6f:	8d 87 a9 c1 08 db    	lea    -0x24f73e57(%rdi),%eax
  75:	c3                   	retq   

0000000000000076 <addval_257>:
  76:	8d 87 89 c1 60 db    	lea    -0x249f3e77(%rdi),%eax
  7c:	c3                   	retq   

000000000000007d <getval_326>:
  7d:	b8 4d be 89 d6       	mov    $0xd689be4d,%eax
  82:	c3                   	retq   

0000000000000083 <addval_259>:
  83:	8d 87 88 ca 90 90    	lea    -0x6f6f3578(%rdi),%eax
  89:	c3                   	retq   

000000000000008a <setval_413>:
  8a:	c7 07 88 ca 84 c9    	movl   $0xc984ca88,(%rdi)
  90:	c3                   	retq   

0000000000000091 <addval_255>:
  91:	8d 87 48 89 e0 91    	lea    -0x6e1f76b8(%rdi),%eax
  97:	c3                   	retq   

0000000000000098 <addval_172>:
  98:	8d 87 81 c1 38 c9    	lea    -0x36c73e7f(%rdi),%eax
  9e:	c3                   	retq   

000000000000009f <getval_203>:
  9f:	b8 8d c1 90 c3       	mov    $0xc390c18d,%eax
  a4:	c3                   	retq   

00000000000000a5 <setval_448>:
  a5:	c7 07 89 ca 92 90    	movl   $0x9092ca89,(%rdi)
  ab:	c3                   	retq   

00000000000000ac <getval_376>:
  ac:	b8 e4 c8 89 e0       	mov    $0xe089c8e4,%eax
  b1:	c3                   	retq   

00000000000000b2 <addval_309>:
  b2:	8d 87 68 89 e0 c3    	lea    -0x3c1f7698(%rdi),%eax
  b8:	c3                   	retq   

00000000000000b9 <getval_190>:
  b9:	b8 89 d6 91 c3       	mov    $0xc391d689,%eax
  be:	c3                   	retq   

00000000000000bf <setval_455>:
  bf:	c7 07 89 d6 18 db    	movl   $0xdb18d689,(%rdi)
  c5:	c3                   	retq   

00000000000000c6 <getval_486>:
  c6:	b8 48 8b e0 90       	mov    $0x90e08b48,%eax
  cb:	c3                   	retq   

00000000000000cc <addval_394>:
  cc:	8d 87 09 d6 90 c3    	lea    -0x3c6f29f7(%rdi),%eax
  d2:	c3                   	retq   

00000000000000d3 <setval_273>:
  d3:	c7 07 2b 48 89 e0    	movl   $0xe089482b,(%rdi)
  d9:	c3                   	retq   

00000000000000da <setval_464>:
  da:	c7 07 89 c1 20 db    	movl   $0xdb20c189,(%rdi)
  e0:	c3                   	retq   

00000000000000e1 <addval_350>:
  e1:	8d 87 89 ca 94 d2    	lea    -0x2d6b3577(%rdi),%eax
  e7:	c3                   	retq   

00000000000000e8 <setval_351>:
  e8:	c7 07 89 ca 38 c0    	movl   $0xc038ca89,(%rdi)
  ee:	c3                   	retq   

00000000000000ef <addval_296>:
  ef:	8d 87 58 89 e0 90    	lea    -0x6f1f76a8(%rdi),%eax
  f5:	c3                   	retq   

00000000000000f6 <getval_392>:
  f6:	b8 b6 89 d6 91       	mov    $0x91d689b6,%eax
  fb:	c3                   	retq   

00000000000000fc <getval_125>:
  fc:	b8 2d 4c 89 e0       	mov    $0xe0894c2d,%eax
 101:	c3                   	retq   

0000000000000102 <getval_362>:
 102:	b8 c9 ca 20 d2       	mov    $0xd220cac9,%eax
 107:	c3                   	retq   

0000000000000108 <getval_151>:
 108:	b8 8d ca 20 c9       	mov    $0xc920ca8d,%eax
 10d:	c3                   	retq   

000000000000010e <getval_410>:
 10e:	b8 89 d6 a4 c0       	mov    $0xc0a4d689,%eax
 113:	c3                   	retq   

0000000000000114 <addval_417>:
 114:	8d 87 89 c1 78 d2    	lea    -0x2d873e77(%rdi),%eax
 11a:	c3                   	retq   

000000000000011b <end_farm>:
 11b:	b8 01 00 00 00       	mov    $0x1,%eax
 120:	c3                   	retq   
