static uint8_t taskCore0 = 0;
static uint8_t taskCore1 = 1;
bool blink1_running = true;
bool blink2_running = true;
int led1 = 13;
int led2 = 12;
 
void blink1(void * parameter){
  String taskMessage = "Task running on core ";
      taskMessage = taskMessage + xPortGetCoreID();
  //loop del thread (interrompibile dal loop principale)
  while(blink1_running){
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    delay(500);
    Serial.println(taskMessage);
  }
  //se il flag è negato arriva quà
        digitalWrite(led1, LOW);
        // spegne il led e poi termina (su comando del loop())
}

void blink2(void * parameter){
  String taskMessage = "Task running on core ";
      taskMessage = taskMessage + xPortGetCoreID();
  //loop del thread (interrompibile dal loop principale)
  while(blink2_running){
    digitalWrite(led2, HIGH);
    delay(1000);
    digitalWrite(led2, LOW);
    delay(1000);
    Serial.println(taskMessage);
  }
  //se il flag è negato arriva quà
        digitalWrite(led2, LOW);
        // spegne il led e poi termina (su comando del loop())
}
 
void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  Serial.print("Starting to create task on core ");
  Serial.println(taskCore0);
  xTaskCreatePinnedToCore(
                    blink1,   /* Function to implement the task */
                    "blink1", /* Name of the task */
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    0,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    taskCore0);  /* Core where the task should run */
   Serial.println("Task created...");
   delay(500);
   Serial.print("Starting to create task on core ");
   Serial.println(taskCore1);
   xTaskCreatePinnedToCore(
                    blink2,   /* Function to implement the task */
                    "blink2", /* Name of the task */
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    0,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    taskCore1);  /* Core where the task should run */
  Serial.println("Task created...");
}
 
void loop() {
  int count = 0;
  while(count < 10){
    Serial.print("Faccio qualcosa... ");
    Serial.println(count);
    count += 1;
    delay(1000);
  }
  Serial.print("Termino il threads...");
  // interrompe i loop di tutti i thread
  blink1_running = false;
  blink2_running = false;
}
