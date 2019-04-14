#include <string.h>
#include <stdio.h>


typedef	int (*OPEN_FUNC) (void);

struct dev_driver_ops {
	OPEN_FUNC open;
	unsigned int (*read) (void);
	void (*write) (unsigned int parm);
};

struct dev_device {
	unsigned int local_parm;
	struct dev_driver_ops ops;/*or usr pointer*/
};

struct dev_device ooc_obj;


int dev_driver_ops_open(void)
{
	printf("[%s]\n", __func__);
	return 0;
}

unsigned int dev_driver_ops_read(void)
{
	return ooc_obj.local_parm;
}

void dev_driver_ops_write(unsigned int parm)
{
	ooc_obj.local_parm = parm;
}

void ooc_init(void)
{
	ooc_obj.ops.open = dev_driver_ops_open;
	ooc_obj.ops.read = dev_driver_ops_read;
	ooc_obj.ops.write = dev_driver_ops_write;
}

/***************************************************/

void ooc_open(void)
{
	ooc_obj.ops.open();
}

void ooc_read(void)
{
	unsigned int ret = ooc_obj.ops.read();
	printf("[%s][%u]\n", __func__, ret);
}

void ooc_write(unsigned int parm)
{
	ooc_obj.ops.write(parm);
}


int main(void)
{
	ooc_init();
	ooc_open();
	ooc_write(3);
	ooc_read();
	return 0;
}

