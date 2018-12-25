package com.alick.ffmpegdemo;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.alick.ffmpeglibrary.FFmpegPlayer;
import com.alick.ffmpeglibrary.FileUtils;
import com.alick.ffmpeglibrary.T;

import java.io.File;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button btn_readFile;
    private Button btn_readVideoFile;
    private Button btn_readVideoFile2;
    private Button btn_imoocBtn;
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
        btn_imoocBtn=findViewById(R.id.btn_imoocBtn);

        // Example of a call to a native method
//        fFmpegPlayer.playMyMedia("https://blog.csdn.net/ywl5320");

//        fFmpegPlayer.test("/storage/emulated/0/ddmsrec_1510054497477.mp4");
        fFmpegPlayer.test2("哈哈哈哈哈哈哈");
//        fFmpegPlayer.readFileContent("/storage/emulated/0/2017-11-07Log.txt");

//        tv_ffmepgConfigInfo.setText(fFmpegPlayer.getFFmpegConfigInfo());

        btn_readFile.setOnClickListener(this);
        btn_readVideoFile.setOnClickListener(this);
        btn_readVideoFile2.setOnClickListener(this);
        btn_imoocBtn.setOnClickListener(this);
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
                String s1 = fFmpegPlayer.readVideoFileInfo2("/storage/emulated/0/FFmpegDemo/src/台球.mp4");
                T.show(this,s1);
                break;
            case R.id.btn_imoocBtn:
                File file = new File(Environment.getExternalStorageDirectory() + File.separator + "FFmpegDemo", System.currentTimeMillis() + ".aac");

                boolean file1 = FileUtils.createFile(file);
                if(!file1){
                    T.show(this,"创建aac文件失败");
                    return;
                }
                String result = fFmpegPlayer.executeImoocDemo("/storage/emulated/0/FFmpegDemo/src/taiqiu.mp4", file.getAbsolutePath());
                T.show(this,result);
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
