#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>
#include <asm/ptrace.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <elf.h>
#include <android/log.h>

#if defined(__i386__)
#define pt_regs user_regs_struct
#endif

#define LOG_TAG "INJECT"
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define CPSR_T_MASK (1u << 5)

const char* libc_path = "/system/lib/libc.so";
const char* linker_path = "/system/bin/linker";

/*--------------------------------------------------
*   ����:   ��Ŀ�����ָ���ĵ�ַ�ж�ȡ����
*
*   ����:
*           pid       ��Ҫע��Ľ���pid
*           src       ��Ҫ��ȡ��Ŀ����̵�ַ
*           buf       ��Ҫ��ȡ�����ݻ�����
*           size      ��Ҫ��ȡ�����ݳ���
*
*   ����ֵ: -1
*--------------------------------------------------*/
int ptrace_readdata(pid_t pid, uint8_t *src, uint8_t *buf, size_t size){
    uint32_t i, j, remain;
    uint8_t *laddr;

    union u{
        long val;
        char chars[sizeof(long)];
    }d;

    j = size/4;
    remain = size%4;
    laddr = buf;

    for(i = 0; i<j; i++){
        //���ڴ��ַsrc�ж�ȡ�ĸ��ֽ�
        d.val = ptrace(PTRACE_PEEKTEXT, pid, src, 0);
        memcpy(laddr, d.chars, 4);
        src += 4;
        laddr += 4;
    }

    if(remain > 0){
        d.val = ptrace(PTRACE_PEEKTEXT, pid, src, 0);
        memcpy(laddr, d.chars, remain);
    }
    return 0;
}

/*--------------------------------------------------
*   ����:   ��Ŀ�����ָ���ĵ�ַ��д������
*
*   ����:
*           pid       ��Ҫע��Ľ���pid
*           dest      ��Ҫд���Ŀ����̵�ַ
*           data      ��Ҫд������ݻ�����
*           size      ��Ҫд������ݳ���
*
*   ����ֵ: -1
*--------------------------------------------------*/
int ptrace_writedata(pid_t pid, uint8_t *dest, uint8_t *data, size_t size){
    uint32_t i, j, remain;
    uint8_t *laddr;

    union u{
        long val;
        char u_data[sizeof(long)];
    }d;

    j = size/4;
    remain = size%4;

    laddr = data;

    //��4�ֽڿ���
    for(i = 0; i<j; i++){
        memcpy(d.u_data, laddr, 4);
        //���ڴ��ַ��д���ĸ��ֽ�,�ڴ��ַ��dest����
        ptrace(PTRACE_POKETEXT, pid, dest, d.val);

        dest += 4;
        laddr += 4;
    }

    //�����4�ֽڵģ����ֽڿ���
    //Ϊ�����̶ȵı���ԭջ�����ݣ���Ҫ�Ȱ�ԭ����������ֽڶ�����
    //Ȼ��Ѷ��������remain���ǵ����ֽ���ǰ�������
    if(remain > 0){
        d.val = ptrace(PTRACE_PEEKTEXT, pid, dest, 0);    //���ڴ��ַ�ж�ȡ�ĸ��ֽڣ��ڴ��ַ��dest����
        for(i = 0; i<remain; i++){
            d.u_data[i] = *laddr++;
        }
        ptrace(PTRACE_POKETEXT, pid, dest, d.val);
    }
    return 0;
}

/*--------------------------------------------------
*   ����:   ��ȡָ�����̵ļĴ�����Ϣ
*
*   ����ֵ: ʧ�ܷ���-1
*--------------------------------------------------*/
int ptrace_getregs(pid_t pid, struct pt_regs *regs){
    if(ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0){
        perror("ptrace_getregs: Can not get register values.");
        return -1;
    }
    return 0;
}

/*--------------------------------------------------
*   ����:   �޸�Ŀ����̼Ĵ�����ֵ
*
*   ����:
*           pid        ��Ҫע��Ľ���pid
*           pt_regs    ��Ҫ�޸ĵ��¼Ĵ�����Ϣ
*
*   ����ֵ: -1
*--------------------------------------------------*/
int ptrace_setregs(pid_t pid, struct pt_regs *regs){
    if(ptrace(PTRACE_SETREGS, pid, NULL, regs) < 0){
        perror("ptrace_setregs:Can not set regsiter values.");
        return -1;
    }
    return 0;
}

/*--------------------------------------------------
*   ����:   �ָ���������
*
*   ����:
*           pid        ��Ҫע��Ľ���pid
*
*   ����ֵ: -1
*--------------------------------------------------*/
int ptrace_continue(pid_t pid){
    if(ptrace(PTRACE_CONT, pid, NULL, 0) < 0){
        perror("ptrace_cont");
        return -1;
    }
    return 0;
}

