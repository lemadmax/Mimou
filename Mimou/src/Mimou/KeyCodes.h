#pragma once

// From glfw3.h
#define MM_KEY_UNKNOWN            -1

/* Printable keys */
#define MM_KEY_SPACE              32
#define MM_KEY_APOSTROPHE         39  /* ' */
#define MM_KEY_COMMA              44  /* , */
#define MM_KEY_MINUS              45  /* - */
#define MM_KEY_PERIOD             46  /* . */
#define MM_KEY_SLASH              47  /* / */
#define MM_KEY_0                  48
#define MM_KEY_1                  49
#define MM_KEY_2                  50
#define MM_KEY_3                  51
#define MM_KEY_4                  52
#define MM_KEY_5                  53
#define MM_KEY_6                  54
#define MM_KEY_7                  55
#define MM_KEY_8                  56
#define MM_KEY_9                  57
#define MM_KEY_SEMICOLON          59  /* ; */
#define MM_KEY_EQUAL              61  /* = */
#define MM_KEY_A                  65
#define MM_KEY_B                  66
#define MM_KEY_C                  67
#define MM_KEY_D                  68
#define MM_KEY_E                  69
#define MM_KEY_F                  70
#define MM_KEY_G                  71
#define MM_KEY_H                  72
#define MM_KEY_I                  73
#define MM_KEY_J                  74
#define MM_KEY_K                  75
#define MM_KEY_L                  76
#define MM_KEY_M                  77
#define MM_KEY_N                  78
#define MM_KEY_O                  79
#define MM_KEY_P                  80
#define MM_KEY_Q                  81
#define MM_KEY_R                  82
#define MM_KEY_S                  83
#define MM_KEY_T                  84
#define MM_KEY_U                  85
#define MM_KEY_V                  86
#define MM_KEY_W                  87
#define MM_KEY_X                  88
#define MM_KEY_Y                  89
#define MM_KEY_Z                  90
#define MM_KEY_LEFT_BRACKET       91  /* [ */
#define MM_KEY_BACKSLASH          92  /* \ */
#define MM_KEY_RIGHT_BRACKET      93  /* ] */
#define MM_KEY_GRAVE_ACCENT       96  /* ` */
#define MM_KEY_WORLD_1            161 /* non-US #1 */
#define MM_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define MM_KEY_ESCAPE             256
#define MM_KEY_ENTER              257
#define MM_KEY_TAB                258
#define MM_KEY_BACKSPACE          259
#define MM_KEY_INSERT             260
#define MM_KEY_DELETE             261
#define MM_KEY_RIGHT              262
#define MM_KEY_LEFT               263
#define MM_KEY_DOWN               264
#define MM_KEY_UP                 265
#define MM_KEY_PAGE_UP            266
#define MM_KEY_PAGE_DOWN          267
#define MM_KEY_HOME               268
#define MM_KEY_END                269
#define MM_KEY_CAPS_LOCK          280
#define MM_KEY_SCROLL_LOCK        281
#define MM_KEY_NUM_LOCK           282
#define MM_KEY_PRINT_SCREEN       283
#define MM_KEY_PAUSE              284
#define MM_KEY_F1                 290
#define MM_KEY_F2                 291
#define MM_KEY_F3                 292
#define MM_KEY_F4                 293
#define MM_KEY_F5                 294
#define MM_KEY_F6                 295
#define MM_KEY_F7                 296
#define MM_KEY_F8                 297
#define MM_KEY_F9                 298
#define MM_KEY_F10                299
#define MM_KEY_F11                300
#define MM_KEY_F12                301
#define MM_KEY_F13                302
#define MM_KEY_F14                303
#define MM_KEY_F15                304
#define MM_KEY_F16                305
#define MM_KEY_F17                306
#define MM_KEY_F18                307
#define MM_KEY_F19                308
#define MM_KEY_F20                309
#define MM_KEY_F21                310
#define MM_KEY_F22                311
#define MM_KEY_F23                312
#define MM_KEY_F24                313
#define MM_KEY_F25                314
#define MM_KEY_KP_0               320
#define MM_KEY_KP_1               321
#define MM_KEY_KP_2               322
#define MM_KEY_KP_3               323
#define MM_KEY_KP_4               324
#define MM_KEY_KP_5               325
#define MM_KEY_KP_6               326
#define MM_KEY_KP_7               327
#define MM_KEY_KP_8               328
#define MM_KEY_KP_9               329
#define MM_KEY_KP_DECIMAL         330
#define MM_KEY_KP_DIVIDE          331
#define MM_KEY_KP_MULTIPLY        332
#define MM_KEY_KP_SUBTRACT        333
#define MM_KEY_KP_ADD             334
#define MM_KEY_KP_ENTER           335
#define MM_KEY_KP_EQUAL           336
#define MM_KEY_LEFT_SHIFT         340
#define MM_KEY_LEFT_CONTROL       341
#define MM_KEY_LEFT_ALT           342
#define MM_KEY_LEFT_SUPER         343  // Win, Fn, or cmd
#define MM_KEY_RIGHT_SHIFT        344
#define MM_KEY_RIGHT_CONTROL      345
#define MM_KEY_RIGHT_ALT          346
#define MM_KEY_RIGHT_SUPER        347
#define MM_KEY_MENU               348

#define MM_KEY_LAST               MM_KEY_MENU