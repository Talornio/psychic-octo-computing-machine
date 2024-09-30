#include <pthread.h> //libreria di tipo preemptive

pthread_t t1;
pthread_t t2;
int delayt ;
bool blink1_running = true;
bool blink2_running = true;
int led1 = 13;
int led2 = 12;

void * blink1(void * d)
{
    while(blink1_running){
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
    }
    digitalWrite(led1, LOW);
}

void * blink2(void * d)
{
    while(blink2_running){
      digitalWrite(led2, HIGH);
      delay(1000);
      digitalWrite(led2, LOW);
      delay(1000);
    }
    digitalWrite(led2, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  delayt = 500;
  if (pthread_create(&t1, NULL, blink1, (void *)delay)) {
         Serial.println("Errore crezione thread 1");
  }
  delayt = 1000;
  if (pthread_create(&t2, NULL, blink2, (void *)delay)) {
         Serial.println("Errore crezione thread 2");
  } 
}

void loop() {
  int count = 0;
  while(true){
    Serial.print("Doing stuff... ");
    Serial.println(count);
    count += 1;
    if(count >= 10)
      break;
    delay(1000);
  }
  Serial.print("Ending threads...");
  blink1_running = false;
  blink2_running = false;
}
