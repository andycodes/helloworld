#ifndef __IMP1_H__
#define __IMP1_H__

#define IMP1_SET        128
#define IMP1_GET        128
#define IMP1_MAX        129

#define MEG_LEN (4*1024)
#define FUNC_NAME_LEN 128

typedef struct ecall_info{
    int sign_word;
    char func_name[FUNC_NAME_LEN];
    union {
            int args[6];
            struct {
                    int arg0;
                    int arg1;
                    int arg2;
                    int arg3;
                    int arg4;
                    int arg5;
                }param;
        }data;
}shell_fun_type;

#endif
