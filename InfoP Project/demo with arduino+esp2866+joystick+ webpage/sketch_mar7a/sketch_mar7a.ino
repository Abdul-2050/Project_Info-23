
#define joyX A0
#define joyY A1


void setup() {
  Serial.begin(115200);  // Initialize Serial Communication
}

void loop() {

  // put your main code here, to run repeatedly:

  int xValue = analogRead(joyX);   // Data to be send 
  int yValue = analogRead(joyY);  // Data to be sent

  Serial.println(yValue);            // Send data over Serial
  delay(50);
}
