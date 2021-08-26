const int speaker = 8;
int timer = 1000;
unsigned long last_reset = 0;
int led_pin;
int score = 0;
bool playing = true;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(A0,INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  reset();
}

void loop() {
  if (playing) {
    const bool a = digitalRead(2);
    const bool b = digitalRead(3);
    const bool c = digitalRead(4);
    if (!(a && b && c)) {
      if (correct_pin(a,b,c)) {
        reset();
        delay(250);
        last_reset = millis();
        timer = 250;
        score++;
      } else {
        playing = false;
        digitalWrite(led_pin, LOW);
        Serial.println("Wrong button. Game over.");
        Serial.println("Your score is " + String(score));
      }
    }
    if (millis() - last_reset > timer) {
      playing = false;
      digitalWrite(led_pin, LOW);
      Serial.println("Time's up. Game over.");
      Serial.println("Your score is " + String(score));
    }
  }
}

void reset() {
  digitalWrite(led_pin, LOW);
  delay(50);
  led_pin = random(5,8);
  digitalWrite(led_pin, HIGH);
}

bool correct_pin(bool a, bool b, bool c) { // note that "true" means the button is NOT pressed
  if (led_pin == 5) {
    return b && c; // if all buttons are hit then still return false
  } else if (led_pin == 6) {
    return a && c;
  } else {
    return a && b;
  }
}