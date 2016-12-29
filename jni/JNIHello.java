package jni;

// about detail step, refer
// http://blog.csdn.net/jiangwei0910410003/article/details/17465085
// http://blog.csdn.net/banketree/article/details/40535325

public class JNIHello {  
    // Define a native method 
    public native void sayHello();
    public native int plusInteger(int a, int b);
    public static void main(String[] args){  
        // invoke dynamic library
        System.loadLibrary("JNIHello");  
        JNIHello jniDemo = new JNIHello();  
        jniDemo.sayHello();
        System.out.println("1 + 2 = " + jniDemo.plusInteger(1, 2));
    }  
}
 