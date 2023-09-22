
../bin/boot/boot16.S.o:     file format elf32-i386


Disassembly of section .text:

00000000 <_start>:
   0:	fa                   	cli    
   1:	fc                   	cld    
   2:	31 c0                	xor    %eax,%eax
   4:	8e d8                	mov    %eax,%ds
   6:	8e c0                	mov    %eax,%es
   8:	8e d0                	mov    %eax,%ss
   a:	e8 25 00 72 1a       	call   1a720034 <.BufferOverMB+0x1a71fef7>
   f:	e8 e2 00 83 f8       	call   f88300f6 <.BufferOverMB+0xf882ffb9>
  14:	01 74 0b eb          	add    %esi,-0x15(%ebx,%ecx,1)
  18:	10 eb                	adc    %ch,%bl
  1a:	15 83 f8 01 74       	adc    $0x7401f883,%eax
  1f:	02 eb                	add    %bl,%ch
  21:	07                   	pop    %es

00000022 <_enable_succeed>:
  22:	b0 59                	mov    $0x59,%al
  24:	e8 5f 00 eb 07       	call   7eb0088 <.BufferOverMB+0x7eaff4b>

00000029 <_enable_fails>:
  29:	b0 4e                	mov    $0x4e,%al
  2b:	e8 58 00 eb 00       	call   eb0088 <.BufferOverMB+0xeaff4b>

00000030 <inf_loop>:
  30:	eb fe                	jmp    30 <inf_loop>

00000032 <enableA20>:
  32:	f8                   	clc    
  33:	60                   	pusha  
  34:	b7 00                	mov    $0x0,%bh
  36:	e8 bb 00 72 25       	call   257200f6 <.BufferOverMB+0x2571ffb9>
  3b:	85 c0                	test   %eax,%eax
  3d:	75 40                	jne    7f <_enable_a20_done>
  3f:	e8 4b 00 88 c3       	call   c388008f <.BufferOverMB+0xc387ff52>
  44:	f6 c3 01             	test   $0x1,%bl
  47:	75 58                	jne    a1 <_keyboard_controller>
  49:	f6 c3 02             	test   $0x2,%bl
  4c:	75 12                	jne    60 <.fast_gate>

0000004e <_bios_int>:
  4e:	b8 01 24 cd 15       	mov    $0x15cd2401,%eax
  53:	72 24                	jb     79 <_enable_a20_fail>
  55:	84 e4                	test   %ah,%ah
  57:	75 20                	jne    79 <_enable_a20_fail>
  59:	e8 98 00 85 c0       	call   c08500f6 <.BufferOverMB+0xc084ffb9>
  5e:	75 1f                	jne    7f <_enable_a20_done>

00000060 <.fast_gate>:
  60:	e4 92                	in     $0x92,%al
  62:	a8 02                	test   $0x2,%al
  64:	75 19                	jne    7f <_enable_a20_done>
  66:	0c 02                	or     $0x2,%al
  68:	24 fe                	and    $0xfe,%al
  6a:	e6 92                	out    %al,$0x92
  6c:	e8 85 00 85 c0       	call   c08500f6 <.BufferOverMB+0xc084ffb9>
  71:	75 0c                	jne    7f <_enable_a20_done>
  73:	84 ff                	test   %bh,%bh
  75:	75 02                	jne    79 <_enable_a20_fail>
  77:	eb 28                	jmp    a1 <_keyboard_controller>

00000079 <_enable_a20_fail>:
  79:	b0 4e                	mov    $0x4e,%al
  7b:	e8                   	.byte 0xe8
  7c:	08 00                	or     %al,(%eax)
  7e:	f9                   	stc    

0000007f <_enable_a20_done>:
  7f:	b0 59                	mov    $0x59,%al
  81:	e8 02 00 61 c3       	call   c3610088 <.BufferOverMB+0xc360ff4b>

00000086 <_print_char>:
  86:	b4 0e                	mov    $0xe,%ah
  88:	b7 00                	mov    $0x0,%bh
  8a:	cd 10                	int    $0x10
  8c:	c3                   	ret    

0000008d <_bios_function_gate_support>:
  8d:	53                   	push   %ebx
  8e:	f8                   	clc    
  8f:	b8 03 24 cd 15       	mov    $0x15cd2403,%eax
  94:	72 08                	jb     9e <_bios_function_gate_fail>
  96:	84 e4                	test   %ah,%ah
  98:	75 04                	jne    9e <_bios_function_gate_fail>
  9a:	89 d8                	mov    %ebx,%eax
  9c:	5b                   	pop    %ebx
  9d:	c3                   	ret    

