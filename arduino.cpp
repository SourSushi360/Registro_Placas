const int trigPin = 2;
const int echoPin = 3;
const int trig2 = 6;
const int echo2 = 5;
const int ledPin = 4; // Pin del LED
unsigned long lastActiveTime = 0;
const unsigned long inactivityThreshold = 2000; 
float distancia_comparacion_cm;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distancia_cm = (duration / 2) / 29.1;
  Serial.print("Distancia: ");
  Serial.print(distancia_cm);
  Serial.println(" cm 1");
  
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  
  long duration2 = pulseIn(echo2, HIGH);
  float distancia_cm2 = (duration2 / 2) / 29.1;
  Serial.print("Distancia: ");
  Serial.print(distancia_cm2);
  Serial.println(" cm 2");
  
  if (millis() - lastActiveTime <= inactivityThreshold && distancia_comparacion_cm == distancia_cm) {
	  digitalWrite(ledPin, HIGH);
      Serial.print(distancia_comparacion_cm);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  if (distancia_cm2 < 50) {
    lastActiveTime = millis();
    distancia_comparacion_cm = distancia_cm;
  } else {
    digitalWrite(ledPin, LOW);
    lastActiveTime = 0;
  }
  
  delay(1000);
}
