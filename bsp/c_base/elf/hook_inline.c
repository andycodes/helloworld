
//3.1 寻址指令替换地址
/*
首先跟got表hook一样，读取/proc/self/map文件，找到目标so的基地址，
然后把目标函数的偏移地址 +8 作为指令替换的地址。
*/
void *base_addr = get_model_base(getpid(), "libnative-lib.so");  // 读取map文件，按行读取分割匹配，获取so对应的内存基地址
int *addr =  base_addr + targer_addr + 8 ; // 指令替换开始地址

//3.2构建8字节跳转代码
//首先 备份要被替换的2条ARM汇编代码
memcpy(backup_addr, addr, 8)
/*
然后 用寄存器间接寻址方式，通过LDR PC指令和一个
地址（共计8 Bytes）替换备份的2条汇编代码,
修改pc的值，来修改程序执行流程。跳转指令为啥
不用B系列指令来跳转？因为ARM的B系列指令跳转范围
只有4M，Thumb的B系列指令跳转范围只有256字节，
然而大多数情况下跳转范围都会大于4M，
故采用LDR PC, [PC, ?]构造跳转指令
构建的跳转的汇编指令如下
*/
LDR PC, [PC, #-4] 
xxxxaddr
//翻译成c语言为
BYTE szLdrPCOpcodes[8] = {0x04, 0xF0, 0x1F, 0xE5};  // LDR PC, [PC, #-4]对应的机器码为：0xE51FF004
memcpy(szLdrPCOpcodes + 4, &pJumpAddress, 4); // 将目的地址拷贝到跳转指令下方的4 Bytes中

//3.3 构建stub函数
/*
构造思路是先压栈保存寄存器现场，然后跳转到用户的自定义的hook函数并执行，
执行完成后，从栈恢复所有的寄存器状态,然后跳转到之前备份的8字节代码处。

压栈出栈，以及切换状态 需要用到汇编代码
*/
_shellcode_start_s:
    push    {r0, r1, r2, r3}  ;//压栈保存cpu现场
    mrs     r0, cpsr
    str     r0, [sp, #0xC]
    str     r14, [sp, #8]   
    add     r14, sp, #0x10
    str     r14, [sp, #4]    
    pop     {r0}               
    push    {r0-r12}           
    mov     r0, sp
    ldr     r3, _hookstub_function_addr_s 
    blx     r3     ;//跳转到用户自定义hook函数
    ldr     r0, [sp, #0x3C] ;//恢复cpu现场
    msr     cpsr, r0
    ldmfd   sp!, {r0-r12}       
    ldr     r14, [sp, #4]
    ldr     sp, [r13]
    ldr     pc, _old_function_addr_s

//3.4 执行备份代码，跳转到原函数继续执行
/*
先执行之前备份的2条ARM代码（共计8 Btyes），然后用LDR指令跳转回Hook地址+8 bytes的地址处继续执行
*/
//备份代码1
//备份代码2
LDR PC, [PC, #-4] ;// 跳回hook地址+8处，继续执行原函数
HOOK_ADDR+8

//4.指令修复
/*
以上流程看似一切正常，cpu的现场都被保存和
恢复了,但是，如果说 被替换的两条指令，
在恢复执行的时候，有用到pc寄存器的值，
这两条指令的执行位置是在stub跳板函数中，
并不是原函数，所以pc的值并不是预期的值，
这种情况就要进行执行指令修复。
指令修复需要考虑以下指令
（ARM为例，thumb和thumb2类似）
B系列跳转
ADD_ARMADR_ARM, LDR_ARM, MOV_ARM
其它指令 OTHER_ARM
篇幅原因以最简单的ADD指令为例讲解下
指令修复：ADD指令 可能用到PC寄存器，
用到PC的时候，PC位于ADD指令机器码的
为16到19位。
修复时候，给PC正确的值即可。
*/

//1.首先找一个指令没有用到的寄存器Rr
int rd;
int rm;
int r;
// 解析指令得到rd、rm寄存器
rd = (instruction & 0xF000) >> 12;
rm = instruction & 0xF;
// 为避免冲突，排除rd、rm寄存器，选择一个临时寄存器Rr
for (r = 12; ; --r) {
	if (r != rd && r != rm) {
		break;
	}
}

//2.然后把Rr值压栈
  //  trampoline_instructions 存放修正后指令的首地址，用于调用原函数
  trampoline_instructions[index++] = 0xE52D0004 | (r << 12); // PUSH {Rr}，保护Rr寄存器值


//3.把PC的值给Rr
    trampoline_instructions[index++] = 0xE59F0008 | (r << 12); // LDR Rr, [PC, #8]，

//4 变换原指令ADR Rd, <label>为ADR Rd, Rr, ?
   trampoline_instructions[index++] = (instruction & 0xFFF0FFFF) | (r << 16);

//5.Rr出栈，恢复Rm原来的值
  trampoline_instructions[index++] = 0xE49D0004 | (r << 12); // POP {Rr}

//6.继续执行下面的代码
    trampoline_instructions[index++] = 0xE28FF000;// ADD PC, PC，0 跳过下一条指令
    trampoline_instructions[index++] = pc; // 存放的地址


