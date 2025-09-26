#include "DHT.h"
#define DHTPIN1 4     
#define DHTTYPE1 DHT22
DHT dht1(DHTPIN1, DHTTYPE1);

int releJosue = 32;  

// Parámetros de control para DHT22
float tempMin = 23.0;  
float tempMax = 24.0;  

// ==============================
// SETUP
// ==============================
void setup() {
  Serial.begin(115200);

  // Iniciar sensores
  dht1.begin();

  // Configurar pines de relés
  pinMode(releJosue, OUTPUT);

  // Relés inicialmente apagados
  digitalWrite(releJosue, LOW);
}

// ==============================
// LOOP PRINCIPAL
// ==============================
void loop() {
  // -------------------------
  // Lectura DHT22
  // -------------------------
  float temp1 = dht1.readTemperature();

  if (isnan(temp1)) {
    Serial.println("❌ Error al leer el DHT22");
  } else {
    Serial.print("🌡 DHT22 - Temperatura: ");
    Serial.print(temp1);
    Serial.println(" °C");

    // Control con histéresis
    if (temp1 >= tempMax) {
      digitalWrite(releJosue, HIGH); 
      Serial.println("✅ DHT22 -> Relé activado (ventilador ENCENDIDO)");
    } else if (temp1 <= tempMin) {
      digitalWrite(releJosue, LOW);  
      Serial.println("🛑 DHT22 -> Relé desactivado (ventilador APAGADO)");
    }
  }



  delay(2000); // Espera entre lecturas
}
