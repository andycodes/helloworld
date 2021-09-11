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
ͨ������elf��ʽ������Section header table�ҳ���̬��.got���
λ�ã������ڴ����ҵ���Ӧ��.got��λ�ã����ʱ����
����.got�����ŵ��뺯���ĵ�ַ����ȡĿ�꺯����
ַ����.got��ÿһ�����ڵ�ַ����ƥ�䣬�ҵ��Ļ�
��ֱ���滻�µĺ�����ַ�������������һ�ε����
��Hook�����ˡ�
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

    // ��ʽ���ַ����õ� "/proc/pid/maps"
    if(pid < 0){
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    }else{
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    }

    // ���ļ�/proc/pid/maps����ȡָ��pid���̼��ص��ڴ�ģ����Ϣ
    fp = fopen(filename, "r");
    if(fp != NULL){
        // ÿ��һ�У���ȡ�ļ� /proc/pid/maps������
        while(fgets(line, sizeof(line), fp)){
            // ����ָ����soģ��
            if(strstr(line, module_name)){
                // �ָ��ַ���
                pch = strtok(line, "-");
                // �ַ���ת������
                addr = strtoul(pch, NULL, 16);

                // �����ڴ��ַ�Ĵ���
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

    // ��ȡĿ��pid������"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"ģ��ļ��ص�ַ
    void* base_addr = get_module_base(getpid(), LIB_PATH);
    LOGD("[+] libvivosgmain.so address = %p \n", base_addr);

    // ���汻Hook��Ŀ�꺯����ԭʼ���õ�ַ
    old_fopen = fopen;
    LOGD("[+] Orig fopen = %p\n", old_fopen);

    int fd;
    // ���ڴ�ģ���ļ�"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"
    fd = open(LIB_PATH, O_RDONLY);
    if(-1 == fd){
        LOGD("error.\n");
        return -1;
    }

        // elf32�ļ����ļ�ͷ�ṹ��Elf32_Ehdr
    Elf32_Ehdr ehdr;
    // ��ȡelf32��ʽ���ļ�"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"���ļ�ͷ��Ϣ
    read(fd, &ehdr, sizeof(Elf32_Ehdr));

    // elf32�ļ��н�������Ϣ�ṹ���ļ�ƫ��
    unsigned long shdr_addr = ehdr.e_shoff;
    // elf32�ļ��н�������Ϣ�ṹ������
    int shnum = ehdr.e_shnum;
    // elf32�ļ���ÿ����������Ϣ�ṹ�еĵ�����Ϣ�ṹ�Ĵ�С������ÿ����������Ϣ�Ľṹ��Ĵ�С��
    int shent_size = ehdr.e_shentsize;

    // elf32�ļ���������ÿ�����������ƴ�ŵĽ��������ַ������ڽ������е����index
    unsigned long stridx = ehdr.e_shstrndx;

    // elf32�ļ��н������ÿ����Ԫ��Ϣ�ṹ�壨����ÿ����������Ϣ�Ľṹ�壩
    Elf32_Shdr shdr;
    // elf32�ļ��ж�λ�����ÿ���������Ƶ��ַ��������Ϣ�ṹ��λ��.shstrtab
    lseek(fd, shdr_addr + stridx * shent_size, SEEK_SET);
    // ��ȡelf32�ļ��е�����ÿ����������Ϣ�Ľṹ�壨�����Ǳ���elf32�ļ���ÿ�������������ַ����ģ�
    read(fd, &shdr, shent_size);
    LOGD("[+] String table offset is %lu, size is %lu", shdr.sh_offset, shdr.sh_size); //41159, size is 254

    // Ϊ����elf32�ļ������еĽ����������ַ��������ڴ�ռ�
    char * string_table = (char *)malloc(shdr.sh_size);
    // ��λ��������elf32�ļ������еĽ����������ַ������ļ�ƫ�ƴ�
    lseek(fd, shdr.sh_offset, SEEK_SET);
    // ��elf32�ڴ��ļ��ж�ȡ���еĽ����������ַ�����������ڴ�ռ���
    read(fd, string_table, shdr.sh_size);

    // ��������elf32�ļ����ļ�ƫ��Ϊ������Ϣ�ṹ����ʼ�ļ�ƫ�ƴ�
    lseek(fd, shdr_addr, SEEK_SET);

    int i;
    uint32_t out_addr = 0;
    uint32_t out_size = 0;
    uint32_t got_item = 0;
    int32_t got_found = 0;

    // ѭ������elf32�ļ��Ľ���������ÿ����������Ϣ�Ľṹ�壩
    for(i = 0; i<shnum; i++){
        // ���ζ�ȡ��������ÿ��������������Ϣ�Ľṹ��
        read(fd, &shdr, shent_size);
        // �жϵ�ǰ���������ṹ�������Ľ����Ƿ���SHT_PROGBITS����
        //����ΪSHT_PROGBITS��.got��������ȫ��ƫ�Ʊ�
        if(shdr.sh_type == SHT_PROGBITS){
            // ��ȡ�����������ַ����ڱ������н����������ַ�����.shstrtab�е����
            int name_idx = shdr.sh_name;

            // �жϽ����������Ƿ�Ϊ".got.plt"����".got"
            if(strcmp(&(string_table[name_idx]), ".got.plt") == 0
                || strcmp(&(string_table[name_idx]), ".got") == 0){
                // ��ȡ����".got"����".got.plt"���ڴ���ʵ�����ݴ�ŵ�ַ
                out_addr = base_addr + shdr.sh_addr;
                // ��ȡ����".got"����".got.plt"�Ĵ�С
                out_size = shdr.sh_size;
                LOGD("[+] out_addr = %lx, out_size = %lx\n", out_addr, out_size);
                int j = 0;
                // ��������".got"����".got.plt"��ȡ�����ȫ�ֵĺ������õ�ַ
                for(j = 0; j<out_size; j += 4){
                    // ��ȡ����".got"����".got.plt"�еĵ��������ĵ��õ�ַ
                    got_item = *(uint32_t*)(out_addr + j);
                    // �жϽ���".got"����".got.plt"�к������õ�ַ�Ƿ��ǽ�Ҫ��Hook��Ŀ�꺯����ַ
                    if(got_item == old_fopen){
                        LOGD("[+] Found fopen in got.\n");
                        got_found = 1;
                        // ��ȡ��ǰ�ڴ��ҳ�Ĵ�С
                        uint32_t page_size = getpagesize();
                        // ��ȡ�ڴ��ҳ����ʼ��ַ����Ҫ�ڴ���룩
                        uint32_t entry_page_start = (out_addr + j) & (~(page_size - 1));
                        LOGD("[+] entry_page_start = %lx, page size = %lx\n", entry_page_start, page_size);
                        // �޸��ڴ�����Ϊ�ɶ���д��ִ��
                        if(mprotect((uint32_t*)entry_page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1){
                            LOGD("mprotect false.\n");
                            return -1;
                        }
                        LOGD("[+] %s, old_fopen = %lx, new_fopen = %lx\n", "before hook function", got_item, new_fopen);

                        // Hook����Ϊ�����Լ�����ĺ���
                        got_item = new_fopen;
                        LOGD("[+] %s, old_fopen = %lx, new_fopen = %lx\n", "after hook function", got_item, new_fopen);
                        // �ָ��ڴ�����Ϊ�ɶ���ִ��
                        if(mprotect((uint32_t*)entry_page_start, page_size, PROT_READ | PROT_EXEC) == -1){
                            LOGD("mprotect false.\n");
                            return -1;
                        }
                        break;
                    // ��ʱ��Ŀ�꺯���ĵ��õ�ַ�Ѿ���Hook��
                    }else if(got_item == new_fopen){
                        LOGD("[+] Already hooked.\n");
                        break;
                    }
                }
                // HookĿ�꺯���ɹ�������ѭ��
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
