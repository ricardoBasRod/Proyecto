int LED = 4;                         // Pin para el LED
int ENTRY_SENSOR_PIN = 2;             // D2 (pin 4) para el sensor de entrada
int EXIT_SENSOR_PIN = 3;              // D3 (pin 0) para el sensor de salida

bool ledState = LOW;                  // Estado actual del LED
bool lastEntrySensorValue = LOW;      // Último valor leído del sensor de entrada
bool lastExitSensorValue = LOW;       // Último valor leído del sensor de salida

  int mode=0;
  int numero=0; 
  String id_="id";
  void setup() {
  pinMode(ENTRY_SENSOR_PIN, INPUT);   // Configurar el sensor de entrada (D2)
  pinMode(EXIT_SENSOR_PIN, INPUT);    // Configurar el sensor de salida (D3)
  pinMode(LED, OUTPUT);               // Configurar el pin del LED
  Serial.begin(9600);
  Serial.println(F("DHTxx Unified Sensor Example"));
  }
void loop() {
  id_="";
  int entrySensorValue = digitalRead(ENTRY_SENSOR_PIN);  // Leer el valor del sensor de entrada
  int exitSensorValue = digitalRead(EXIT_SENSOR_PIN);    // Leer el valor del sensor de salida
  Serial.print(entrySensorValue);
  Serial.print(exitSensorValue);
  // Si el sensor de entrada detecta movimiento (de LOW a HIGH)
  if (entrySensorValue == HIGH && lastEntrySensorValue == LOW) {
    ledState = HIGH;  // Encender el LED
    id_="id_1";
    mode=1;
    numero=numero+1;
    digitalWrite(LED, ledState);
    Serial.print("{"data" : [{\"arduinoID_id_sensor\":");
    Serial.print(id_);
    Serial.print(",\"modo_operacion\":");
    Serial.print(mode);
    Serial.print(",\"num_personas\":\"");
    Serial.print(numero);
    Serial.println("\"}]}");
    delay(1000);  // Esperar 1 segundo antes de procesar nuevamente
  }

  // Si el sensor de salida detecta movimiento (de LOW a HIGH)
  if (exitSensorValue == HIGH && lastExitSensorValue == LOW) {
    ledState = LOW;  // Apagar el LED
    id_="id_2";
    mode=0;
    numero=numero-1;
    digitalWrite(LED, ledState);
    Serial.print("{"data" : [{\"arduinoID_id_sensor\":");
    Serial.print(id_);
    Serial.print(",\"modo_operacion\":");
    Serial.print(mode);
    Serial.print(",\"num_personas\":\"");
    Serial.print(numero);
    Serial.println("\"}]}");
    delay(1000);  // Esperar 1 segundo antes de procesar nuevamente
  }

  // Actualizar los últimos valores leídos de los sensores
  lastEntrySensorValue = entrySensorValue;
  lastExitSensorValue = exitSensorValue;

  delay(1000);  // Esperar 1 segundo entre lecturas
}