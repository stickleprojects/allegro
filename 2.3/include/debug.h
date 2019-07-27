
#ifndef DEBUG_H
    #define DEBUG_H

    #ifndef DEBUG
        #define DEBUG 1
    #endif
    
    #define debug_print(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#endif
