package com.example.lqc.opencvdemo;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    static final String TAG = "FACE";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private Bitmap bitmap;
    private File mMCascadeFile;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_basic_operation).setOnClickListener(this);
        findViewById(R.id.btn_segmentation).setOnClickListener(this);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native Bitmap faceInfo(Bitmap bitmap);

    public native Bitmap faceDetection(Bitmap bitmap);

    public native Bitmap hogFaceDetection(Bitmap bitmap);

    public native void initCascadeClassifier(String path);

    public native Bitmap houghTest(Bitmap bitmap);


    public void copy() {
        try {
            InputStream is = getResources().openRawResource(R.raw.lbpcascade_frontalface);
            File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
            mMCascadeFile = new File(cascadeDir, "lbpcascade_frontalface.xml");
            FileOutputStream os = new FileOutputStream(mMCascadeFile);

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = is.read(buffer)) != -1) {
                os.write(buffer, 0, bytesRead);
            }
            os.flush();
            is.close();
            os.close();
            Log.d(TAG, "file copy success");
            initCascadeClassifier(mMCascadeFile.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_basic_operation:
                startActivity(new Intent(this,BasicOperationActivity.class));
                break;
            case R.id.btn_segmentation:
                startActivity(new Intent(this,ImageCutActivity.class));
                break;
        }
    }
}
