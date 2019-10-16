#define Red 4
#define Green 5
#define Blue 0
#define delayAmount 250

void setup()
{
    pinMode(Red, OUTPUT);
    pinMode(Green, OUTPUT);
    pinMode(Blue, OUTPUT);
}

void loop()
{
    digitalWrite(Red, HIGH);
    delay(delayAmount);
    digitalWrite(Green, HIGH);
    delay(delayAmount);
    digitalWrite(Blue, HIGH);
    delay(delayAmount);

    digitalWrite(Red, LOW);
    delay(delayAmount);
    digitalWrite(Green, LOW);
    delay(delayAmount);
    digitalWrite(Blue, LOW);
    delay(delayAmount);
}