0000009e <_bios_function_gate_fail>:
  9e:	f9                   	stc    
  9f:	5b                   	pop    %ebx
  a0:	c3                   	ret    

000000a1 <_keyboard_controller>:
  a1:	e8 10 00 e8 4d       	call   4de800b6 <.BufferOverMB+0x4de7ff79>
  a6:	00 85 c0 75 d4 b7    	add    %al,-0x482b8a40(%ebp)
  ac:	01 f6                	add    %esi,%esi
  ae:	c3                   	ret    
  af:	02 75 ae             	add    -0x52(%ebp),%dh
  b2:	eb c5                	jmp    79 <_enable_a20_fail>

000000b4 <_enable_a20_keyboard_controller>:
  b4:	fa                   	cli    
  b5:	e8 2e 00 b0 ad       	call   adb000e8 <.BufferOverMB+0xadafffab>
  ba:	e6 64                	out    %al,$0x64
  bc:	e8 27 00 b0 d0       	call   d0b000e8 <.BufferOverMB+0xd0afffab>
  c1:	e6 64                	out    %al,$0x64
  c3:	e8 27 00 e4 60       	call   60e400ef <.BufferOverMB+0x60e3ffb2>
  c8:	66 50                	push   %ax
  ca:	e8 19 00 b0 d1       	call   d1b000e8 <.BufferOverMB+0xd1afffab>
  cf:	e6 64                	out    %al,$0x64
  d1:	e8 12 00 66 58       	call   586600e8 <.BufferOverMB+0x5865ffab>
  d6:	0c 02                	or     $0x2,%al
  d8:	e6 60                	out    %al,$0x60
  da:	e8 09 00 b0 ae       	call   aeb000e8 <.BufferOverMB+0xaeafffab>
  df:	e6 64                	out    %al,$0x64
  e1:	e8 02 00 fb c3       	call   c3fb00e8 <.BufferOverMB+0xc3faffab>

000000e6 <_wait_io1>:
  e6:	e4 64                	in     $0x64,%al
  e8:	a8 02                	test   $0x2,%al
  ea:	75 fa                	jne    e6 <_wait_io1>
  ec:	c3                   	ret    

000000ed <_wait_io2>:
  ed:	e4 64                	in     $0x64,%al
  ef:	a8 01                	test   $0x1,%al
  f1:	75 f3                	jne    e6 <_wait_io1>
  f3:	c3                   	ret    

000000f4 <check_a20>:
  f4:	9c                   	pushf  
  f5:	1e                   	push   %ds
  f6:	06                   	push   %es
  f7:	57                   	push   %edi
  f8:	56                   	push   %esi
  f9:	fa                   	cli    
  fa:	31 c0                	xor    %eax,%eax
  fc:	8e d8                	mov    %eax,%ds
  fe:	be 00 05 f7 d0       	mov    $0xd0f70500,%esi
 103:	8e c0                	mov    %eax,%es
 105:	bf 10 05 8a 04       	mov    $0x48a0510,%edi
 10a:	a2 3c 01 26 8a       	mov    %al,0x8a26013c
 10f:	05 a2 3d 01 b4       	add    $0xb4013da2,%eax
 114:	01 c7                	add    %eax,%edi
 116:	04 00                	add    $0x0,%al
 118:	00 26                	add    %ah,(%esi)
 11a:	c7 05 01 00 8a 04 26 	movl   $0x75053a26,0x48a0001
 121:	3a 05 75 
 124:	02 fe                	add    %dh,%bh
 126:	cc                   	int3   

00000127 <_check_a20_exit>:
 127:	a0 3c 01 88 04       	mov    0x488013c,%al
 12c:	a0 3d 01 26 88       	mov    0x8826013d,%al
 131:	05 c1 e8 08 fb       	add    $0xfb08e8c1,%eax
 136:	07                   	pop    %es
 137:	1f                   	pop    %ds
 138:	5f                   	pop    %edi
 139:	5e                   	pop    %esi
 13a:	9d                   	popf   
 13b:	c3                   	ret    

0000013c <.BufferBelowMB>:
	...

0000013d <.BufferOverMB>:
	...
