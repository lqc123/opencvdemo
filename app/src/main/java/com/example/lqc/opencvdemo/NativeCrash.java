package com.example.lqc.opencvdemo;

import android.util.Log;

/**
 * Copyright (C), 2015-2019, suning
 * FileName: Test
 * Author: liuqiancheng
 * Date: 2019/8/18 14:29
 * Description:
 * Version: 1.0.0
 */
public class NativeCrash {
    public void onNativeCrashed() {
        Log.e("crash", "onNativeCrashed");
    }

    public native int nativeRegisterHandler();

    public native void nativeMakeError();
}
