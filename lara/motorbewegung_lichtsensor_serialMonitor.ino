#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

int schalter1Pin = A0; // Schalter 1 auf der rechten Seite
int schalter2Pin = A1; // Schalter 2 auf der linken Seite

int ldrLinksPin = A2; // Fotowiderstand auf der linken Seite (2)
int ldrRechtsPin = A3; // Fotowiderstand auf der rechten Seite (1)

int step_number = 0;

bool motorDirection = true; // true für im Uhrzeigersinn, false für gegen den Uhrzeigersinn

void setup() {
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  pinMode(schalter1Pin, INPUT);
  pinMode(schalter2Pin, INPUT);

  pinMode(ldrLinksPin, INPUT);
  pinMode(ldrRechtsPin, INPUT);

  Serial.begin(9600); // Starte die serielle Kommunikation mit einer Baudrate von 9600
}

void loop() {
  int ldrLinksWert = analogRead(ldrLinksPin); // Lese den Wert des linken Fotowiderstands
  int ldrRechtsWert = analogRead(ldrRechtsPin); // Lese den Wert des rechten Fotowiderstands

  Serial.print("LDR Links: ");
  Serial.print(ldrLinksWert);
  Serial.print("\tLDR Rechts: ");
  Serial.println(ldrRechtsWert);

  if (digitalRead(schalter1Pin) == HIGH || digitalRead(schalter2Pin) == HIGH) {
    delay(50); // Entprellen

    if (digitalRead(schalter1Pin) == HIGH) {
      motorDirection = false; // Wechsle die Richtung
      Serial.println("Schalter 1 aktiviert - Drehrichtung geändert");
    }

    if (digitalRead(schalter2Pin) == HIGH) {
      motorDirection = true; // Wechsle die Richtung
      Serial.println("Schalter 2 aktiviert - Drehrichtung geändert");
    }

    OneStep(motorDirection); // Mache einen Schritt in die neue Richtung
    delay(2); // Kurze Pause zwischen den Schritten
  } else if (ldrLinksWert > ldrRechtsWert + 10) { // Wenn links heller als rechts ist (+10 als Toleranz)
    motorDirection = true; // Bewege nach links
    OneStep(motorDirection);
    delay(2);
    Serial.println("Nach links drehen (Sonne folgen)");
  } else if (ldrRechtsWert > ldrLinksWert + 10) { // Wenn rechts heller als links ist (+10 als Toleranz)
    motorDirection = false; // Bewege nach rechts
    OneStep(motorDirection);
    delay(2);
    Serial.println("Nach rechts drehen (Sonne folgen)");
  }
}

void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
