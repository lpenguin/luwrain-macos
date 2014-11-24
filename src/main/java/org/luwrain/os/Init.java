package org.luwrain.os;

import org.luwrain.os.speech.CarbonTts;
import org.luwrain.os.speech.VoiceDescription;

import java.util.Scanner;

public class Init {

    public static int readVoiceIndex(CarbonTts talker) {
        VoiceDescription[] voices = talker.getVoices();
        for (int i = 0; i < voices.length; i++) {
            VoiceDescription voice = voices[i];
            System.out.printf("#%d %s - @%d\n", i + 1, voice.name, voice.region);
        }
        System.out.printf("Type voice number: ");
        return new Scanner(System.in).nextInt() - 1;
    }

    public static void init() {
        System.loadLibrary("luwrainlinux");
    }

    public static void main(String[] args) {
        SpeechBackEnd talker = SpeechBackEnds.obtain(null, null, 0);//new MacCarbonTTS();
//        talker.createChannel(readVoiceIndex(talker));
        Scanner scanner = new Scanner(System.in);
        String text = null;
        while(!"exit".equals(text)) {
            System.out.printf("Type text: ");
            text = scanner.nextLine();
            talker.say(text);
        }
        //talker.dispose();
//        init();
//        try {
//            Terminal t = new Terminal();
//            t.open("date");
//            t.getLineCount();
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
    }
}