/*--------------------------------------------------
*   ����:   ���ӽ���
*
*   ����ֵ: ʧ�ܷ���-1
*--------------------------------------------------*/
int ptrace_attach(pid_t pid){
    if(ptrace(PTRACE_ATTACH, pid, NULL, 0) < 0){
        perror("ptrace_attach");
        return -1;
    }
    return 0;
}

// �ͷŶ�Ŀ����̵ĸ��ӵ���
int ptrace_detach(pid_t pid)
{
    if (ptrace(PTRACE_DETACH, pid, NULL, 0) < 0) {
        perror("ptrace_detach");
        return -1;
    }

    return 0;
}
/*--------------------------------------------------
*   ����:   ��ȡ������ָ��ģ����׵�ַ
*    ԭ��  ͨ������/proc/pid/maps�ļ������ҵ�Ŀ��module_name���ڴ�ӳ����ʼ��ַ��
*    �����ڴ��ַ�ı�﷽ʽ��startAddrxxxxxxx-endAddrxxxxxxx�ģ�����ͨ��ʹ��strtok(line,"-")���ָ��ַ�����ȡ��ַ
*    ���pid = -1,��ʾ��ȡ���ؽ��̵�ĳ��ģ��ĵ�ַ���������pid���̵�ĳ��ģ��ĵ�ַ
*   ����:
*           pid             ��Ҫע��Ľ���pid, ���Ϊ0���ȡ�������
*           module_name        ��Ҫ��ȡģ��·��
*
*   ����ֵ: ʧ�ܷ���NULL, �ɹ�����addr
*--------------------------------------------------*/
void *get_module_base(pid_t pid, const char* module_name)
{
    FILE* fp;
    long addr = 0;
    char* pch;
    char filename[32];
    char line[1024];

    if(pid < 0){
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    }else{
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    }

    fp = fopen(filename, "r");

    if(fp != NULL){
        while(fgets(line, sizeof(line), fp)){
            if(strstr(line, module_name)){
                pch = strtok(line, "-");
                //������pch�ַ������ݲ���base(��ʾ����)��ת�����޷��ŵĳ�������
                addr = strtoul(pch, NULL, 16);
                if(addr == 0x8000)
                    addr = 0;
                break;
            }
        }
        fclose(fp);
    }
    return (void*)addr;
}


/*--------------------------------------------------
*   ����:   ��ȡĿ������к���ָ��
*
*   ����:
*           target_pid          ��Ҫע��Ľ���pid
*           module_name            ��Ҫ��ȡ�ĺ������ڵ�lib��·��
*           local_addr            ��Ҫ��ȡ�ĺ������ڵ�ǰ�����ڴ��еĵ�ַ
*
*           Ŀ������к���ָ�� = Ŀ�����ģ���ַ - �������ģ���ַ + �ڴ��еĵ�ַ
*
*   ����ֵ: ʧ�ܷ���NULL, �ɹ�����ret_addr
*--------------------------------------------------*/
void* get_remote_addr(pid_t target_pid, const char* module_name, void* local_addr){
    void* local_handle, *remote_handle;
    //��ȡ����ĳ��ģ�����ʼ��ַ
    local_handle = get_module_base(-1, module_name);
    //��ȡԶ��pid��ĳ��ģ�����ʼ��ַ
    remote_handle = get_module_base(target_pid, module_name);

    LOGD("[+]get remote address: local[%x], remote[%x]\n", local_handle, remote_handle);

    //local_addr - local_handle��ֵΪָ������(��mmap)�ڸ�ģ���е�ƫ������Ȼ���ټ���remote_handle�������Ϊָ��������Ŀ����̵������ַ
    void* ret_addr = (void*)((uint32_t)local_addr - (uint32_t)local_handle) + (uint32_t)remote_handle;
    return ret_addr;
}

