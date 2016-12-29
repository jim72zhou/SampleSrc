// JNIHello.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"

#include <iostream>

#include "jni_JNIHello.h"

JNIEXPORT void JNICALL Java_jni_JNIHello_sayHello (JNIEnv * env, jobject obj)  
{  
	std::cout<<"Hello World"<<std::endl;  
}


JNIEXPORT jint JNICALL Java_jni_JNIHello_plusInteger(JNIEnv *, jobject, jint a, jint b)
{
	return a + b;
}

