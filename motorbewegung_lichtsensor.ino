#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

int schalter1Pin = A0; // Schalter 1 ist an Analogen Pin A0 angeschlossen
int schalter2Pin = A1; // Schalter 2 ist an Analogen Pin A1 angeschlossen

int ldrLinksPin = A2; // Fotowiderstand auf der linken Seite
int ldrRechtsPin = A3; // Fotowiderstand auf der rechten Seite

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
}

void loop() {
  int ldrLinksWert = analogRead(ldrLinksPin); // Lese den Wert des linken Fotowiderstands
  int ldrRechtsWert = analogRead(ldrRechtsPin); // Lese den Wert des rechten Fotowiderstands

  if (digitalRead(schalter1Pin) == HIGH || digitalRead(schalter2Pin) == HIGH) {
    delay(50); // Entprellen

    if (digitalRead(schalter1Pin) == HIGH) {
      motorDirection = false; // Wechsle die Richtung
    }

    if (digitalRead(schalter2Pin) == HIGH) {
      motorDirection = true; // Wechsle die Richtung
    }

    OneStep(motorDirection); // Mache einen Schritt in die neue Richtung
    delay(2); // Kurze Pause zwischen den Schritten
  } else if (ldrLinksWert > ldrRechtsWert + 10) { // Wenn links heller als rechts ist (+10 als Toleranz)
    motorDirection = true; // Bewege nach links
    OneStep(motorDirection);
    delay(2);
  } else if (ldrRechtsWert > ldrLinksWert + 10) { // Wenn rechts heller als links ist (+10 als Toleranz)
    motorDirection = false; // Bewege nach rechts
    OneStep(motorDirection);
    delay(2);
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
