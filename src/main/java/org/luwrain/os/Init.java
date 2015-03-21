package org.luwrain.os;

import org.luwrain.macos.Macos;
import org.luwrain.macos.speech.CarbonTts;
import org.luwrain.macos.speech.VoiceDescription;

import java.util.Scanner;

public class Init {

//    public static String readVoiceName(CarbonTts talker) {
//        VoiceDescription[] voices = talker.getVoices();
//        for (int i = 0; i < voices.length; i++) {
//            VoiceDescription voice = voices[i];
//            System.out.printf("#%d %s - @%d\n", i + 1, voice.name, voice.region);
//        }
//        System.out.printf("Type voice number: ");
//        int index =  new Scanner(System.in).nextInt() - 1;
//        if(index < 0 || index >= voices.length){
//            throw new IllegalStateException("Invalid voice index!");
//        }
//        return voices[index].name;
//    }

    public static void main(String[] args) {
        Macos os = new Macos();
        os.init();
        CarbonTts talker = new CarbonTts();
//        String name = readVoiceName(talker);
        talker.init(new String[]{CarbonTts.SPEECH_VOICE_NAME+"Bahh"});
//        int voiceIndex = readVoiceIndex(talker);
//        talker.createChannel(voiceIndex);
        Scanner scanner = new Scanner(System.in);
        String text = null;
        while(!"exit".equals(text)) {
            System.out.printf("Type text: ");
            text = scanner.nextLine();
            talker.say(text);
        }
        talker.dispose();
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