/*--------------------------------------------------
*   ����:   ͨ�����̵����ƻ�ȡ��Ӧ�Ľ���pid
*   ԭ��  ͨ������/procĿ¼�µ�������Ŀ¼����ȡ��Щ��Ŀ¼��Ŀ¼��(һ����ǽ��̵Ľ��̺�pid)��
*            ��ȡ��Ŀ¼���󣬾���ϳ�/proc/pid/cmdline�ļ�����Ȼ�����δ���Щ�ļ���cmdline�ļ�
*            �����ŵľ��ǽ�������ͨ�������Ϳ��Ի�ȡ���̵�pid��
*   ����ֵ: δ�ҵ�����-1
*--------------------------------------------------*/
int find_pid_of(const char* process_name){
    int id;
    pid_t pid = -1;
    DIR* dir;
    FILE* fp;
    char filename[32];
    char cmdline[296];

    struct dirent* entry;

    if(process_name == NULL){
        return -1;
    }

    dir = opendir("/proc");
    if(dir == NULL){
        return -1;
    }

    while((entry = readdir(dir)) != NULL){
        id = atoi(entry->d_name);
        if(id != 0){
            sprintf(filename, "/proc/%d/cmdline", id);
            fp = fopen(filename, "r");
            if(fp){
                fgets(cmdline, sizeof(cmdline), fp);
                fclose(fp);// �ͷŶ�Ŀ����̵ĸ��ӵ���

                if(strcmp(process_name, cmdline) == 0){
                    pid = id;
                    break;
                }
            }
        }
    }
    closedir(dir);
    return pid;
}

long ptrace_retval(struct pt_regs* regs){
    return regs->ARM_r0;
}

long ptrace_ip(struct pt_regs* regs){
    return regs->ARM_pc;
}

/*--------------------------------------------------
*   ����:   ����Զ�̺���ָ��
*    ԭ��    
1����Ҫִ�е�ָ��д��Ĵ����У�
ָ��ȴ���4��long�Ļ�����Ҫ��ʣ���ָ��ͨ��
ptrace_writedata����д��ջ�У�
2��ʹ��ptrace_continue��������Ŀ�Ľ��̣�
ֱ��Ŀ�Ľ��̷���״ֵ̬0xb7f
���Ը�ֵ�ķ�����������֣���
3������ִ����֮��Ŀ����̹���
ʹ��ptrace_getregs������ȡ��ǰ�����мĴ���ֵ��
�������ʹ��ptrace_retval������ȡ�����ķ���ֵ��
*   ����:
*           pid             ��Ҫע��Ľ���pid
*           addr             ���õĺ���ָ���ַ
*           params          ���õĲ���
*           num_params      ���õĲ�������
*           regs            Զ�̽��̼Ĵ�����Ϣ(ARMǰ4��������r0 ~ r3����)
*
*   ����ֵ: ʧ�ܷ���-1
*--------------------------------------------------*/
int ptrace_call(pid_t pid, uint32_t addr, long* params, 
uint32_t num_params, struct pt_regs* regs)
{
    uint32_t i;
    for(i = 0; i<num_params && i < 4; i++){
        regs->uregs[i] = params[i];
    }

    if(i < num_params){
        regs->ARM_sp -= (num_params - i) * sizeof(long);
        ptrace_writedata(pid, (void*)regs->ARM_sp, (uint8_t*)&params[i], (num_params - i)*sizeof(long));
    }
    //��PC�Ĵ���ֵ��ΪĿ�꺯���ĵ�ַ
    regs->ARM_pc = addr;
    ////ָ��ж�
    if(regs->ARM_pc & 1){
        /* thumb */
        regs->ARM_pc &= (~1u);
        regs->ARM_cpsr |= CPSR_T_MASK;
    }else{
         /* arm */
        regs->ARM_cpsr &= ~CPSR_T_MASK;
    }
    ///�����ӳ���ķ��ص�ַΪ�գ��Ա㺯��ִ����󣬷��ص�null��ַ������SIGSEGV����
    regs->ARM_lr = 0;

    //���޸ĺ��regsд��Ĵ����У�Ȼ�����ptrace_continue��ִ������ָ���Ĵ���
    if(ptrace_setregs(pid, regs) == -1 || ptrace_continue(pid) == -1){
        printf("error.\n");
        return -1;
    }

    int stat = 0;
    /* WUNTRACED����waitpid������ӽ��̽�����ͣ״̬��
    ��ô���������ء�����Ǳ�ptrace���ӽ��̣�
    ��ô��ʹ���ṩWUNTRACED������Ҳ�����ӽ��̽���
    ��ͣ״̬��ʱ���������ء�
    ����ʹ��ptrace_cont���е��ӽ��̣�������3�������
    ������ͣ״̬������һ��ϵͳ���ã����ӽ����˳������ӽ��̵�ִ�з������������0xb7f�ͱ�ʾ�ӽ��̽�������ͣ״̬��
    �ҷ��͵Ĵ����ź�Ϊ11(SIGSEGV)������ʾ��ͼ����δ
    ������Լ����ڴ�, ����ͼ��û��дȨ�޵��ڴ��
    ַд���ݡ���ôʲôʱ��ᷢ�����ִ����أ���Ȼ�����ӽ���ִ����ע���
    ����������������ǰ��������regs->ARM_lr = 0��
    ���ͻ᷵�ص�0��ַ������ִ�У�
    �����ͻ����SIGSEGV�ˣ�
    */
    waitpid(pid, &stat, WUNTRACED);
    /*stat��ֵ����2�ֽ����ڱ�ʾ�����ӽ��̵��˳�
    ����ͣ״̬�ź�ֵ����2�ֽڱ�ʾ�ӽ�����
    �˳�(0x0)������ͣ(0x7f)״̬��
    0xb7f�ͱ�ʾ�ӽ���Ϊ��ͣ״̬����������ͣ���ź�
    ��Ϊ11��sigsegv����*/
    while(stat != 0xb7f){
        if(ptrace_continue(pid) == -1){
            printf("error.\n");
            return -1;
        }
        waitpid(pid, &stat, WUNTRACED);
    }
    return 0;
}

