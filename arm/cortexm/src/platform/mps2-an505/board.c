char *board_info(void)
{
    return "CM33,mps2-an505";
}

void board_init(void)
{        
    UartStdOutInit();
    printk ("Version 1.1.0" " Build date: " __DATE__ "\n");
}