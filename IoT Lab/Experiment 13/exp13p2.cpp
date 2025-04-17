#define LED_PIN 5 // GPIO5(D1 on NodeMCU)

void setup(){
    pinMode(LED_PIN, OUTPUT);
}
void loop(){
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
}