
%include ".\include\boot.inc"
SECTION MBR vstart=0x7c00   
;MBR  BIOS加载此二进制代码到内存0X8000地址上，CPU运行

    mov  ax, 0
    mov  ss, ax
    mov  ds, ax
    mov  es, ax
	mov  ss, ax
    mov  si, ax
	mov  sp, 0x7c00
    mov  ax, 0xb800
    mov  gs, ax	
   
   ; 清屏
;利用0x06号功能，上卷全部行，则可清屏。
; -----------------------------------------------------------
;INT 0x10   功能号:0x06	   功能描述:上卷窗口
;------------------------------------------------------
;输入：
;AH 功能号= 0x06
;AL = 上卷的行数(如果为0,表示全部)
;BH = 上卷行属性
;(CL,CH) = 窗口左上角的(X,Y)位置
;(DL,DH) = 窗口右下角的(X,Y)位置
;无返回值：
   mov     ax, 0600h
   mov     bx, 0700h
   mov     cx, 0                   ; 左上角: (0, 0)
   mov     dx, 184fh		   ; 右下角: (80,25),
				   ; 因为VGA文本模式中，一行只能容纳80个字符,共25行。
				   ; 下标从0开始，所以0x18=24,0x4f=79
   int     10h      ; int 10h

   ;===============================图形模式===============
   ;mov     ax, 0013h
   ;mov     bx, 107h
   ;mov     cx, 0                   ; 左上角: (0, 0)
   ;int     10h 

   
readSection1:	
	 ;读取0磁头0柱面2扇区数据到内存的BX地址处
    mov  BX, LOADER_BASE_ADDR ; BX = 0X900  ES:BX数据存储缓冲区的地址

	mov  AH, 0x02     ; AH = 02表示要做的是读盘操作
    mov  AL, 4        ; AL表示要连续读取几个扇区
    mov  CH, 0        ;CH 用来存储柱面号
    mov  CL, 3        ;CL 用来存储扇区号
    mov  DH, 0        ;DH 用来存储磁头号 
    mov  DL, 0        ;驱动器编号，一般我们只有一个软盘驱动器，所以写死为0
    INT  0x13         ;调用BIOS中断实现磁盘读取功能



	jmp  LOADER_BASE_ADDR	  ;EIP跳转

    

;fin:
;	jmp $

	
;times 510-($-$$) db 0
;db 0x55,0xaa
