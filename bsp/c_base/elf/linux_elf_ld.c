#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(){
      printf("Loading libs\n");
      int (*pt2Function)(void) = NULL;
      //pointer to a void function - change this to match method sig
      void* sdl_library = dlopen("/system/libtarget.so", RTLD_LAZY);
      if (sdl_library == NULL) {
          // report error ...
          printf("Unable to load library\n");
          char *errstr;
          errstr = dlerror();
          if (errstr != NULL)
                printf ("A dynamic linking error occurred: (%s)\n", errstr);
      } else {
          printf("Lib loaded, getting dlysm\n");
          void* initializer = dlsym(sdl_library,"JNI_OnLoad");
          if (initializer == NULL) {
              // report error ...   printf("Unable to get address of JNI_OnLoad\n");
              char *errstr;
              errstr = dlerror();
              if (errstr != NULL)
                    printf ("A dynamic linking error occurred: (%s)\n", errstr);
          } else {
              // cast initializer to its proper type and use
              printf("calling get process\n");
              //asm("BKPT #0");
              pt2Function = initializer;
              printf("got get process, setting up\n");
              printf("Ok, lets Calling the function");
              int result = pt2Function();
              printf("Result of call is %d", result);
              //asm("BKPT #0");
          }
      }
      return 0;
}

