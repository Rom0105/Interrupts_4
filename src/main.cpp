#include <Arduino.h>

<<<<<<< HEAD
#define BUTTON_PIN 4

enum class ButtonState { Idle, Pressing, Held, Releasing };

ButtonState state = ButtonState::Idle;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; 
unsigned long counter = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Ready. Polling button...");
}

void loop() {
  static unsigned long lastPoll = 0;
  unsigned long now = millis();

  
  if (now - lastPoll >= 10) {
    lastPoll = now;

    int reading = digitalRead(BUTTON_PIN);

    switch (state) {
      case ButtonState::Idle:
        if (reading == LOW) {
          state = ButtonState::Pressing;
          lastDebounceTime = now;
        }
        break;

      case ButtonState::Pressing:
        if (reading == LOW && (now - lastDebounceTime > debounceDelay)) {
          state = ButtonState::Held;
          counter++;
          Serial.print("Button pressed count: ");
          Serial.println(counter);
        } else if (reading == HIGH) {
          state = ButtonState::Idle; 
        }
        break;

      case ButtonState::Held:
        if (reading == HIGH) {
          state = ButtonState::Releasing;
          lastDebounceTime = now;
        }
        break;

      case ButtonState::Releasing:
        if (reading == HIGH && (now - lastDebounceTime > debounceDelay)) {
          state = ButtonState::Idle;
        } else if (reading == LOW) {
          state = ButtonState::Held; 
        }
        break;
    }
  }
}
=======
#define RELAY_PIN      18

#define PERIOD_MS      15000UL   // Повний період циклу (15 секунд)
#define ON_TIME_MS      2000UL   // Час увімкнення (2 секунди)

void relayTask(void *pvParameters) 
{
    pinMode(RELAY_PIN, OUTPUT);
    
    while (1) 
    {
        // 1. УВІМКНУТИ РЕЛЕ (Подаємо HIGH)
        digitalWrite(RELAY_PIN, LOW); 
        // Засинаємо на час роботи реле (2 сек)
        vTaskDelay(pdMS_TO_TICKS(ON_TIME_MS)); 

        // 2. ВИМКНУТИ РЕЛЕ (Подаємо LOW)
        digitalWrite(RELAY_PIN, HIGH);  
        // Засинаємо на залишок періоду (15 сек - 2 сек = 13 сек)
        vTaskDelay(pdMS_TO_TICKS(PERIOD_MS - ON_TIME_MS)); 
    }
}

void setup() 
{
    // Створюємо фонову задачу для керування реле
    // Вона працюватиме автоматично на рівні системи ESP32
    xTaskCreatePinnedToCore(
        relayTask,       // Функція, яка виконує код реле
        "Relay_Task",    // Назва задачі
        2048,            // Розмір виділеної пам'яті (стек)
        NULL,            // Параметри задачі
        1,               // Пріоритет (1 - стандартний)
        NULL,            // Хендл задачі
        1                // Номер ядра процесора (0 або 1)
    );
}

void loop() 
{
    // Порожньо! Головний потік вільний для ваших майбутніх завдань.
}
>>>>>>> c53fdfd (Первый коммит: мой проект)
