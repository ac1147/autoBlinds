// VCC -> 5V
// GND -> Common ground with Arduino + Power Supply

const int RPWM = 5;    // Right PWM input
const int LPWM = 6;    // Left PWM input

void motorLeft() {
  analogWrite(LPWM, 255);
  analogWrite(RPWM, 0);
}

void motorRight() {
  analogWrite(LPWM, 0);
  analogWrite(RPWM, 255);
}

void motorOff() {
  analogWrite(LPWM, 0);
  analogWrite(RPWM, 0);
}

void setup() {
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(RPWM, LOW);
  digitalWrite(LPWM, LOW);
  digitalWrite(LED, LOW);

  Serial.begin(9600);
  Serial.println("Type something and press Enter:");
}

void loop() {
  if (Serial.available()) {
    char keyBoardButton = Serial.read();     // Read 1 character
    Serial.print("You typed: ");
    Serial.println(keyBoardButton);
    if (keyBoardButton == 'a') {
      motorRight();
    }
    if (keyBoardButton == 'd') {
      motorLeft();
    }
    if (keyBoardButton == 's') {
      motorOff();
    }
  }
}
