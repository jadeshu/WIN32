
;--------------   gdt描述符属性  -----------
DESC_G_4K   equ	  1_00000000000000000000000b   
DESC_D_32   equ	   1_0000000000000000000000b
DESC_L	    equ	    0_000000000000000000000b	;  64位代码标记，此处标记为0便可。
DESC_AVL    equ	     0_00000000000000000000b	;  cpu不用此位，暂置为0  
DESC_LIMIT_CODE2  equ 1111_0000000000000000b
DESC_LIMIT_DATA2  equ DESC_LIMIT_CODE2
DESC_LIMIT_VIDEO2  equ 0000_000000000000000b
DESC_P	    equ		  1_000000000000000b
DESC_DPL_0  equ		   00_0000000000000b
DESC_DPL_1  equ		   01_0000000000000b
DESC_DPL_2  equ		   10_0000000000000b
DESC_DPL_3  equ		   11_0000000000000b
DESC_S_CODE equ		     1_000000000000b
DESC_S_DATA equ	  DESC_S_CODE
DESC_S_sys  equ		     0_000000000000b
;x=1,c=0,r=0,a=0 代码段是可执行的,非依从的,不可读的,已访问位a清0.
DESC_TYPE_CODE  equ	      1000_00000000b	  
;x=0,e=0,w=1,a=0 数据段是不可执行的,向上扩展的,可写的,已访问位a清0.
DESC_TYPE_DATA  equ	      0010_00000000b	

;cf9800
DESC_CODE_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_CODE2 + DESC_P + DESC_DPL_0 + DESC_S_CODE + DESC_TYPE_CODE + 0x00
DESC_DATA_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_DATA2 + DESC_P + DESC_DPL_0 + DESC_S_DATA + DESC_TYPE_DATA + 0x00
DESC_VIDEO_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_VIDEO2 + DESC_P + DESC_DPL_0 + DESC_S_DATA + DESC_TYPE_DATA + 0x0b
	
;--------------   选择子属性  ---------------
RPL0  equ   00b
RPL1  equ   01b
RPL2  equ   10b
RPL3  equ   11b
TI_GDT	 equ   000b
TI_LDT	 equ   100b
;--------------------------------------------
section loader vstart=0x900

   jmp loader_start
   
;构建gdt及其内部的描述符===============================================
   GDT_BASE:   dd    0x00000000 
	       	   dd    0x00000000

   CODE_DESC:  dd    0x0000FFFF 
	       	   dd    DESC_CODE_HIGH4

   DATA_STACK_DESC:  dd    0x0000FFFF
		     		 dd    DESC_DATA_HIGH4

   VIDEO_DESC: dd    0x80000007	       ; limit=(0xbffff-0xb8000)/4k=0x7
	           dd    DESC_VIDEO_HIGH4  ; 此时dpl为0

   GDT_SIZE    equ   $ - GDT_BASE
   GDT_LIMIT   equ   GDT_SIZE -	1 
   times 60 dq 0					 ; 此处预留60个描述符的空位(slot)
   SELECTOR_CODE  equ (0x0001<<3) + TI_GDT + RPL0     ; 8[1000] 相当于(CODE_DESC - GDT_BASE)/8 + TI_GDT + RPL0
   SELECTOR_DATA  equ (0x0002<<3) + TI_GDT + RPL0	 ; 16[10000] 同上
   SELECTOR_VIDEO equ (0x0003<<3) + TI_GDT + RPL0	 ; 24[11000] 同上 


   ;以下是定义gdt的指针，前2字节是gdt界限，后4字节是gdt起始地址
   gdt_ptr  dw  GDT_LIMIT 
	    	dd  GDT_BASE
;======================================================================
			
loader_start:

;-----------------   准备进入保护模式   -------------------
;1 打开A20
;2 加载gdt
;3 将cr0的pe位置1

   ;-----------------  打开A20  ----------------
   in al,0x92
   or al,0000_0010B
   out 0x92,al

   ;-----------------  加载GDT  ----------------
   lgdt [gdt_ptr]

   ;-----------------  cr0第0位置1  ----------------
   mov eax, cr0
   or eax, 0x00000001
   mov cr0, eax

   jmp dword SELECTOR_CODE:p_mode_start	     ; 刷新流水线，避免分支预测的影响,这种cpu优化策略，最怕jmp跳转，
					     ; 这将导致之前做的预测失效，从而起到了刷新的作用。

[bits 32]
p_mode_start:
   mov ax, SELECTOR_DATA
   mov ds, ax
   mov es, ax
   mov ss, ax
   mov esp,0x900
   mov ax, SELECTOR_VIDEO
   mov gs, ax
	
   ;160=80个字符[80*2]
   mov byte [gs:160*8], 'J'
   mov byte [gs:160*8+1],0x02
   
   mov byte [gs:160*8+2], 'a'
   mov byte [gs:160*8+3],0x02
   
   mov byte [gs:160*8+4], 'd'
   mov byte [gs:160*8+5],0x02
   
   mov byte [gs:160*8+6], 'e'
   mov byte [gs:160*8+7],0x02
   
   mov byte [gs:160*8+8], ' '
   mov byte [gs:160*8+9],0x00
   
   mov byte [gs:160*8+10], 'O'
   mov byte [gs:160*8+11],0x02
   
   mov byte [gs:160*8+12], 'S'
   mov byte [gs:160*8+13],0x02

   jmp $