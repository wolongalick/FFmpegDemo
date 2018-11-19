package com.alick.ffmpegdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.alick.ffmpeglibrary.FFmpegPlayer;

public class MainActivity extends AppCompatActivity {
    FFmpegPlayer fFmpegPlayer = new FFmpegPlayer();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        fFmpegPlayer.playMyMedia("https://blog.csdn.net/ywl5320");
        tv.setText("fffff");//ssssdfsf`wfwef
    }



    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which iswefwef  packaged with this application.sf
     */
//    public native String stringFromJNI();qwqwdqwdasdad
//qwdqqwd
    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }
}
