#include "carbon_tts.h"

VoiceDescription chooseVoiceDescription(const vector<VoiceDescription>& voices);
string readInputText();

int main(int argc, char** argv){
    try{
        CarbonTts talker;
        cout<<"Getting voices list"<<endl;

        cout<<"Creating speech channel"<<endl;
        talker.createSpeechChannel(chooseVoiceDescription(talker.getVoices()).voice);
        cout<<"Type text: "<<endl;
        string text = readInputText();
        cout<<"Trying to say"<<endl;
        talker.say(text);
        sleep(1000);
        talker.destroySpeechChannel();
        cout<<"Bye!"<<endl;
    }catch(OSException& ex){
        cout<<"Exception: "<<ex.what()<<endl;
        ex.printStacktrace();
    }catch(CarbonTtsException & ex){
        cout<<"CarbonTts exception: "<<ex.what()<<endl;
    }


}

VoiceDescription chooseVoiceDescription(const vector<VoiceDescription>& voices){
//    return voices.front();
    cout<<"Availible voices: "<<endl;
    int i = 0;
    for(VoiceDescription description: voices){
        cout<<"#"<<i<<" "<<description.name<<" (region "<<description.region<<")"<<endl;
        i++;
    }
    int index;
    cout<<"Choose voice #";
    cin>>index;
    return voices[index];

}

string readInputText(){
    string line;
//    getline(cin, line);
    cin>>line;
    return line;
}