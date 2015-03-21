package org.luwrain.macos.speech;

import org.luwrain.speech.BackEnd;

import java.util.Arrays;

/**
 * Created by nikita on 02.10.14.
 * org.luwrain.macos.speech.CarbonTts
 */
public class CarbonTts implements BackEnd {
    public static final String SPEECH_VOICE_NAME = "--speech:voice=";
    @Override
    public String init(String[] cmdLine) {
        System.out.printf("init() cmdLine: "+Arrays.toString(cmdLine) +"\n");

        native_initialize();

        String name;
        if(cmdLine.length == 0 || (name = readVoiceNameFromCommandLine(cmdLine)) == null) {
            System.out.println("init() voice name not found in command line args. Using default voice");
            createChannel(0);
        }else{
            createChannel(name);
        }
        return null;
    }

    private static String readVoiceNameFromCommandLine(String[] commandLine){
        for(String arg: commandLine){
            if(arg.startsWith(SPEECH_VOICE_NAME)){
                return arg.replaceFirst(SPEECH_VOICE_NAME, "");
            }
        }
        return null;
    }

    @Override
    public void say(String text){
        System.out.printf("say() text: "+text+"\n");
        native_say(text);
    }

    @Override
    public void say(String text, int pitch) {
        // FIXME: поддерживать параметр pitch
        System.out.printf("say() text: "+text+", pitch: "+pitch+"" +
                ", using default implementation say(String)" +
                "\n");
        say(text);
    }

    @Override
    public void say(String text, int pitch, int rate) {
        // FIXME: поддерживать параметры pitch, rate
        System.out.printf("say() text: "+text+", pitch: "+pitch+", rate:"+rate+
                    ", using default implementation say(String)" +
                    "\n");
        say(text);
    }

    @Override
    public void sayLetter(char letter) {
        // FIXME: сделать имплементацию напрямую через MacOS text-to-speech
        System.out.printf("sayLetter() letter: " + letter + "\n");
        say(letter+"");
    }

    @Override
    public void sayLetter(char letter, int pitch) {
        // FIXME: поддерживать параметр pitch
        System.out.printf("sayLetter() letter: "+letter+", pitch: "+pitch+"\n");
        sayLetter(letter);
    }

    @Override
    public void sayLetter(char letter, int pitch, int rate) {
        // FIXME: поддерживать параметры pitch, rate
        System.out.printf("sayLetter() letter: "+letter+", pitch: "+pitch+", rate: "+rate+"\n");
        sayLetter(letter);
    }

    @Override
    public void silence() {
        System.out.printf("[NOOP] silence()\n");
    }

    @Override
    public void setDefaultPitch(int i) {
        System.out.printf("[NOOP] setDefaultRate() value: "+i+"\n");
    }

    @Override
    public void setDefaultRate(int i) {
        System.out.printf("[NOOP] setDefaultRate() value: "+i+"\n");
    }

    public void createChannel(String voiceName){
        // FIXME: не загружать голоса при каждом вызове createChannel(String )
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

    protected VoiceDescription[] getVoices(){
        return native_getVoices();
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        dispose();
    }

    private long nativeHandle;

    public native void dispose();

    private native void native_createChannel(int voiceIndex);

    private native void native_say(String text);

    private native void native_initialize();

    private native VoiceDescription[] native_getVoices();
}
