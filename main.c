#include <QTRSensors.h>

// Definición de pines para el control del motor
#define PIN_IN1 2
#define PIN_IN2 5
#define PIN_ENABLE1 3
#define PIN_IN3 8
#define PIN_IN4 9
#define PIN_ENABLE2 10

// Definición de estados del robot
enum State {
    AVANZAR,
    GIRAR_DERECHA,
    GIRAR_IZQUIERDA,
    STOP
};

// Función para imprimir el estado actual en el puerto serial
void printCurrentState(State state) {
    switch (state) {
        case AVANZAR:
            Serial.println("AVANZAR");
            break;
        case GIRAR_DERECHA:
            Serial.println("GIRAR_DERECHA");
            break;
        case GIRAR_IZQUIERDA:
            Serial.println("GIRAR_IZQUIERDA");
            break;
        default:
            Serial.println("ESTADO DESCONOCIDO");
            break;
    }
}

// Estado inicial del robot
State currentState = AVANZAR;

QTRSensors qtr;  // Objeto para sensores QTR

const uint8_t SensorCount = 6;  // Número de sensores
uint16_t sensorValues[SensorCount];  // Valores de los sensores

void setup() {
    // Configuración de los pines de salida
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);
    pinMode(PIN_ENABLE1, OUTPUT);
    pinMode(PIN_IN3, OUTPUT);
    pinMode(PIN_IN4, OUTPUT);
    pinMode(PIN_ENABLE2, OUTPUT);

    // Configuración de los sensores QTR
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, SensorCount);
    
    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);  // Encender LED durante la calibración

    // Hacer que el robot gire en su eje durante la calibración
    analogWrite(PIN_ENABLE1, 150);
    analogWrite(PIN_ENABLE2, 150);
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);
    digitalWrite(PIN_IN3, HIGH);
    digitalWrite(PIN_IN4, LOW);

    // Calibrar los sensores
    for (uint16_t i = 0; i < 400; i++) {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW);  // Apagar LED después de la calibración

    // Detener el robot después de la calibración
    analogWrite(PIN_ENABLE1, 0);
    analogWrite(PIN_ENABLE2, 0);

    // Inicializar comunicación serial
    Serial.begin(9600);

    // Imprimir valores de calibración en el puerto serial
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);
}

void loop() {
    // Leer la posición de la línea
    uint16_t position = qtr.readLineBlack(sensorValues);

    // Calcular promedios de los sensores
    int Primer_Promedio = (sensorValues[0] + sensorValues[1]) / 2;
    int Segundo_Promedio = (sensorValues[2] + sensorValues[3]) / 2;
    int Tercer_Promedio = (sensorValues[4] + sensorValues[5]) / 2;

    // Determinar el estado del robot basado en los promedios de los sensores
    if (Primer_Promedio < 500 && Segundo_Promedio > 500 && Tercer_Promedio > 500) {
        currentState = GIRAR_IZQUIERDA;
    } else if (Tercer_Promedio < 500 && Segundo_Promedio > 500 && Primer_Promedio > 500) {
        currentState = GIRAR_DERECHA;
    } else if (Primer_Promedio < 500 && Segundo_Promedio < 500 && Tercer_Promedio < 500) {
        currentState = STOP;
    } else {
        currentState = AVANZAR;
    }

    // Ejecutar acciones basadas en el estado actual
    switch (currentState) {
        case GIRAR_DERECHA:
            analogWrite(PIN_ENABLE1, 0);
            analogWrite(PIN_ENABLE2, 130);
            digitalWrite(PIN_IN1, LOW);
            digitalWrite(PIN_IN2, HIGH);
            digitalWrite(PIN_IN3, LOW);
            digitalWrite(PIN_IN4, HIGH);
            break;
        case GIRAR_IZQUIERDA:
            analogWrite(PIN_ENABLE1, 130);
            analogWrite(PIN_ENABLE2, 0);
            digitalWrite(PIN_IN1, LOW);
            digitalWrite(PIN_IN2, HIGH);
            digitalWrite(PIN_IN3, LOW);
            digitalWrite(PIN_IN4, HIGH);
            break;
        case AVANZAR:
            analogWrite(PIN_ENABLE1, 150);
            analogWrite(PIN_ENABLE2, 150);
            digitalWrite(PIN_IN1, LOW);
            digitalWrite(PIN_IN2, HIGH);
            digitalWrite(PIN_IN3, LOW);
            digitalWrite(PIN_IN4, HIGH);
            break;
        case STOP:
            analogWrite(PIN_ENABLE1, 0);
            analogWrite(PIN_ENABLE2, 0);
            digitalWrite(PIN_IN1, LOW);
            digitalWrite(PIN_IN2, HIGH);
            digitalWrite(PIN_IN3, LOW);
            digitalWrite(PIN_IN4, HIGH);
            break;
    }

    delay(10); // Pequeño retraso para estabilidad
}
