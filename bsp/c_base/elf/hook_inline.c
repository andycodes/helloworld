
//3.1 Ѱַָ���滻��ַ
/*
���ȸ�got��hookһ������ȡ/proc/self/map�ļ����ҵ�Ŀ��so�Ļ���ַ��
Ȼ���Ŀ�꺯����ƫ�Ƶ�ַ +8 ��Ϊָ���滻�ĵ�ַ��
*/
void *base_addr = get_model_base(getpid(), "libnative-lib.so");  // ��ȡmap�ļ������ж�ȡ�ָ�ƥ�䣬��ȡso��Ӧ���ڴ����ַ
int *addr =  base_addr + targer_addr + 8 ; // ָ���滻��ʼ��ַ

//3.2����8�ֽ���ת����
//���� ����Ҫ���滻��2��ARM������
memcpy(backup_addr, addr, 8)
/*
Ȼ�� �üĴ������Ѱַ��ʽ��ͨ��LDR PCָ���һ��
��ַ������8 Bytes���滻���ݵ�2��������,
�޸�pc��ֵ�����޸ĳ���ִ�����̡���תָ��Ϊɶ
����Bϵ��ָ������ת����ΪARM��Bϵ��ָ����ת��Χ
ֻ��4M��Thumb��Bϵ��ָ����ת��Χֻ��256�ֽڣ�
Ȼ��������������ת��Χ�������4M��
�ʲ���LDR PC, [PC, ?]������תָ��
��������ת�Ļ��ָ������
*/
LDR PC, [PC, #-4] 
xxxxaddr
//�����c����Ϊ
BYTE szLdrPCOpcodes[8] = {0x04, 0xF0, 0x1F, 0xE5};  // LDR PC, [PC, #-4]��Ӧ�Ļ�����Ϊ��0xE51FF004
memcpy(szLdrPCOpcodes + 4, &pJumpAddress, 4); // ��Ŀ�ĵ�ַ��������תָ���·���4 Bytes��

//3.3 ����stub����
/*
����˼·����ѹջ����Ĵ����ֳ���Ȼ����ת���û����Զ����hook������ִ�У�
ִ����ɺ󣬴�ջ�ָ����еļĴ���״̬,Ȼ����ת��֮ǰ���ݵ�8�ֽڴ��봦��

ѹջ��ջ���Լ��л�״̬ ��Ҫ�õ�������
*/
_shellcode_start_s:
    push    {r0, r1, r2, r3}  ;//ѹջ����cpu�ֳ�
    mrs     r0, cpsr
    str     r0, [sp, #0xC]
    str     r14, [sp, #8]   
    add     r14, sp, #0x10
    str     r14, [sp, #4]    
    pop     {r0}               
    push    {r0-r12}           
    mov     r0, sp
    ldr     r3, _hookstub_function_addr_s 
    blx     r3     ;//��ת���û��Զ���hook����
    ldr     r0, [sp, #0x3C] ;//�ָ�cpu�ֳ�
    msr     cpsr, r0
    ldmfd   sp!, {r0-r12}       
    ldr     r14, [sp, #4]
    ldr     sp, [r13]
    ldr     pc, _old_function_addr_s

//3.4 ִ�б��ݴ��룬��ת��ԭ��������ִ��
/*
��ִ��֮ǰ���ݵ�2��ARM���루����8 Btyes����Ȼ����LDRָ����ת��Hook��ַ+8 bytes�ĵ�ַ������ִ��
*/
//���ݴ���1
//���ݴ���2
LDR PC, [PC, #-4] ;// ����hook��ַ+8��������ִ��ԭ����
HOOK_ADDR+8

//4.ָ���޸�
/*
�������̿���һ��������cpu���ֳ����������
�ָ���,���ǣ����˵ ���滻������ָ�
�ڻָ�ִ�е�ʱ�����õ�pc�Ĵ�����ֵ��
������ָ���ִ��λ������stub���庯���У�
������ԭ����������pc��ֵ������Ԥ�ڵ�ֵ��
���������Ҫ����ִ��ָ���޸���
ָ���޸���Ҫ��������ָ��
��ARMΪ����thumb��thumb2���ƣ�
Bϵ����ת
ADD_ARMADR_ARM, LDR_ARM, MOV_ARM
����ָ�� OTHER_ARM
ƪ��ԭ������򵥵�ADDָ��Ϊ��������
ָ���޸���ADDָ�� �����õ�PC�Ĵ�����
�õ�PC��ʱ��PCλ��ADDָ��������
Ϊ16��19λ��
�޸�ʱ�򣬸�PC��ȷ��ֵ���ɡ�
*/

//1.������һ��ָ��û���õ��ļĴ���Rr
int rd;
int rm;
int r;
// ����ָ��õ�rd��rm�Ĵ���
rd = (instruction & 0xF000) >> 12;
rm = instruction & 0xF;
// Ϊ�����ͻ���ų�rd��rm�Ĵ�����ѡ��һ����ʱ�Ĵ���Rr
for (r = 12; ; --r) {
	if (r != rd && r != rm) {
		break;
	}
}

//2.Ȼ���Rrֵѹջ
  //  trampoline_instructions ���������ָ����׵�ַ�����ڵ���ԭ����
  trampoline_instructions[index++] = 0xE52D0004 | (r << 12); // PUSH {Rr}������Rr�Ĵ���ֵ


//3.��PC��ֵ��Rr
    trampoline_instructions[index++] = 0xE59F0008 | (r << 12); // LDR Rr, [PC, #8]��

//4 �任ԭָ��ADR Rd, <label>ΪADR Rd, Rr, ?
   trampoline_instructions[index++] = (instruction & 0xFFF0FFFF) | (r << 16);

//5.Rr��ջ���ָ�Rmԭ����ֵ
  trampoline_instructions[index++] = 0xE49D0004 | (r << 12); // POP {Rr}

//6.����ִ������Ĵ���
    trampoline_instructions[index++] = 0xE28FF000;// ADD PC, PC��0 ������һ��ָ��
    trampoline_instructions[index++] = pc; // ��ŵĵ�ַ


