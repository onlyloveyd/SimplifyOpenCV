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
    jint *input;
    input = env->GetIntArrayElements(source, JNI_FALSE);

    Mat sourceMat(height, width, CV_8UC4, (unsigned char *) input);

    Mat grayMat;
    cvtColor(sourceMat, grayMat, CV_BGRA2GRAY);

    Mat resultMat;
    cvtColor(grayMat, resultMat, CV_GRAY2BGRA);
    int size = width * height;
    jintArray result = env->NewIntArray(size);
    uchar *output = resultMat.data;
    env->SetIntArrayRegion(result, 0, size, (const jint *) output);
    env->ReleaseIntArrayElements(source, input, 0);
    return result;
}