#include <Servo.h>
#include <SoftwareSerial.h>

#define GAS_SENSOR_PIN A0
#define HEART_RATE_SENSOR_PIN A5
#define ULTRASONIC_TRIG_PIN 2
#define ULTRASONIC_ECHO_PIN 3
#define SERVO_PIN 9

Servo myServo;
SoftwareSerial bluetooth(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(HEART_RATE_SENSOR_PIN, INPUT);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN);
}

void loop() {
  // Read gas sensor data
  int gasValue = analogRead(GAS_SENSOR_PIN);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Control servo based on gas sensor data
  if (gasValue > 500) {
    myServo.write(90); // Rotate servo to 90 degrees
  } else {
    myServo.write(0); // Rotate servo to 0 degrees
  }

  // Read heart rate sensor data
  int heartRate = analogRead(HEART_RATE_SENSOR_PIN);
  Serial.print("Heart Rate Sensor Value: ");
  Serial.println(heartRate);

  // Read ultrasonic sensor data
  long duration, distance;
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("Ultrasonic Sensor Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send data over Bluetooth
  bluetooth.print("Gas: ");
  bluetooth.println(gasValue);
  bluetooth.print("Heart Rate: ");
  bluetooth.println(heartRate);
  bluetooth.print("Distance: ");
  bluetooth.print(distance);
  bluetooth.println(" cm");

  delay(1000); // Delay for stability
}