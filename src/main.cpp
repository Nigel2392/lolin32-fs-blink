#include <Arduino.h>
#include <LittleFS.h>

void draw(String box, uint32_t timeOn);

const uint8_t LEFT = 4;
const uint8_t CENTER = 16;
const uint8_t RIGHT = 17;
const uint8_t PINARRAY[3] = {
  LEFT, CENTER, RIGHT
};

File file;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LEFT, OUTPUT);
  pinMode(CENTER, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  Serial.begin(230400);
  
  if(!LittleFS.begin(true)){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  file = LittleFS.open("/lights.txt", "r");
  if (!file) {
    Serial.println("file open failed");
    return;
  }
  
  Serial.println("Starting...");
}

void draw(String box, uint32_t timeOn) {
  uint8_t i, j;

  Serial.println("___");
  
  for (i = 0; i <= 2; i++) {
    if (box[i] == '*') {
      digitalWrite(PINARRAY[i], HIGH);
      Serial.print('*');
    } else {
      digitalWrite(PINARRAY[i], LOW);
      Serial.print('-');
    };
  };

  Serial.println();

  if (timeOn > 0) {
    delay(timeOn);

    for (i = 0; i <= 2; i++) {
      digitalWrite(PINARRAY[i], LOW);
    };
  };
}

// the loop function runs over and over again forever
void loop() {
  if (!file) {
    Serial.println("Error opening file");
    delay(10000);
    return;
  }

  String line;
  while (file.available()) {
    line = file.readStringUntil('\n');
    draw(line.c_str(), 1000);
    delay(1000);
  }

  file.seek(0, SeekSet);
  delay(10000);
}
