#define CH1_PIN 9 // Left stick (CH1) signal pin
#define CH2_PIN 10 // Right stick (CH2) signal pin

void setup() {
  // Initialize pins
  pinMode(CH1_PIN, INPUT);
  pinMode(CH2_PIN, INPUT);

  // Start Serial Monitor
  Serial.begin(9600);
  Serial.println("Starting Signal Monitor...");
}

void loop() {
  // Read receiver signals
  int leftSignal = pulseIn(CH1_PIN, HIGH);  // Signal from left stick
  int rightSignal = pulseIn(CH2_PIN, HIGH); // Signal from right stick

  // Print received values to Serial Monitor
  Serial.print("Left Stick (CH1) Signal: ");
  Serial.print(leftSignal);
  Serial.print(" | Right Stick (CH2) Signal: ");
  Serial.println(rightSignal);

  // Add a small delay to make output readable
  delay(100);
}

