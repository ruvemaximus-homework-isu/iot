// одна кнопка
#define B1 -73
#define B2 63
#define B3 -49
#define B4 -34

// две кнопки
#define B1B2 -65
#define B1B3 -121
#define B1B4 -106
#define B2B3 15
#define B2B4 30
#define B3B4 -33


char input_pins = 0;
char prev_input_pins = 0;

short inputs[] = {8, 9};
short outputs[] = {10, 11};

void setup()
{
  Serial.begin(9600);
  
  for (auto i : inputs) pinMode(i, INPUT_PULLUP);
  for (auto o : outputs) pinMode(o, OUTPUT);

  Serial.println("Started");
}

void loop()
{
  input_pins = 0;

  for (byte i = 0; i < 2; i++) {
    for (byte j = 0; j < 2; j++) {
      input_pins = input_pins << 1 | digitalRead(8 + j);
      // вот эта штука позволяет отличать нажатие кнопок, 
      // которые дают одинаковые данные при одинаковых output 
      digitalWrite(outputs[j], i != j);  
      input_pins = input_pins << 1 | digitalRead(8 + j);
    }
  }

  if (input_pins != prev_input_pins) {
    // проверка на то, что ни одна кнопка не была нажата раньше
    if (prev_input_pins == -1) {
      switch (input_pins) {
        case B1: Serial.println("B1"); break;
        case B2: Serial.println("B2"); break;
        case B3: Serial.println("B3"); break;
        case B4: Serial.println("B4"); break;
      }
    }
    // если какая-то кнопка уже была нажата
    else {
      switch (input_pins) {
        case B1B2: Serial.println("B1B2"); break;
        case B1B3: Serial.println("B1B3"); break;
        case B1B4: Serial.println("B1B4"); break;
        case B2B3: Serial.println("B2B3"); break;
        case B2B4: Serial.println("B2B4"); break;
        case B3B4: Serial.println("B3B4"); break;
      }
    } 
  } 
  
  // Serial.println((int)input_pins);

  prev_input_pins = input_pins;
  delay(300);
}