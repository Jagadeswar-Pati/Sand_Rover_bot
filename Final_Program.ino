#define CH1_PIN 9 // Left stick (CH1) signal pin
#define CH2_PIN 10 // Right stick (CH2) signal pin
#define IN1 4 // Left motor control pins
#define IN2 5
#define ENA 3 // Left motor speed (PWM)
#define IN3 6// Right motor control pins
#define IN4 7
#define ENB 11 // Right motor speed (PWM)

void setup() {
  // Initialize pins
  pinMode(CH1_PIN, INPUT);
  pinMode(CH2_PIN, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Start Serial Monitor
  Serial.begin(9600);
  Serial.println("Starting Sand Rover Bot...");
}

void loop() {
  // Read receiver signals
  int leftSignal = pulseIn(CH1_PIN, HIGH);  // Signal from left stick
  int rightSignal = pulseIn(CH2_PIN, HIGH); // Signal from right stick

  // Print raw PWM values to Serial Monitor
  Serial.print("Left Stick (CH1) Signal: ");
  Serial.print(leftSignal);
  Serial.print(" | Right Stick (CH2) Signal: ");
  Serial.println(rightSignal);

  // Define dead zone thresholds
  int deadZoneLow = 1400;
  int deadZoneHigh = 1560;

  // Check for dead zone and set motor speeds
  int leftSpeed = 0;
  int rightSpeed = 0;

  if (leftSignal > deadZoneHigh || leftSignal < deadZoneLow) {
    leftSpeed = map(leftSignal, 1000, 2000, -255, 255);
  }

  if (rightSignal > deadZoneHigh || rightSignal < deadZoneLow) {
    rightSpeed = map(rightSignal, 1000, 2000, -255, 255);
  }

  // Print mapped speeds to Serial Monitor
  Serial.print("Mapped Left Speed: ");
  Serial.print(leftSpeed);
  Serial.print(" | Mapped Right Speed: ");
  Serial.println(rightSpeed);

  // Control left motor
  if (leftSpeed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (leftSpeed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    leftSpeed = -leftSpeed; // Make speed positive
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  analogWrite(ENA, constrain(leftSpeed, 0, 255));

  // Control right motor
  if (rightSpeed > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (rightSpeed < 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    rightSpeed = -rightSpeed; // Make speed positive
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  analogWrite(ENB, constrain(rightSpeed, 0, 255));

  // Add a small delay for stability
  delay(100);
}

