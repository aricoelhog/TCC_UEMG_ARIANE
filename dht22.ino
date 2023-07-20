#include <DHT.h>                            // Biblioteca dos sensores DHT
                      
DHT dht22(5, DHT22);                        // Definicao do objeto dht do tipo DHT22, conectado ao pino GPIO5
float temperatura, umidade;                 // Variaveis que armazenarao os valores de temperatura ambiente e umidade

/////////////////////////////////////////////

// Funcao do DHT22 que deve rodar no setup principal
void DHT22_setup() {
  dht22.begin();                            // Inicia o sensor
}

/////////////////////////////////////////////

// Funcao do DHT22 que deve rodar no loop principal
void DHT22_loop(){
  
  umidade = dht22.readHumidity();           // Le a umidade do ambiente
  temperatura = dht22.readTemperature();    // Le a temperatura ambiente

  // Se nao houver valor lido para temperatura ou para umidade:
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Nao foi possivel medir os parametros!");        // Mostra a mensagem no Monitor Serial
  }
  else { // Senao:
    Serial.print("Temperatura: ");          // Mostra a mensagem no Monitor Serial
    Serial.print(temperatura);              // Mostra o resultado no Monitor Serial
    Serial.println(" °C");                  // Mostra a mensagem no Monitor Serial
    Serial.println("--------");             // Mostra a mensagem no Monitor Serial
    Serial.print("Umidade: ");              // Mostra a mensagem no Monitor Serial
    Serial.print(umidade);                  // Mostra o resultado no Monitor Serial
    Serial.println(" %");                   // Mostra a mensagem no Monitor Serial
  }
}
