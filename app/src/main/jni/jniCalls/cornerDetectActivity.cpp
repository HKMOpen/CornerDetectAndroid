/*
 *    Copyright 2016 Anand Muralidhar
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <jni.h>
#include "cornerClass.h"
#include "myJNIHelper.h"

#ifdef __cplusplus
extern "C" {
#endif

// global pointer is used in JNI calls to reference to same object of type Cube
CornerClass *gCornerObject =NULL;

// global pointer to instance of MyJNIHelper that is used to read from assets
MyJNIHelper * gHelperObject=NULL;

/**
 * Create the persistent native object and also initialize the single helper object
 */
JNIEXPORT void JNICALL
Java_com_anandmuralidhar_cornerdetectandroid_CornerDetectActivity_CreateObjectNative(JNIEnv *env,
                                                                                     jobject instance,
                                                                                     jobject assetManager,
                                                                                     jstring pathToInternalDir) {

    gHelperObject = new MyJNIHelper(env, instance, assetManager, pathToInternalDir);
    gCornerObject = new CornerClass();
}

JNIEXPORT void JNICALL
Java_com_anandmuralidhar_cornerdetectandroid_CornerDetectActivity_DeleteObjectNative(JNIEnv *env,
                                                                                     jobject instance) {
    if (gCornerObject != NULL) {
        delete gCornerObject;
    }
    gCornerObject = NULL;

    if (gHelperObject != NULL) {
        delete gHelperObject;
    }
    gHelperObject = NULL;
}

JNIEXPORT void JNICALL
Java_com_anandmuralidhar_cornerdetectandroid_CornerDetectActivity_SetCameraPreviewDimsNative(
        JNIEnv *env, jobject instance, jint previewWidth, jint previewHeight) {

    if (gCornerObject == NULL) {
        return;
    }
    gCornerObject->SetCameraPreviewDims((int) previewWidth, (int) previewHeight);
}

#ifdef __cplusplus
}
#endif
