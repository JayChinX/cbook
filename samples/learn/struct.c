#include <stdlib.h>
#include <stdio.h>

// 创建结构体
struct Student {
    int age;
    char sex;
    float score;
};

int main(int argc, char const *argv[]) {
    // 创建结构体变量
    struct Student stu = {16, 'F', 80.0f}; // 初始化并赋值

    struct Student stu2; // 初始化
    stu2.age = 16;       // 赋值
    stu2.sex = 'X';
    stu2.score = 90.0f;
    printf("输出：age: %d, sex: %c, score: %f \n", stu.age, stu.sex, stu.score);
    printf("age: %d, sex: %c, score: %f \n", stu2.age, stu2.sex, stu2.score);

    struct Student *stuP = &stu;
    printf("age: %d, sex: %c, score: %f \n", stuP->age, stuP->sex, stuP->score);

    return 0;
}
