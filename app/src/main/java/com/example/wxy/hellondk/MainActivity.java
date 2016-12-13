package com.example.wxy.hellondk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private byte[]bytes;
    private TextView text;
    private TextView textView1;
    static {
        System.loadLibrary("hello-jni");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        text= (TextView) findViewById(R.id.text);
        textView1= (TextView) findViewById(R.id.text1);
        bytes=encryptBase64("wxy".getBytes());
        text.setText(new String(bytes));
        decryptBase64(bytes);
        textView1.setText(new String(decryptBase64(bytes)));
    }

    public native byte[] encryptBase64(byte[] bytes);
    public native byte[] decryptBase64(byte[] bytes);

}
