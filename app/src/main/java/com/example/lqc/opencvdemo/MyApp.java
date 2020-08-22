package com.example.lqc.opencvdemo;

import android.app.Application;
import android.content.Context;

/**
 * Copyright (C), 2015-2019, suning
 * FileName: MyApp
 * Author: liuqiancheng
 * Date: 2019/6/3 17:42
 * Description:
 * Version: 1.0.0
 */
public class MyApp extends Application{

    private static MyApp mMyApp;

    @Override
    public void onCreate() {
        super.onCreate();
        mMyApp = this;
    }
    public static Context getAppContext(){
        return mMyApp;
    }
}
