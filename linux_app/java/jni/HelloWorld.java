/**
 * 
 */
 package com.magc.jni;

 /**
 * @author magc
 *
 */
 public class HelloWorld {
    
    static {
        
        System.loadLibrary("Hello");
        
    }

    public     native void DisplayHello();
    /**
     * @param args
     */
    public static void main(String[] args) {

        new HelloWorld().DisplayHello();
    }

}