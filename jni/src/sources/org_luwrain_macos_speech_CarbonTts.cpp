#include "org_luwrain_macos_speech_CarbonTts.h"
#include "carbon_tts.h"
#include "handle.h"



using namespace std;

void Java_org_luwrain_macos_speech_CarbonTts_native_1initialize(JNIEnv *env, jobject obj) {
    cout<<"Java_org_luwrain_macos_speech_CarbonTts_native_1initialize"<<endl;
    CarbonTts * talker = new CarbonTts();
    setHandle(env, obj, talker);
}

void Java_org_luwrain_macos_speech_CarbonTts_native_1say(JNIEnv *env, jobject obj, jstring jtext) {
    cout<<"Java_org_luwrain_macos_speech_CarbonTts_native_1say"<<endl;
    const char *text = env->GetStringUTFChars(jtext, 0);
    cout<<"Say() text: "<<text<<endl;
    getHandle<CarbonTts>(env, obj)->say(text);
}

void Java_org_luwrain_macos_speech_CarbonTts_native_1createChannel(JNIEnv *env, jobject obj, jint channelIndex) {
    cout<<"Java_org_luwrain_macos_speech_CarbonTts_native_1createChannel() channelIndex: "<<channelIndex<<endl;
    getHandle<CarbonTts>(env, obj)->createSpeechChannel(channelIndex);
}

char* Str63tocstr(Str63 str){
    unsigned char len = str[0];
    char* result = new char[len+1];
    strncpy(result, (char*)(str+1), len);
    result[len] = '\0';
    return result;
}

jobjectArray Java_org_luwrain_macos_speech_CarbonTts_native_1getVoices(JNIEnv *env, jobject obj) {
    cout<<"Java_org_luwrain_macos_speech_CarbonTts_native_1getVoices"<<endl;
    jclass voiceDescClass = env->FindClass("org/luwrain/macos/speech/VoiceDescription");
    cout<<"Found class: "<<voiceDescClass<<endl;
    jmethodID ctorId = env->GetMethodID(voiceDescClass, "<init>", "(Ljava/lang/String;I)V");
    cout<<"with ctorId: "<<ctorId<<endl;
    CarbonTts * talker = getHandle<CarbonTts>(env, obj);
    vector<VoiceDescription> voices = talker->getVoices();
    jobjectArray res = env->NewObjectArray(voices.size(), voiceDescClass, nullptr);
    for(int i = 0 ; i < voices.size(); i++){
        VoiceDescription voice = voices[i];

        jobject item = env->NewObject(voiceDescClass, ctorId, env->NewStringUTF(Str63tocstr(voice.name)), voice.region);
        env->SetObjectArrayElement(res, i, item);
    }

    return res;
}

void Java_org_luwrain_macos_speech_CarbonTts_dispose(JNIEnv *env, jobject obj) {
    cout<<"Java_org_luwrain_macos_speech_CarbonTts_dispose"<<endl;
    CarbonTts * talker = getHandle<CarbonTts>(env, obj);
    setHandle<CarbonTts>(env, obj, nullptr);
    delete talker;
}
