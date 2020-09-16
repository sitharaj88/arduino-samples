const char LED = 13;

void setup() {
  //make pin 13 as output
  pinMode(LED, OUTPUT); 
}

void loop() {
  //LED "ON"
  digitalWrite(LED, HIGH);
  //wait 1 sec
  delay(1000);
  //LED "OFF"
  digitalWrite(LED, LOW);
  //wait 1 sec
  delay(1000);
}
