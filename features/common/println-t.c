#include "println.h"

int main(void)
{
    uint8_t v_u8 = 0;
    int8_t v_i8 = -1;
    uint16_t v_u16 = 0x1234;
    int16_t v_i16 = -1234;
    uint32_t v_u32 = 0x12345678;
    int32_t v_i32 = -12345678;
    uint64_t v_u64 = 0x1111222233334444;
    int64_t v_i64 = -1234567890;
    float v_f32 = 3.1415;
    double v_f64 = -99999.123;
    uint8_t arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("***************************** start *********************************\n");
    println(v_u8);
    println(v_u8, v_i8);
    println(v_u16, v_i16, 123456, -123456);
    println(v_u32, v_i32, v_u64, v_i64);
    println(v_f32, v_f64);
    println(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    println(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]);
    printf("***************************** end **********************************\n");
    return 0;
}