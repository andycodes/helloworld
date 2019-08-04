#include "tracelog.h"

void  __tracelog(u32 config,char* log_file,int file_max_size, char* log_msg,int msg_size) 
{ 
    struct file *fp; 
    mm_segment_t old_fs; 
    size_t f_size = 0;
    char msg_buf[LOG_MSG_MAX_SIZE] ={0};

    if((NULL == log_file)||(NULL == log_msg))
    {
        printk("parm NULL\n");
        return ;
    }

    if(msg_size >LOG_USR_MSG_MAX_SIZE)
   {
        printk("msg_size >LOG_USR_MSG_MAX_SIZE\n");
        return ;
   }

   if(LOG_CONF_NO_LOG == config) 
    {
        printk("No Log\n");
        return ;
    }


   memset((void*)msg_buf,0,LOG_MSG_MAX_SIZE);

    snprintf(
    msg_buf,
    LOG_MSG_MAX_SIZE,
    "my_debug:\npath:%s\nfunction:%s(),line:%d,date:%s,time:%s\n %s\n",
    __FILE__,
    __FUNCTION__,
    __LINE__,
    __DATE__, 
    __TIME__,
    log_msg); 

    if(PRINK_CONF(config))
    {
         printk("%s\n",msg_buf);
    } 

    if(!FILE_CONF(config))
   {
        printk("no file log\n");
        return;
   }
    

    old_fs = get_fs(); 
    set_fs(KERNEL_DS); 
    //set_fs(get_ds); //get_ds获得kernel的内存访问地址范围ARM LINUX 4G
    
    /*O_CREAT: IF not exist ,Creat it*/
    /*O_APPEND 每次写时都加到文件的尾端*/
    fp = filp_open(log_file, O_WRONLY | O_CREAT|O_APPEND, 0644); 
    
   if (IS_ERR(fp)) 
    { 
       printk("create file error:%s\n",KERNEL_FILE); 
       goto ERROR_EXIT;
    } 

   /*get file size*/
    f_size = vfs_llseek(fp, 0, SEEK_END);//SEEK_SET为定位到文件头

    if(f_size >= file_max_size)
   {
        printk(" f_size %d too big ,recreat log file\n", f_size);  
        /*O_TRUNC 重新创建文件*/
        fp = filp_open(log_file, O_WRONLY | O_TRUNC, 0644); 
    
       if (IS_ERR(fp)) 
        { 
           printk("create file error:%s\n",KERNEL_FILE); 
           goto ERROR_EXIT;
        } 
   }

/*write*/    
/*以下两种方法都可以
**建议使用vfs_write
*/
#if 0
    vfs_write(fp, buf, sizeof(buf), &pos);
#else
    fp->f_op->write(fp, (char *)msg_buf, strlen(msg_buf), &fp->f_pos);
#endif
    
    filp_close(fp, NULL); 
    set_fs(old_fs);     
    return ; 
ERROR_EXIT:
    {
         set_fs(old_fs); 
          return; 
    }
}

void  tracelog(char* log_msg,int msg_size) 
{
	__tracelog(0xFFFF,KERNEL_FILE,TRACE_FILE_MAX_SIZE,log_msg,msg_size); 
}

