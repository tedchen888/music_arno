#include "pitches.h"
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int buzzer = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
   Serial.begin(9600);
}

/*
消防车： 以低频频率650Hz至750Hz，高频频率1450Hz至1550Hz， 由低频升至高频时间1.5秒，再由高频降至低频为3.5秒。
救护车： 以低频频率650Hz至750Hz，高频频率900z至1000Hz， 低频持续时间0.4秒，高频持续时间0.6秒，高低频交替进行。
警车： 以低频频率650Hz至750Hz，高频频率1450Hz至1550Hz， 由低频升至高频时间0.23秒，再由高频降至低频为0.1秒。
*/
bool is_120 = true;
unsigned long last_time = 0;
unsigned long now = 0;
unsigned long interval = 0;
bool is_high = true;
long play_low_time = 400000;
long play_high_time = 600000;

void play_120() {
  now = micros();
  interval = now - last_time;
  
  if (interval > 769) { //650Hz，每秒650次 1000000/650=1538/2=769
      digitalWrite(buzzer, is_high);
      is_high = is_high?false:true;
  }
  
  if (play_low_time > 0) { //低频
    if (interval > 769) { //650Hz，每秒650次 1000000/650=1538/2=769
      digitalWrite(buzzer, is_high);
      is_high = is_high?false:true;
    }
    play_low_time -= interval;
    play_high_time = 600000;
    Serial.println(now);
  } else if (play_high_time > 0) {
    if (interval > 344) { //1450Hz，每秒1450次 1000000/1450=689/2=344
      digitalWrite(buzzer, is_high);
      is_high = is_high?false:true;
    }
    play_low_time = 400000;
    play_high_time -= interval;
  }  
  last_time = now;
}

void loop() {

  play_120();
  
  // put your main code here, to run repeatedly:
  /*
    for (int i = 0; i<80; ++i)    {      
      digitalWrite(buzzer, HIGH);      
      delay(1);      
      digitalWrite(buzzer, LOW);      
      delay(1);   
    }   
    for (int i = 0; i<100; ++i)   {      
      digitalWrite(buzzer, HIGH);      
      delay(2);     
      digitalWrite(buzzer, LOW);      
      delay(2);    
    }*/
}
