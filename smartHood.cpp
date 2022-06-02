int flamePin = A0; // KY-026 analog interface
int MQ2pin = A1;//MQ2 analog interface
int fan = D6;
int flameValue;
int smokeValue;

void setup()
{
    pinMode(fan, OUTPUT);
    pinMode(MQ2pin, INPUT);
    pinMode(flamePin, INPUT);
    Serial.begin(9600);
    Serial.println("Smoke detector warming up!");
    delay(60000); // 1 minute warm up
}
void loop()
{
    digitalWrite(fan, LOW);
    smokeValue = analogRead(MQ2pin); // read analog input pin 1
    flameValue = analogRead(flamePin); // read analog input pin 0
    Serial.print("Smoke Value: ");
    Serial.print(smokeValue);
    Serial.print(" Flame Value: ");
    Serial.println(flameValue);
    if(smokeValue > 2000)
    {
        smoke();
    }
    if(flameValue < 500)
    {
        flame();
    }
  
    delay(1000);
}

void flame()
{
    Serial.println("Fire!");
    Particle.publish("mode","FIRE", PRIVATE);
    digitalWrite(fan, HIGH);
    delay(10000);
}
void smoke()
{
    Particle.publish("mode","SMOKE", PRIVATE);
    Serial.println("Smoke detected!");
    digitalWrite(fan, HIGH);
    delay(10000);
    
}