/*--------------------------------------------------
*   ����:   ����Զ�̺���ָ��
*
*   ����:
*           pid            ��Ҫע��Ľ���pid
*           func_name      ���õĺ�������, �˲�������Debug�����
*           func_addr      ���õĺ���ָ���ַ
*           param          ���õĲ���
*           param_num      ���õĲ�������
*           regs           Զ�̽��̼Ĵ�����Ϣ(ARMǰ4��������r0 ~ r3����)
*
*   ����ֵ: ʧ�ܷ���-1
*--------------------------------------------------*/
int ptrace_call_wrapper(pid_t target_pid, const char* func_name, void* func_addr, long* param, int param_num, struct pt_regs* regs){
    LOGD("[+]Calling %s in target process.\n", func_name);
    if(ptrace_call(target_pid, (uint32_t)func_addr, param, param_num, regs) == -1)
        return -1;
    if(ptrace_getregs(target_pid, regs) == -1){
        return -1;
    }
    LOGD("[+] Target process returned from %s, return value = %x, pc = %x \n", func_name, ptrace_retval(regs), ptrace_ip(regs));
    return 0;
}

/*--------------------------------------------------
*   ����:   Զ��ע��
*
*   ����:
*           target_pid          ��Ҫע��Ľ���Pid
*           library_path           ��Ҫע���.so·��
*           function_name          .so�е����ĺ�����
*           param                 �����Ĳ���
*            param_size            ������С�����ֽ�Ϊ��λ
*
*   ����ֵ: ע��ʧ�ܷ���-1
*--------------------------------------------------*/
int inject_remote_process(pid_t target_pid, const char* library_path, const char* function_name, const char* param, size_t param_size){
    int ret = -1;
    void* mmap_addr, *dlopen_addr, *dlsym_addr, *dlclose_addr, *dlerror_addr;
    void *local_handle, *remote_handle, *dlhandle;
    uint8_t *map_base = 0;
    uint8_t *dlopen_param1_ptr, *dlsym_param2_ptr, *saved_r0_pc_ptr, *inject_param_ptr, *remote_code_ptr, *local_code_ptr;

    struct pt_regs regs, original_regs;
    extern uint32_t _dlopen_addr_s, _dlopen_param1_s, _dlopen_param2_s, _dlsym_addr_s, _dlsym_param2_s, _dlclose_addr_s, _inject_start_s, _inject_end_s, _inject_function_param_s, _saved_cpsr_s, _saved_r0_pc_s;

    uint32_t code_length;
    long parameters[10];

    LOGD("[+] Injecting process: %d\n", target_pid);

    //��ATTATCH��ָ��Ŀ����̣���ʼ����
    if(ptrace_attach(target_pid) == -1){
        goto exit;
    }

    //��GETREGS����ȡĿ����̵ļĴ����������ֳ�
    if(ptrace_getregs(target_pid, &regs) == -1)
        goto exit;

    //����ԭʼ�Ĵ���
    memcpy(&original_regs, &regs, sizeof(regs));

    //��ͨ��get_remote_addr������ȡĿ����̵�mmap�����ĵ�ַ���Ա�Ϊlibxxx.so�����ڴ�
    //����mmap������libc.so���У�Ϊ�˽�libxxx.so���ص�Ŀ������У�����Ҫʹ��Ŀ����̵�mmap������������Ҫ���ҵ�libc.so����Ŀ����̵���ʼ��ַ��
    mmap_addr = get_remote_addr(target_pid, libc_path, (void*)mmap);    //libc_path = "/system/lib/libc.so"
    LOGD("[+] Remote mmap address: %x\n", mmap_addr);

    parameters[0] = 0;����// ����ΪNULL��ʾ��ϵͳ�Զ�ѡ������ڴ�ĵ�ַ
    parameters[1] = 0x4000;����// ӳ���ڴ�Ĵ�С
    parameters[2] = PROT_READ | PROT_WRITE |PROT_EXEC;����// ��ʾӳ���ڴ�����ɶ���д��ִ��
    parameters[3] = MAP_ANONYMOUS | MAP_PRIVATE;����// ��������ӳ��
    parameters[4] = 0;����//����Ҫӳ���ļ����ڴ��У���Ϊ�ļ���fd
    parameters[5] = 0;����//�ļ�ӳ��ƫ����

    //��ͨ��ptrace_call_wrapper����mmap��������Ŀ�������Ϊlibxxx.so�����ڴ�
    if(ptrace_call_wrapper(target_pid, "mmap", mmap_addr, parameters, 6, &regs) == -1)
        goto exit;
    //�ݴӼĴ����л�ȡmmap�����ķ���ֵ����������ڴ��׵�ַ��
    map_base = ptrace_retval(&regs);

    //�����λ�ȡlinker��dlopen��dlsym��dlclose��dlerror�����ĵ�ַ
    dlopen_addr = get_remote_addr(target_pid, linker_path, (void*)dlopen);
    dlsym_addr = get_remote_addr(target_pid, linker_path, (void*)dlsym);
    dlclose_addr = get_remote_addr(target_pid, linker_path, (void*)dlclose);
    dlerror_addr = get_remote_addr(target_pid, linker_path, (void*)dlerror);

    LOGD("[+] Get imports: dlopen: %x, dlsym: %x, dlclose: %x, dlerror: %x\n", dlopen_addr, dlsym_addr, dlclose_addr, dlerror_addr);

    printf("library path = %s\n", library_path);
    //�ߵ���dlopen����
    //(1)��Ҫע���so��д��ǰ��mmap�������ڴ�
    ptrace_writedata(target_pid, map_base, library_path, strlen(library_path) + 1);

    parameters[0] = map_base;
    parameters[1] = RTLD_NOW | RTLD_GLOBAL;

    //(2)ִ��dlopen
    if(ptrace_call_wrapper(target_pid, "dlopen", dlopen_addr, parameters, 2, &regs) == -1){
        goto exit;
    }
    //(3)ȡ��dlopen�ķ���ֵ�������sohandle������
    void* sohandle = ptrace_retval(&regs);

    //�����dlsym����
    //Ϊfunctionname����һ������
    #define FUNCTION_NAME_ADDR_OFFSET 0X100
    ptrace_writedata(target_pid, map_base + FUNCTION_NAME_ADDR_OFFSET, function_name, strlen(function_name) + 1);
    parameters[0] = sohandle;
    parameters[1] = map_base + FUNCTION_NAME_ADDR_OFFSET;

    //����dlsym
    if(ptrace_call_wrapper(target_pid, "dlsym", dlsym_addr, parameters, 2, &regs) == -1)
        goto exit;
    void* hook_entry_addr = ptrace_retval(&regs);
    LOGD("hooke_entry_addr = %p\n", hook_entry_addr);

    //����ñ�ע�뺯��hook_entry
    #define FUNCTION_PARAM_ADDR_OFFSET 0X200
    ptrace_writedata(target_pid, map_base + FUNCTION_PARAM_ADDR_OFFSET, parameters, strlen(parameters) + 1);
    parameters[0] = map_base + FUNCTION_PARAM_ADDR_OFFSET;

    if(ptrace_call_wrapper(target_pid, "hook_entry", hook_entry_addr, parameters, 1, &regs) == -1)
        goto exit;
    //�����dlclose�ر�lib
    printf("Press enter to dlclose and detach.\n");
    getchar();
    parameters[0] = sohandle;

    if(ptrace_call_wrapper(target_pid, "dlclose", dlclose, parameters, 1, &regs) == -1)
        goto exit;

    //?�ָ��ֳ����˳�ptrace
    ptrace_setregs(target_pid, &original_regs);
    ptrace_detach(target_pid);
    ret = 0;

exit:
    return ret;
}

int main(int argc, char** argv) {
    pid_t target_pid;
    target_pid = find_pid_of("com.bbk.appstore");
    if (-1 == target_pid) {
        printf("Can't find the process\n");
        return -1;
    }
    //target_pid = find_pid_of("/data/test");
    inject_remote_process(target_pid, "/data/local/tmp/libentry.so", "hook_entry",  "Fuck you!", strlen("Fuck you!"));
    return 0;
}
