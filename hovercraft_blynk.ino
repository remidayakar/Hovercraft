#define BLYNK_TEMPLATE_ID "TMPL5I5d-81XN"
#define BLYNK_TEMPLATE_NAME "hovercraft"
#define BLYNK_AUTH_TOKEN "H3S2VAbWPyfDI2mFdcudklwFpSZZ0UKj"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>  // Include for servo on ESP32

// WiFi credentials
char ssid[] = "Remi";
char pass[] = "qwerty123";

// Servo setup
Servo myServo;
int servoPin = 14;  // PWM-capable pin on ESP32

// MOSFET Gate Pin
#define MOSFET_GATE_PIN 4

BLYNK_WRITE(V0) {
  int angle = param.asInt();  // Value from slider
  angle = constrain(angle, 0, 180);
  myServo.write(angle);
  Serial.print("Servo angle set to: ");
  Serial.println(angle);
}

BLYNK_WRITE(V2) {
  int switchState = param.asInt();  // Button state
  if (switchState == 1) {
    digitalWrite(MOSFET_GATE_PIN, LOW);   // MOSFET ON (P-channel)
    Serial.println("Motor ON");
  } else {
    digitalWrite(MOSFET_GATE_PIN, HIGH);  // MOSFET OFF
    Serial.println("Motor OFF");
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize servo
  myServo.attach(servoPin);

  // Set MOSFET gate pin as output
  pinMode(MOSFET_GATE_PIN, OUTPUT);
  digitalWrite(MOSFET_GATE_PIN, HIGH);  // Start OFF

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}