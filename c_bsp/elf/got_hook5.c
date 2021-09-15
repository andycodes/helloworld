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
        //写入数据
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
    //这里插入一段文本
    const char *text = "hello ";
    fwrite(text, strlen(text), 1, fp);
    return fwrite(buf, size, count, fp);
}
 
/**
 * 直接硬编码的方式进行
 * hook演示操作
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
        // 1. 查找自身对应的基址
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
        
        //2. 基址+偏移=真实的地址
        addr = base_addr + 0x2FE0;
        printf("addr=0x%08X", addr);
        //注意：调整写权限
        mprotect((void *) PAGE_START(addr), PAGE_SIZE, PROT_READ | PROT_WRITE);
        //替换目标地址
        *(void **) addr = hook_fwrite;
        //注意：清除指令缓存
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
    // 获取指定pid进程加载的内存模块信息
    fp = fopen(filename, "r");
    while (fgets(line, sizeof(line), fp)) {
        if (NULL != strstr(line, module_name) &&
            sscanf(line, "%"PRIxPTR"-%*lx %*4s 00000000", &addr) == 1)
            break;
    }
    fclose(fp);
    return (void *) addr;
}

