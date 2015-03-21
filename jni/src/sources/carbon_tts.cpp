#include "carbon_tts.h"

#include <objc/objc.h>

using namespace std;

CFStringRef fromString(string s){
    return CFStringCreateWithBytes(kCFAllocatorDefault, (UInt8 const *) s.c_str(), s.size(), kCFStringEncodingUTF8, YES);
}

CFNumberRef createSpeechDoneCallback(){
    void (*callbackPointer)(SpeechChannel, long);
    callbackPointer = &CarbonTts::speechDoneCallback;
    return CFNumberCreate(NULL, kCFNumberLongType, &callbackPointer);
}

CFNumberRef createSpeechErrorCallback(){
    void (*calbackPointer)(SpeechChannel, long, CFErrorRef);
    calbackPointer = &CarbonTts::speechErrorCallback;
    return CFNumberCreate(NULL, kCFNumberLongType, &calbackPointer);
}

void CarbonTts::loadVoices() throw(OSException){
    SInt16 voicesCount;
    VoiceSpec voiceSpec; /* VoiceSpec is a structure that contains the identity of the synthesizer required to use a voice and the ID of a voice. */

    OSException::checkOSError(CountVoices(&voicesCount)); // Handle error if necessary.
    voices.reserve(voicesCount);
    for (SInt16 voiceIndex = 1; voiceIndex <= voicesCount; voiceIndex++) {
        VoiceDescription voiceDesc;
        OSException::checkOSError(GetIndVoice(voiceIndex, &voiceSpec)); // Handle error if necessary.
        OSException::checkOSError(GetVoiceDescription(&voiceSpec, &voiceDesc, sizeof(voiceDesc))); // Handle error if necessary.
        voices.push_back(voiceDesc);
    }

    cout<<"Loaded voices: "<<voices.size()<<endl;
}


void CarbonTts::say(string text) throw(OSException){
    CFStringRef str = fromString(text);
    OSException::checkOSError(
            SpeakCFString(speechChannel, str, NULL)
    );
}

void CarbonTts::createSpeechChannel(VoiceSpec voiceSpec) throw(OSException, CarbonTtsException){
    if(speechChannel != nullptr){
        cerr<<"Speech channel already created!"<<endl;
        throw new CarbonTtsException("Speech channel already created");
    }

    OSException::checkOSError(NewSpeechChannel(&voiceSpec, &speechChannel));



    CarbonTts * pThis= this;
    CFNumberRef thisRef = CFNumberCreate(NULL, kCFNumberLongType, &pThis);

    OSException::checkOSError(
            SetSpeechProperty(speechChannel, kSpeechRefConProperty, thisRef)
    );

    OSException::checkOSError(
            SetSpeechProperty(speechChannel, kSpeechSpeechDoneCallBack, createSpeechDoneCallback())
    );
}

void CarbonTts::destroySpeechChannel() throw(OSException){
    OSException::checkOSError(DisposeSpeechChannel(speechChannel));
}

void CarbonTts::speechDoneCallback(SpeechChannel channel, long refConstant) {
    cout<<"Speech done. channel: "<<channel<<endl;
    CarbonTts * thisRef = (CarbonTts *)refConstant;

}

void CarbonTts::speechTextDoneCallback(SpeechChannel channel, long refCon, void **nextBuf, unsigned long *byteLen, long *controlFlags) {

}

void CarbonTts::speechErrorCallback(SpeechChannel channel, long refConstant, CFErrorRef errorRef) {

}
