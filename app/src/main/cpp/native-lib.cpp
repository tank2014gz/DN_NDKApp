#include <jni.h>
#include <string>
#include <android/log.h>
#include <fmod.hpp>
#include <unistd.h>


#define LOG_TAG "dongran"
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


using namespace FMOD;
extern "C"
JNIEXPORT void JNICALL
Java_com_dr_dn_ndk_VoiceFix_fix(JNIEnv *env, jclass type, jint model, jstring voicePath_) {
    const char *voicePath = env->GetStringUTFChars(voicePath_, 0);
    //fmod系统环境
    System *system = 0;
    unsigned int version = 0;
    Sound *sound = 0;
    void *extradriverdata = 0;
    //音轨
    Channel *channel = 0;
    //DSP数字信号
    DSP *dsp;

//创建FMOD音频系统
    FMOD::System_Create(&system);
    system->getVersion(&version);
    if (version < FMOD_VERSION) {
        LOGE("ERROR %s", "FMOD lib version doesn't match header version");
    }
    LOGE("version %08x", version);

//初始化音频系统
    system->init(32, FMOD_INIT_NORMAL, extradriverdata);
//   初始化音频
    system->createSound(voicePath, FMOD_DEFAULT, 0, &sound);
//播放音频
    system->playSound(sound, 0, false, &channel);

    //添加音效
    switch (model) {
        case 0:
            //原声


            break;
        case 1:
            //萝莉  音调升高
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 1.8);//0.5-2.0...1.0
            channel->addDSP(0, dsp);
            break;
        case 2:
            //大叔  音调降低
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
            channel->addDSP(0, dsp);
            break;
        case 3:
            //惊悚  音调  回声，颤音
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 1.8);//0.5-2.0...1.0
            channel->addDSP(0, dsp);

            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);  //10--5000;  500
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 10); //0 --100
            channel->addDSP(1, dsp);


            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY, 8.0);  //10--5000;  500
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8); //0 --100
            channel->addDSP(2, dsp);

            break;
        case 4://搞怪  频率加快
            float frequency;
            channel->getFrequency(&frequency);
            channel->setFrequency(frequency * 1.5f);

            break;
        case 5://灵魂出窍
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);  //10--5000;  500
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 10); //0 --100
            channel->addDSP(0, dsp);
            break;

        default:
            break;


    }

//等声音播放完再释放
    bool isPlaying = true;

    while (isPlaying) {
        channel->isPlaying(&isPlaying);
        usleep(1000);
    }

    //释放资源
    sound->release();
    system->release();
    env->ReleaseStringUTFChars(voicePath_, voicePath);
}
