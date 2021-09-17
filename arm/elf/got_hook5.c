#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <inttypes.h>
#include <sys/mman.h>

void writeText(const char *path, const char *text) 
{
        FILE *fp = NULL;
        if ((fp = fopen(path, "w")) == NULL) {
                printf("file cannot open");
        }
        //д������
        fwrite(text, strlen(text), 1, fp);
        if (fclose(fp) != 0) {
                printf("file cannot be closed");
        }
}

#define PAGE_START(addr) ((addr) & PAGE_MASK)
#define PAGE_END(addr)   (PAGE_START(addr) + PAGE_SIZE)

size_t hook_fwrite(const void *buf, size_t size, size_t count, FILE *fp) 
{
    printf("hook fwrite success");
    //�������һ���ı�
    const char *text = "hello ";
    fwrite(text, strlen(text), 1, fp);
    return fwrite(buf, size, count, fp);
}
 
/**
 * ֱ��Ӳ����ķ�ʽ����
 * hook��ʾ����
 * @param env
 * @param obj
 * @param jSoName
 */
void Java_com_feature_hook_NativeHook_hookSimple(JNIEnv *env, jobject obj, jstring jSoName) 
{
        const char *soName = (*env)->GetStringUTFChars(env, jSoName, 0);
        printf("soName=%s", soName);
        char line[1024] = "\n";
        FILE *fp = NULL;
        uintptr_t base_addr = 0;
        uintptr_t addr = 0;
        // 1. ���������Ӧ�Ļ�ַ
        if (NULL == (fp = fopen("/proc/self/maps", "r"))) 
                return;
        
        while (fgets(line, sizeof(line), fp)) {
                if (NULL != strstr(line, soName) &&
                        sscanf(line, "%"PRIxPTR"-%*lx %*4s 00000000", &base_addr) == 1)
                break;
        }
        
        fclose(fp);
        printf("base_addr=0x%08X", base_addr);
        
        if (0 == base_addr) 
                return;
        
        //2. ��ַ+ƫ��=��ʵ�ĵ�ַ
        addr = base_addr + 0x2FE0;
        printf("addr=0x%08X", addr);
        //ע�⣺����дȨ��
        mprotect((void *) PAGE_START(addr), PAGE_SIZE, PROT_READ | PROT_WRITE);
        //�滻Ŀ���ַ
        *(void **) addr = hook_fwrite;
        //ע�⣺���ָ���
        __builtin___clear_cache((void *) PAGE_START(addr), (void *) PAGE_END(addr));
}


void *get_module_base(pid_t pid, const char *module_name) {
    FILE *fp;
    long addr = 0;
    char filename[32] = "\n";
    char line[1024] = "\n";
    LOG_D("pid=%d ", pid);
    if (pid < 0) {
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    } else {
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    }
    // ��ȡָ��pid���̼��ص��ڴ�ģ����Ϣ
    fp = fopen(filename, "r");
    while (fgets(line, sizeof(line), fp)) {
        if (NULL != strstr(line, module_name) &&
            sscanf(line, "%"PRIxPTR"-%*lx %*4s 00000000", &addr) == 1)
            break;
    }
    fclose(fp);
    return (void *) addr;
}

