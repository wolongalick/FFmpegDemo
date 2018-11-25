package com.alick.ffmpegdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.alick.ffmpeglibrary.FFmpegPlayer;
import com.alick.ffmpeglibrary.T;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button btn_readFile;
    private Button btn_readVideoFile;
    private Button btn_readVideoFile2;
    private TextView tv_ffmepgConfigInfo;
    FFmpegPlayer fFmpegPlayer = new FFmpegPlayer();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn_readFile= findViewById(R.id.btn_readTextFile);
        btn_readVideoFile= findViewById(R.id.btn_readVideoFile);
        btn_readVideoFile2= findViewById(R.id.btn_readVideoFile2);
        tv_ffmepgConfigInfo=findViewById(R.id.tv_ffmepgConfigInfo);

        // Example of a call to a native method
//        fFmpegPlayer.playMyMedia("https://blog.csdn.net/ywl5320");

//        fFmpegPlayer.test("/storage/emulated/0/ddmsrec_1510054497477.mp4");
        fFmpegPlayer.test2("哈哈哈哈哈哈哈");
//        fFmpegPlayer.readFileContent("/storage/emulated/0/2017-11-07Log.txt");

//        tv_ffmepgConfigInfo.setText(fFmpegPlayer.getFFmpegConfigInfo());

        btn_readFile.setOnClickListener(this);
        btn_readVideoFile.setOnClickListener(this);
        btn_readVideoFile2.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_readTextFile:
                fFmpegPlayer.read("/storage/emulated/0/ddmsrec_1510054497477.mp4");
                break;
            case R.id.btn_readVideoFile:
                String s = fFmpegPlayer.readVideoFileInfo("/storage/emulated/0/DCIM/Camera/VID_20181130_140540.mp4");
                T.show(this,s);
                break;
            case R.id.btn_readVideoFile2:
                String s1 = fFmpegPlayer.readVideoFileInfo2("/storage/emulated/0/DCIM/Camera/VID_20181130_140540.mp4");
                T.show(this,s1);
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
