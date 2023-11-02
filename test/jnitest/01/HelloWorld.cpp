
#include "HelloWorld.h"

JNIEXPORT jstring JNICALL Java_HelloWorld_test(JNIEnv *env, jobject) {
    // 检查异常
    jthrowable exc = env->ExceptionOccurred();
    if (exc) {
        // 处理异常

        // 向java层抛出自定义异常
        env->ThrowNew(env->FindClass("java/lang/Exception"), "xx 异常");
        //清理异常
        env->ExceptionClear();
    }

    if (env->ExceptionCheck()) {
        env->ExceptionClear();
        env->ThrowNew(
            env->FindClass("java/lang/Exception"), "向java层抛出异常");
    }
    return env->NewStringUTF("返回成功");
}