#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>

/*
通过解析elf格式，分析Section header table找出静态的.got表的
位置，并在内存中找到相应的.got表位置，这个时候内
存中.got表保存着导入函数的地址，读取目标函数地
址，与.got表每一项函数入口地址进行匹配，找到的话
就直接替换新的函数地址，这样就完成了一次导入表
的Hook操作了。
*/


#define LOG_TAG "INJECT"
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)

//FILE *fopen(const char *filename, const char *modes)
FILE* (*old_fopen)(const char *filename, const char *modes);
FILE* new_fopen(const char *filename, const char *modes){
    LOGD("[+] New call fopen.\n");
    if(old_fopen == -1){
        LOGD("error.\n");
    }
    return old_fopen(filename, modes);
}

void* get_module_base(pid_t pid, const char* module_name){
    FILE* fp;
    long addr = 0;
    char* pch;
    char filename[32];
    char line[1024];

    // 格式化字符串得到 "/proc/pid/maps"
    if(pid < 0){
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    }else{
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    }

    // 打开文件/proc/pid/maps，获取指定pid进程加载的内存模块信息
    fp = fopen(filename, "r");
    if(fp != NULL){
        // 每次一行，读取文件 /proc/pid/maps中内容
        while(fgets(line, sizeof(line), fp)){
            // 查找指定的so模块
            if(strstr(line, module_name)){
                // 分割字符串
                pch = strtok(line, "-");
                // 字符串转长整形
                addr = strtoul(pch, NULL, 16);

                // 特殊内存地址的处理
                if(addr == 0x8000){
                    addr = 0;
                }
                break;
            }
        }
    }
    fclose(fp);
    return (void*)addr;
}

#define LIB_PATH "/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"
int hook_fopen(){

    // 获取目标pid进程中"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"模块的加载地址
    void* base_addr = get_module_base(getpid(), LIB_PATH);
    LOGD("[+] libvivosgmain.so address = %p \n", base_addr);

    // 保存被Hook的目标函数的原始调用地址
    old_fopen = fopen;
    LOGD("[+] Orig fopen = %p\n", old_fopen);

    int fd;
    // 打开内存模块文件"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"
    fd = open(LIB_PATH, O_RDONLY);
    if(-1 == fd){
        LOGD("error.\n");
        return -1;
    }

        // elf32文件的文件头结构体Elf32_Ehdr
    Elf32_Ehdr ehdr;
    // 读取elf32格式的文件"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"的文件头信息
    read(fd, &ehdr, sizeof(Elf32_Ehdr));

    // elf32文件中节区表信息结构的文件偏移
    unsigned long shdr_addr = ehdr.e_shoff;
    // elf32文件中节区表信息结构的数量
    int shnum = ehdr.e_shnum;
    // elf32文件中每个节区表信息结构中的单个信息结构的大小（描述每个节区的信息的结构体的大小）
    int shent_size = ehdr.e_shentsize;

    // elf32文件节区表中每个节区的名称存放的节区名称字符串表，在节区表中的序号index
    unsigned long stridx = ehdr.e_shstrndx;

    // elf32文件中节区表的每个单元信息结构体（描述每个节区的信息的结构体）
    Elf32_Shdr shdr;
    // elf32文件中定位到存放每个节区名称的字符串表的信息结构体位置.shstrtab
    lseek(fd, shdr_addr + stridx * shent_size, SEEK_SET);
    // 读取elf32文件中的描述每个节区的信息的结构体（这里是保存elf32文件的每个节区的名称字符串的）
    read(fd, &shdr, shent_size);
    LOGD("[+] String table offset is %lu, size is %lu", shdr.sh_offset, shdr.sh_size); //41159, size is 254

    // 为保存elf32文件的所有的节区的名称字符串申请内存空间
    char * string_table = (char *)malloc(shdr.sh_size);
    // 定位到具体存放elf32文件的所有的节区的名称字符串的文件偏移处
    lseek(fd, shdr.sh_offset, SEEK_SET);
    // 从elf32内存文件中读取所有的节区的名称字符串到申请的内存空间中
    read(fd, string_table, shdr.sh_size);

    // 重新设置elf32文件的文件偏移为节区信息结构的起始文件偏移处
    lseek(fd, shdr_addr, SEEK_SET);

    int i;
    uint32_t out_addr = 0;
    uint32_t out_size = 0;
    uint32_t got_item = 0;
    int32_t got_found = 0;

    // 循环遍历elf32文件的节区表（描述每个节区的信息的结构体）
    for(i = 0; i<shnum; i++){
        // 依次读取节区表中每个描述节区的信息的结构体
        read(fd, &shdr, shent_size);
        // 判断当前节区描述结构体描述的节区是否是SHT_PROGBITS类型
        //类型为SHT_PROGBITS的.got节区包含全局偏移表
        if(shdr.sh_type == SHT_PROGBITS){
            // 获取节区的名称字符串在保存所有节区的名称字符串段.shstrtab中的序号
            int name_idx = shdr.sh_name;

            // 判断节区的名称是否为".got.plt"或者".got"
            if(strcmp(&(string_table[name_idx]), ".got.plt") == 0
                || strcmp(&(string_table[name_idx]), ".got") == 0){
                // 获取节区".got"或者".got.plt"在内存中实际数据存放地址
                out_addr = base_addr + shdr.sh_addr;
                // 获取节区".got"或者".got.plt"的大小
                out_size = shdr.sh_size;
                LOGD("[+] out_addr = %lx, out_size = %lx\n", out_addr, out_size);
                int j = 0;
                // 遍历节区".got"或者".got.plt"获取保存的全局的函数调用地址
                for(j = 0; j<out_size; j += 4){
                    // 获取节区".got"或者".got.plt"中的单个函数的调用地址
                    got_item = *(uint32_t*)(out_addr + j);
                    // 判断节区".got"或者".got.plt"中函数调用地址是否是将要被Hook的目标函数地址
                    if(got_item == old_fopen){
                        LOGD("[+] Found fopen in got.\n");
                        got_found = 1;
                        // 获取当前内存分页的大小
                        uint32_t page_size = getpagesize();
                        // 获取内存分页的起始地址（需要内存对齐）
                        uint32_t entry_page_start = (out_addr + j) & (~(page_size - 1));
                        LOGD("[+] entry_page_start = %lx, page size = %lx\n", entry_page_start, page_size);
                        // 修改内存属性为可读可写可执行
                        if(mprotect((uint32_t*)entry_page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1){
                            LOGD("mprotect false.\n");
                            return -1;
                        }
                        LOGD("[+] %s, old_fopen = %lx, new_fopen = %lx\n", "before hook function", got_item, new_fopen);

                        // Hook函数为我们自己定义的函数
                        got_item = new_fopen;
                        LOGD("[+] %s, old_fopen = %lx, new_fopen = %lx\n", "after hook function", got_item, new_fopen);
                        // 恢复内存属性为可读可执行
                        if(mprotect((uint32_t*)entry_page_start, page_size, PROT_READ | PROT_EXEC) == -1){
                            LOGD("mprotect false.\n");
                            return -1;
                        }
                        break;
                    // 此时，目标函数的调用地址已经被Hook了
                    }else if(got_item == new_fopen){
                        LOGD("[+] Already hooked.\n");
                        break;
                    }
                }
                // Hook目标函数成功，跳出循环
                if(got_found)
                    break;
            }
        }
    }
    free(string_table);
    close(fd);
}

int hook_entry(char* a){
    LOGD("[+] Start hooking.\n");
    hook_fopen();
    return 0;
}
