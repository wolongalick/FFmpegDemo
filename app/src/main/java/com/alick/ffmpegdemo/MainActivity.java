package com.alick.ffmpegdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.alick.ffmpeglibrary.FFmpegPlayer;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button btn_readFile;
    FFmpegPlayer fFmpegPlayer = new FFmpegPlayer();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn_readFile= (Button) findViewById(R.id.btn_readFile);

        // Example of a call to a native method
//        fFmpegPlayer.playMyMedia("https://blog.csdn.net/ywl5320");

        fFmpegPlayer.test("/storage/emulated/0/ddmsrec_1510054497477.mp4");
        fFmpegPlayer.test2("哈哈哈哈哈哈哈");

        btn_readFile.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_readFile:
                fFmpegPlayer.read("/storage/emulated/0/ddmsrec_1510054497477.mp4");
                break;
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which iswefwef  packaged with this application.sf
     */
//    public native String stringFromJNI();qwqwdqwdasdad
    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }
}
