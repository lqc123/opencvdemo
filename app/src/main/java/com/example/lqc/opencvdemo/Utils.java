package com.example.lqc.opencvdemo;

import android.graphics.Bitmap;

/**
 * Copyright (C), 2015-2019, suning
 * FileName: Utils
 * Author: liuqiancheng
 * Date: 2019/6/3 17:40
 * Description:
 * Version: 1.0.0
 */
public class Utils {
    public static Object createBitmap(){
       return Bitmap.createBitmap(dp2sp(200), dp2sp(100), Bitmap.Config.ARGB_4444);
    }
    public static int dp2sp(int dp){
        float density = MyApp.getAppContext().getResources().getDisplayMetrics().density;
        return (int) (dp*density+0.5);
    }
}
