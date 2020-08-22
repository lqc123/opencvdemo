package com.example.lqc.opencvdemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageView;

/**
 * 位图基本运算
 */
public class BasicOperationActivity extends AppCompatActivity implements View.OnClickListener {

    private ImageView mIvCombinat;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_basic_operation);
        findViewById(R.id.btn_add).setOnClickListener(this);
        findViewById(R.id.btn_sub).setOnClickListener(this);
        mIvCombinat = findViewById(R.id.iv_combinat);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_add:
                Bitmap bitmap = addOperation(BitmapFactory.decodeResource(getResources(), R.mipmap.ic_test2), BitmapFactory.decodeResource(getResources(), R.mipmap.ic_test3));
                mIvCombinat.setImageBitmap(bitmap);
                break;
            case R.id.btn_sub:
                Bitmap bitmap2 = subOperation(BitmapFactory.decodeResource(getResources(), R.mipmap.ic_test2), BitmapFactory.decodeResource(getResources(), R.mipmap.ic_test3));
                mIvCombinat.setImageBitmap(bitmap2);
                break;
        }
    }



    public native Bitmap addOperation(Bitmap bitmap, Bitmap bitmap1);
    public native Bitmap subOperation(Bitmap bitmap, Bitmap bitmap1);
}
