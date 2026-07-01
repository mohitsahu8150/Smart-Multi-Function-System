#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define buttonPin 2

int mode = 0;
int lastButtonState = HIGH;

// ===== CUSTOM BLOCK =====
byte block[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

// ===== CLOCK =====
int sec = 0, min = 0, hour = 12;
bool isPM = false;
unsigned long clockMillis = 0;

// ===== INTRO =====
String message = ">>> WELCOME TO GEC AJMER <<< | MOHIT SAHU | B.TECH 2ND YEAR ECE | EMBEDDED SYSTEM PROJECT |   ";
int scrollPos = 0;

// ===== STOPWATCH =====
int t_min = 0;
int t_sec = 0;
bool timer_running = false;
unsigned long timerMillis = 0;
unsigned long lastPressTime = 0;

// ===== DINO =====
int dinoRow = 1;
bool dinoUp = false;
int obstaclePos = 15;
int obstacleRow = 1;
int score = 0;
int gameSpeed = 150;
unsigned long gameMillis = 0;

// ===== BUTTON =====
unsigned long pressStartTime = 0;
bool buttonPressed = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, block);   // custom obstacle
  pinMode(buttonPin, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop() {

  int buttonState = digitalRead(buttonPin);

  // press detect
  if (buttonState == LOW && lastButtonState == HIGH) {
    pressStartTime = millis();
    buttonPressed = true;
  }

  // release detect
  if (buttonState == HIGH && lastButtonState == LOW && buttonPressed) {

    unsigned long pressDuration = millis() - pressStartTime;

    if (pressDuration > 800) {
      mode++;
      if (mode > 4) mode = 0;
      lcd.clear();
    } else {

      // ===== STOPWATCH =====
      if (mode == 2) {
        unsigned long now = millis();

        if (now - lastPressTime < 400) {
          t_min = 0;
          t_sec = 0;
          timer_running = false;
        } else {
          timer_running = !timer_running;
        }

        lastPressTime = now;
      }

      // ===== DINO =====
      if (mode == 3) {
        dinoUp = !dinoUp;
      }
    }

    buttonPressed = false;
  }

  lastButtonState = buttonState;

  // ===== MODE 0: INTRO =====
  if (mode == 0) {
    lcd.setCursor(0, 0);
    lcd.print("INTRODUCTION");

    lcd.setCursor(0, 1);
    lcd.print(message.substring(scrollPos, scrollPos + 16));

    scrollPos++;
    if (scrollPos > message.length() - 16) scrollPos = 0;

    delay(200);
  }

  // ===== MODE 1: CLOCK =====
  else if (mode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Clock");

    lcd.setCursor(0, 1);
    lcd.print(hour); lcd.print(":");
    if (min < 10) lcd.print("0"); lcd.print(min); lcd.print(":");
    if (sec < 10) lcd.print("0"); lcd.print(sec);
    lcd.print(isPM ? " PM" : " AM");

    if (millis() - clockMillis >= 1000) {
      clockMillis = millis();

      sec++;
      if (sec >= 60) { sec = 0; min++; }
      if (min >= 60) { min = 0; hour++; }
      if (hour == 12 && min == 0 && sec == 0) isPM = !isPM;
      if (hour > 12) hour = 1;
    }
  }

  // ===== MODE 2: STOPWATCH =====
  else if (mode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Stopwatch");

    lcd.setCursor(0, 1);

    if (t_min < 10) lcd.print("0");
    lcd.print(t_min);
    lcd.print(":");
    if (t_sec < 10) lcd.print("0");
    lcd.print(t_sec);

    if (timer_running && millis() - timerMillis >= 1000) {
      timerMillis = millis();

      t_sec++;
      if (t_sec >= 60) {
        t_sec = 0;
        t_min++;
      }
    }
  }

  // ===== MODE 3: DINO GAME =====
  else if (mode == 3) {

    lcd.clear();

    if (dinoUp) dinoRow = 0;
    else dinoRow = 1;

    lcd.setCursor(1, dinoRow);
    lcd.print("D");

    // 🔥 SOLID OBSTACLE
    lcd.setCursor(obstaclePos, obstacleRow);
    lcd.write(byte(0));

    if (millis() - gameMillis >= gameSpeed) {
      gameMillis = millis();
      obstaclePos--;
    }

    if (obstaclePos < 0) {
      obstaclePos = 15;
      obstacleRow = random(0, 2);
      score++;

      if (gameSpeed > 80) gameSpeed -= 3;
    }

    if (obstaclePos == 1 && obstacleRow == dinoRow) {
      lcd.clear();
      lcd.print("Game Over");
      lcd.setCursor(0,1);
      lcd.print("Score:");
      lcd.print(score);
      delay(2000);

      obstaclePos = 15;
      score = 0;
      gameSpeed = 150;
    }
  }

  // ===== MODE 4: THANK YOU =====
  else if (mode == 4) {
    lcd.setCursor(0, 0);
    lcd.print("THANK YOU :)");

    lcd.setCursor(0, 1);
    lcd.print("MOHIT SAHU");
  }
}