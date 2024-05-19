const int LEDs[] = {2,3};
int j = 0;
int pirState = LOW;
int val = 0;

void setup() {

pinMode(8, INPUT);
Serial.begin(9600);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
cli();
TCCR1A = 0;
TCCR1B = 0;
TCNT1 = 0;
OCR1A = 15625;
TCCR1B |= (1 << WGM12);
TCCR1B |= (1 << CS12) | (1 << CS10);
TIMSK1 |= (1 << OCIE1A);
sei();
}
ISR(TIMER1_COMPA_vect)
{
for(int i=0; i<2; i++){
digitalWrite(LEDs[i],LOW);
}
digitalWrite(LEDs[j],HIGH);
j ++;
if(j > 1)
j = 0;
}
void loop() {

val = digitalRead(8);
Serial.println("checking...");
delay(250);
if (val == HIGH)
{
if (pirState == LOW)
{
Serial.println("MOTION DETECTED!");
pirState = HIGH;
}
}
else
{
if (pirState == HIGH)
{
pirState = LOW;
}
}
}