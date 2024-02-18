#ifndef __PRINTLN_H__
#define __PRINTLN_H__

#include <stdio.h>
#include <stdint.h>

#define IS_SAME_TYPE(T1, T2) __builtin_types_compatible_p(__typeof__(T1), __typeof__(T2))

#define likely(x) __builtin_expect(!!(x), 1)
#define unlinkely(x) __builtin_expect(!!(x), 1)
#define __NAME2_HELPER(a, b) a##b
#define NAME2(a, b) __NAME2_HELPER(a, b)
#define UNIQUE_NAME(prefix) NAME2(NAME2(prefix, _), __LINE__)
#define IS_ARRAY(A) !IS_SAME_TYPE((A), &(A)[0])
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define FOREACH_ARRAY_ELEMENT(arr, item_ptr, closure)  \
    do {                                               \
        for (size_t i = 0; i < ARRAY_SIZE(arr); i++) { \
            typeof(arr[0]) *item_ptr = arr + i;        \
            {                                          \
                closure                                \
            }                                          \
        }                                              \
    } while (0)
#define _STR(s) #s
#define STR(s) _STR(s)

//
#define PRINTF printf

#define IF_LIKELY(match, s, closure) \
    if (IS_SAME_TYPE(match, s)) {    \
        closure                      \
    }

typedef enum _type_id {
    type_char = 0,
    type_i8 = 1,
    type_i16 = 2,
    type_i32 = 3,
    type_i64 = 4,
    type_u8 = 5,
    type_u16 = 6,
    type_u32 = 7,
    type_u64 = 8,
    type_f32 = 9,
    type_f64 = 10,
    type_custom,
} type_id_t;

#define IF_LIKEY_EQ(a, b, closure) \
    if (likely(a == b)) {          \
        closure                    \
    }
#define PRINT_FMT(fmt, ty, var)                                                \
    do {                                                                       \
        typeof(var) _v = var;                                                  \
        PRINTF("[%s: " STR(% fmt) "] ", STR(var), (ty) * (ty *)(void *)(&_v)); \
    } while (0)
#define PRINT_PARSE(type_id, var)                                     \
    do {                                                              \
        IF_LIKEY_EQ(type_id, type_char, PRINT_FMT(c, char, var);)     \
        IF_LIKEY_EQ(type_id, type_u8, PRINT_FMT(u, uint8_t, var);)    \
        IF_LIKEY_EQ(type_id, type_u16, PRINT_FMT(u, uint16_t, var);)  \
        IF_LIKEY_EQ(type_id, type_u32, PRINT_FMT(u, uint32_t, var);)  \
        IF_LIKEY_EQ(type_id, type_u64, PRINT_FMT(lx, uint64_t, var);) \
        IF_LIKEY_EQ(type_id, type_i8, PRINT_FMT(d, int8_t, var);)     \
        IF_LIKEY_EQ(type_id, type_i16, PRINT_FMT(d, int16_t, var);)   \
        IF_LIKEY_EQ(type_id, type_i32, PRINT_FMT(d, int32_t, var);)   \
        IF_LIKEY_EQ(type_id, type_i64, PRINT_FMT(ld, int64_t, var);)  \
        IF_LIKEY_EQ(type_id, type_f32, PRINT_FMT(f, float, var);)     \
        IF_LIKEY_EQ(type_id, type_f64, PRINT_FMT(lf, double, var);)   \
    } while (0)

#define TYPE_PARSE(x)       \
    _Generic((x),           \
        char: type_char,    \
        int8_t: type_i8,    \
        int16_t: type_i16,  \
        int32_t: type_i32,  \
        int64_t: type_i64,  \
        uint8_t: type_u8,   \
        uint16_t: type_u16, \
        uint32_t: type_u32, \
        uint64_t: type_u64, \
        float: type_f32,    \
        double: type_f64,   \
        default: type_u32)

#define PRINT_VAR(s)                     \
    do {                                 \
        type_id_t _type = TYPE_PARSE(s); \
        PRINT_PARSE(_type, s);           \
    } while (0)

#define PRINT_PTR(s)                     \
    do {                                 \
        PRINTF("[%s: 0x%p]", STR(s), s); \
    } while (0)

#define PRINT_ARR(fmt, s)                                         \
    do {                                                          \
        PRINTF("[%s: ", STR(s));                                  \
        FOREACH_ARRAY_ELEMENT(s, pch, PRINTF(STR(% fmt), *pch);); \
        PRINTF("]");                                              \
    } while (0)

#define _PRINT_1(s1) PRINT_VAR(s1)
#define _PRINT_2(s1, s2) \
    do {                 \
        PRINT_VAR(s1);   \
        PRINT_VAR(s2);   \
    } while (0)
#define _PRINT_3(s1, s2, s3) \
    do {                     \
        _PRINT_2(s1, s2);    \
        _PRINT_1(s3);        \
    } while (0)
#define _PRINT_4(s1, s2, s3, s4) \
    do {                         \
        _PRINT_3(s1, s2, s3);    \
        _PRINT_1(s4);            \
    } while (0)
#define _PRINT_5(s1, s2, s3, s4, s5) \
    do {                             \
        _PRINT_4(s1, s2, s3, s4);    \
        _PRINT_1(s5);                \
    } while (0)
#define _PRINT_6(s1, s2, s3, s4, s5, s6) \
    do {                                 \
        _PRINT_5(s1, s2, s3, s4, s5);    \
        _PRINT_1(s6);                    \
    } while (0)

#define _PRINT_7(s1, s2, s3, s4, s5, s6, s7) \
    do {                                     \
        _PRINT_6(s1, s2, s3, s4, s5, s6);    \
        _PRINT_1(s7);                        \
    } while (0)

#define _PRINT_8(s1, s2, s3, s4, s5, s6, s7, s8) \
    do {                                         \
        _PRINT_7(s1, s2, s3, s4, s5, s6, s7);    \
        _PRINT_1(s8);                            \
    } while (0)

#define _PRINT_9(s1, s2, s3, s4, s5, s6, s7, s8, s9) \
    do {                                             \
        _PRINT_8(s1, s2, s3, s4, s5, s6, s7, s8);    \
        _PRINT_1(s9);                                \
    } while (0)

#define _PRINT_10(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10) \
    do {                                                   \
        _PRINT_9(s1, s2, s3, s4, s5, s6, s7, s8, s9);      \
        _PRINT_1(s10);                                     \
    } while (0)

#define _ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, __N, ...) __N
#define VA_NUM_ARGS(...) _ARGS_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define _PRINT_(...) NAME2(_PRINT_, VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#define PRINTLN(args...) \
    _PRINT_(args);       \
    PRINTF("\r\n")

#define println(args...)                       \
    PRINTF("|%s +%d| : ", __FILE__, __LINE__); \
    PRINTLN(args)

#endif  // __PRINTLN_H__