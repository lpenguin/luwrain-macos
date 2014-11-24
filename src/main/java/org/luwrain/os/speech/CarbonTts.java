package org.luwrain.os.speech;

import org.luwrain.os.SpeechBackEnd;

/**
 * Created by nikita on 02.10.14.
 */
public class CarbonTts implements SpeechBackEnd {
    static {
        System.loadLibrary("luwrainMacOs");
    }

    public CarbonTts(){
        native_initialize();
    }

    @Override
    public void say(String text){
        System.out.printf("say() text: "+text+"\n");
        native_say(text);
    }

    @Override
    public void sayLetter(char letter) {
        System.out.printf("[NOOP] sayLetter() letter: " + letter + "\n");
    }

    @Override
    public void silence() {
        System.out.printf("[NOOP] silence()\n");
    }

    @Override
    public void setPitch(int value) {
        System.out.printf("[NOOP] setPitch() value: "+value+"\n");
    }

    public void createChannel(String voiceName){
        VoiceDescription[] voices = getVoices();
        for (int i = 0; i < voices.length; i++) {
            if(voices[i].name.equals(voiceName)){
                createChannel(i);
                return;
            }
        }
        throw new IllegalStateException("Voice not found for name: "+voiceName);
    }

    public void createChannel(int voiceIndex){
        native_createChannel(voiceIndex);
    }

    public VoiceDescription[] getVoices(){
        return native_getVoices();
    }

    @Override
    protected void finalize() throws Throwable {
        dispose();
    }

    private long nativeHandle;

    public native void dispose();

    private native void native_createChannel(int voiceIndex);

    private native void native_say(String text);

    private native void native_initialize();

    private native VoiceDescription[] native_getVoices();
}
