#include <jni.h>
#include <string>
#include "include/opencv2/core/hal/interface.h"
#include "include/opencv2/imgproc/types_c.h"
#include "include/opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

extern "C" JNIEXPORT jintArray  JNICALL
Java_tech_kicky_simplifyopencv_MainActivity_doGray(
        JNIEnv *env, jobject thiz, jintArray source,
        jint width, jint height) {
    // TODO: implement convertToGray()
    jint *cbuf;
    cbuf = env->GetIntArrayElements(source, JNI_FALSE);

    Mat inp_img(height, width, CV_8UC4, (unsigned char *) cbuf);

    Mat gray_img;
    cvtColor(inp_img, gray_img, CV_BGRA2GRAY);

    Mat ret_img;
    cvtColor(gray_img, ret_img, CV_GRAY2BGRA);
    int size = width * height;
    jintArray result = env->NewIntArray(size);
    uchar *ptr = ret_img.data;
    env->SetIntArrayRegion(result, 0, size, (const jint *) ptr);
    env->ReleaseIntArrayElements(source, cbuf, 0);
    return result;
}