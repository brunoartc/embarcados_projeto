#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int init_com(void)
{
    printk("\nHello World\n");
    return  0;
}
   
static void finish_com(void)
{
    return;
}

module_init(init_com);
module_exit(finish_com);