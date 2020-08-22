package com.example.lqc.opencvdemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

public class ImageCutActivity extends AppCompatActivity implements View.OnClickListener {

    private SurfaceView mSvDest;
    private Surface mSurface;
    private Bitmap mBitmap;
    private ImageView mIvDst;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_cut);
        mBitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.ic_test2);

        mSvDest = findViewById(R.id.sv_dst);
        mIvDst = findViewById(R.id.iv_dst);
        ViewGroup.LayoutParams layoutParams = mSvDest.getLayoutParams();
        layoutParams.height=mBitmap.getHeight();
        layoutParams.width=mBitmap.getWidth();
        mSvDest.setLayoutParams(layoutParams);
        mSvDest.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                mSurface = holder.getSurface();
            }

            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {

            }
        });
        findViewById(R.id.btn_floodFill).setOnClickListener(this);
        findViewById(R.id.btn_grabCut).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if(mSurface==null){
            return;
        }
        if(v.getId()==R.id.btn_grabCut){
            mIvDst.setImageBitmap(grabCut(mBitmap,mBitmap.getConfig()));
        }else {
            floodFill(mBitmap,mSurface);
        }
    }

    /**
     * 漫水填充
     * @param bitmap
     * @param surface
     */
    private native void floodFill(Bitmap bitmap, Surface surface);

    /**
     * GrabCut图像分割算法
     * @return
     */
    public  native Bitmap grabCut(Bitmap bitmap, Bitmap.Config config);
}
