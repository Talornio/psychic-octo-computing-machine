#include <pthread.h>

pthread_t t1;
pthread_t t2;

const byte led1 = 13;
const byte button = 25;

byte led_state = LOW;
byte current_button_state;
byte last_button_state;
const unsigned long tbase = 100;
unsigned long precm = 0;
int delayt;

void * SerialInputThread(void * d){
  int time = (int) d;
  while(true){
    if(millis() - precm >= tbase){
      if(Serial.available()){
      String input_string = Serial.readString();
      Serial.println(input_string);
      if(input_string.indexOf("accendi")>=0){
        digitalWrite(led1, HIGH);
      }
      if(input_string.indexOf("spegni")>=0){
        digitalWrite(led1, LOW);
      }
      }
      //Serial.print(precm);
    }
    delay(time);
  }
  return NULL;
}

void * ToggleButtonThread(void * d){
  int time = (int)d;
  while(true){
    if((millis() - precm) >= tbase){
      precm = millis();
      last_button_state = current_button_state;
      current_button_state = digitalRead(button);
      if(last_button_state == HIGH && current_button_state == LOW) {
      led_state = !led_state;
      digitalWrite(led1, led_state); 
      //Serial.print(precm);
      }
    }
    delay(time);
  }
  return NULL;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(button, INPUT);
  delayt = 500;
  if(pthread_create(&t1, NULL, SerialInputThread, (void *)delayt)){
    Serial.println("Errore creazione thread 1"); 
  }
  if(pthread_create(&t2, NULL, ToggleButtonThread, (void *)delayt)){
    Serial.println("Errore creazione thread 2"); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
