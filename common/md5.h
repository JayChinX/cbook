
#ifndef MD5_H
#define MD5_H

#include <cstring>
#include <string>

/* Parameters of MD5. */
#define s11 7
#define s12 12
#define s13 17
#define s14 22
#define s21 5
#define s22 9
#define s23 14
#define s24 20
#define s31 4
#define s32 11
#define s33 16
#define s34 23
#define s41 6
#define s42 10
#define s43 15
#define s44 21

/**
 * @Basic MD5 functions.
 *
 * @param there bit32.
 *
 * @return one bit32.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/**
 * @Rotate Left.
 *
 * @param {num} the raw number.
 *
 * @param {n} rotate left n.
 *
 * @return the number after rotated left.
 */
#define ROTATELEFT(num, n) (((num) << (n)) | ((num) >> (32 - (n))))

/**
 * @Transformations for rounds 1, 2, 3, and 4.
 */
#define FF(a, b, c, d, x, s, ac)            \
    {                                       \
        (a) += F((b), (c), (d)) + (x) + ac; \
        (a) = ROTATELEFT((a), (s));         \
        (a) += (b);                         \
    }
#define GG(a, b, c, d, x, s, ac)            \
    {                                       \
        (a) += G((b), (c), (d)) + (x) + ac; \
        (a) = ROTATELEFT((a), (s));         \
        (a) += (b);                         \
    }
#define HH(a, b, c, d, x, s, ac)            \
    {                                       \
        (a) += H((b), (c), (d)) + (x) + ac; \
        (a) = ROTATELEFT((a), (s));         \
        (a) += (b);                         \
    }
#define II(a, b, c, d, x, s, ac)            \
    {                                       \
        (a) += I((b), (c), (d)) + (x) + ac; \
        (a) = ROTATELEFT((a), (s));         \
        (a) += (b);                         \
    }

using std::string;

/* Define of byte.*/
typedef unsigned char byte;
/* Define of byte. */
typedef unsigned int bit32;

class MD5 {
  public:
    MD5(const string &message);

    /* 生成摘要信息 */
    const byte *getDigest();

    /* 转换摘要为string */
    string toStr();

  private:
    /* 初始化 MD5，
     */
    void init(const byte *input, size_t len);

    /* MD5 基本变换
     */
    void transform(const byte block[64]);

    /* 加密 输入 bit，输出 byte */
    void encode(const bit32 *input, byte *output, size_t length);

    /* 解密 */
    void decode(const byte *input, bit32 *output, size_t length);

  private:
    /* 是否完成计算 */
    bool finished;

    /* ABCD，4 组计算的状态 */
    bit32 state[4];

    /*  */
    bit32 count[2];

    /* 输入 buffer */
    byte buffer[64];

    /* 摘要信息 */
    byte digest[16];

    /* 全局对象，计算？ */
    static const byte PADDING[64];

    /* 全局对象，Hex numbers */
    static const char HEX_NUMBERS[16];
};

#endif