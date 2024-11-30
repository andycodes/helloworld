unsigned long __stack_chk_guard = 0xBAAAAAAD;//provide some magic numbers

void __stack_chk_fail(void)                         
{
 /* Error message */                                 
}// will be called when guard variable is corrupted 