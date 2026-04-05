// utils.h
#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <stddef.h>

uint16_t BCDByteToInt(uint8_t* BCDBytes, size_t BCDBytes_size);

#define MAX2(a, b) ((a) > (b) ? (a) : (b))

#define ZERO_OR_COMPILE_ERROR(cond) ((int) sizeof(char[1 - 2 * !(cond)]) - 1)
 
#define IS_ARRAY(array) \
        ZERO_OR_COMPILE_ERROR( \
                !__builtin_types_compatible_p(__typeof__(array), \
                                              __typeof__(&(array)[0])))

#define ARRAY_SIZE(array) \
        ((long) (IS_ARRAY(array) + (sizeof(array) / sizeof((array)[0]))))

#endif
