#define BLYNK_TEMPLATE_ID "TMPL5I5d-81XN"
#define BLYNK_TEMPLATE_NAME "hovercraft"
#define BLYNK_AUTH_TOKEN "H3S2VAbWPyfDI2mFdcudklwFpSZZ0UKj"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "Icam_IOT";
char pass[] = "T%D/Q%;GL|W@";

Servo myServo;
int servoPin = 18;  // Choose a PWM-capable pin on ESP32

BLYNK_WRITE(V0) {
  int angle = param.asInt();  // Get value from Blynk Slider (0 - 180)
  angle = constrain(angle, 0, 180);  // Ensure safe ranges
  myServo.write(angle);
  Serial.print("Servo angle set to: ");
  Serial.println(angle);

// GPIO pin controlling the MOSFET Gate
#define MOSFET_GATE_PIN 4

BLYNK_WRITE(V2) {
  int switchState = param.asInt();  // Button ON = 1, OFF = 0

  if (switchState == 1) {
    digitalWrite(MOSFET_GATE_PIN, LOW);   // Turn MOSFET ON (Motor ON)
    Serial.println("Motor ON");
  } else {
    digitalWrite(MOSFET_GATE_PIN, HIGH);  // Turn MOSFET OFF (Motor OFF)
    Serial.println("Motor OFF");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(MOSFET_GATE_PIN, OUTPUT);
  digitalWrite(MOSFET_GATE_PIN, HIGH);  // Start with motor OFF (MOSFET OFF)

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
