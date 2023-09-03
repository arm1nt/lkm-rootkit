#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("arm1nt");
MODULE_DESCRIPTION("POC rootkit for academic purposes only!");

static int __init rootkit_init(void)
{
    pr_info("Loading rootkit\n");

    return 0;
}


static void __exit rootkit_exit(void)
{
    pr_info("Unloading rootkit\n");
}


module_init(rootkit_init);
module_exit(rootkit_exit);