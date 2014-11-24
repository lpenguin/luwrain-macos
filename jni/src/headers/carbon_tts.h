#include <exception>
#include <MacTypes.h>
#include <string>
#include <array>
#include <SpeechSynthesis.h>
#include <list>
#include <iostream>
#include <execinfo.h>
#include <vector>

using namespace std;

class OSException : public exception{
private:
    OSErr osErr;
    void* callstack[128];
    int frames;
    char** strs;

public:
    static void checkOSError(OSErr osErr) throw(OSException)
    {
        if(osErr != noErr) {
            throw OSException(osErr);
        }
    }

    OSException(OSErr osErr):osErr(osErr){
        frames = backtrace(callstack, 128);
        strs = backtrace_symbols(callstack, frames);
    }
    virtual const char* what() const throw() {
        return (string("OsErr exception, code: ")+ std::to_string(osErr)).c_str();
    }

    void printStacktrace(){
        for (int i = 0; i < frames; ++i) {
            cout<<strs[i]<<endl;
        }
    }
};

class CarbonTtsException : public exception{
public:
    CarbonTtsException(string message):message(message){}

    virtual const char* what() const throw() {
        return message.c_str();
    }
    
private:
     string message;
};



class CarbonTts {
public:
    CarbonTts() throw(OSException) {
        speechChannel = nullptr;
        loadVoices();
    }

    void loadVoices() throw(OSException);

    void createSpeechChannel(VoiceSpec voiceSpec) throw(OSException, CarbonTtsException);

    void createSpeechChannel(int i) throw(OSException, CarbonTtsException){
        createSpeechChannel(voices[i].voice);
    }

    void destroySpeechChannel() throw(OSException);

    void say(string text) throw(OSException);

    vector<VoiceDescription> getVoices() {
        return voices;
    };

    void disposeSpeechChannel() throw(OSException){
        if(speechChannel != nullptr){
            OSException::checkOSError(DisposeSpeechChannel(speechChannel));
        }
    }

    static void speechDoneCallback(SpeechChannel channel, long refConstant);

    static void speechTextDoneCallback(SpeechChannel channel, long refCon, void **nextBuf, unsigned long *byteLen, long *controlFlags);

    static void speechErrorCallback(SpeechChannel channel, long refConstant, CFErrorRef errorRef);

    ~CarbonTts(){
        disposeSpeechChannel();
    }

private:
    vector<VoiceDescription> voices;
    SpeechChannel speechChannel;


};