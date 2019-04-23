package com.dr.dn.ndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import org.fmod.FMOD;

public class MainActivity extends AppCompatActivity {
    
    private String mVoicePath;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mVoicePath = "file:///android_asset/loveSelf.mp3";
        FMOD.init(this.getApplication());
    }
    
    
    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }
    
    public void onFix(View view) {
        switch (view.getId()) {
            case R.id.image1:
                VoiceFix.fix(VoiceFix.MODE_NORMAL, mVoicePath);
                break;
            case R.id.image2:
                VoiceFix.fix(VoiceFix.MODE_LUOLI, mVoicePath);
                break;
            case R.id.image3:
                VoiceFix.fix(VoiceFix.MODE_AUNCALL, mVoicePath);
                break;
            case R.id.image4:
                VoiceFix.fix(VoiceFix.MODE_JINGSONG, mVoicePath);
                break;
            case R.id.image5:
                VoiceFix.fix(VoiceFix.MODE_GAOXIAO, mVoicePath);
                break;
            case R.id.image6:
                VoiceFix.fix(VoiceFix.MODE_LINGHUNCHUQIAO, mVoicePath);
                break;
        }
    }
}
