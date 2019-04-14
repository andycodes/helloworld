#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void MemDump(const void *adr, int len)
{
	const char *hex_ch 	= "0123456789ABCDEF";
	const char *fmt    		= "[%lX]  %.8s %.8s %.8s %.8s  * %.16s *\n";
	const char *base_adr, *curr_adr;
	unsigned char  hex[16<<4], asc[16];
	unsigned int num = len/16, rem= len%16;
	unsigned int ix=0;

	base_adr = curr_adr = (const char *)adr;
	for (ix=0; ix <= num; ix++){
		unsigned int iy;
		memset(hex,' ',16<<1);
		memset(asc,' ',sizeof(asc));
		for (iy=0; iy < ((ix<num) ? 16 : rem); iy++) {
			hex[(iy<<1)+0] = hex_ch[0x0F&(base_adr[(ix<<4)+iy]>>4)];
			hex[(iy<<1)+1] = hex_ch[0x0F&(base_adr[(ix<<4)+iy])   ];
			asc[iy]=((unsigned char)base_adr[(ix<<4)+iy]<=' ') ? '.' : base_adr[(ix<<4)+iy];
		}

		if ((ix<num) || (rem>0)){
			hex[iy<<1]=' ';
			printf(fmt,curr_adr,hex+0,hex+8,hex+16,hex+24,asc);
			fflush(stdout);
			curr_adr += 16;
		}
	}
}


int main(int argc, char *argv[])
{
	char obj[1024] ;
	memset((void*)obj, 0x55, sizeof(obj));
	MemDump(obj, sizeof(obj));
}

