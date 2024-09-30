int buttonState = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  pinMode(34, INPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  // read the state of the pushbutton value
  buttonState = digitalRead(34);
  // check if pushbutton is pressed.  if it is, the
  // buttonState is HIGH
  if (buttonState == HIGH) {
    // turn LED on
    digitalWrite(12, HIGH);
    Serial.println(1);
    delay(200);
  } else {
    // turn LED off
    digitalWrite(12, LOW);
    Serial.println(0);
    delay(200);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
