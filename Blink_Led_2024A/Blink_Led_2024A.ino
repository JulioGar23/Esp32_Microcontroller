//Code by: Julio A. García-Rodríguez.

int test_led = 2;  

void setup() {
  pinMode(test_led, OUTPUT);     //configuration through pinMode function.
  digitalWrite(test_led, HIGH);   //initial state. 
}

void loop() {
  digitalWrite(test_led, HIGH);
  delay(2000);
  digitalWrite(test_led, LOW);
  delay(500);
}
