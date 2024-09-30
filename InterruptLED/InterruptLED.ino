const byte LED = 14;
const byte BUTTON = 27;

// Interrupt Service Routine (ISR)
void switchPressed ()
{
  if (digitalRead(BUTTON) == HIGH)
    digitalWrite (LED, HIGH);
  else
    digitalWrite(LED, LOW);
}  // end of switchPressed

void setup ()
{
  pinMode(LED, OUTPUT);      // so we can update the LED
  digitalWrite(BUTTON, HIGH);  // internal pull-up resistor
  // attach interrupt handler
  attachInterrupt(digitalPinToInterrupt(BUTTON), switchPressed, CHANGE);  
  
}  // end of setup

void loop ()
{
  // loop doing nothing 
} 
