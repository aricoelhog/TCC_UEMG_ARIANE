#include <ESP_LM35.h>                       // Biblioteca do sensor LM35 para ESP

// Declaracao das variaveis
ESP_LM35 temp(36);                          // Definicao do objeto temp, do tipo ESP_LM35 onde o valor entre parenteses e o pino GPIO36 que esta conectado ao sensor LM35
float tLM35;                                // Variavel que armazenara o valor de temperatuta lido pelo sensor

/////////////////////////////////////////////

// Funcao do LM35 que deve rodar no loop principal
void LM35_loop() {
  float somaDasTemperaturas = 0;                           // Variavel que armazenara a soma das temperaturas em Celsius(°C) lidas
  for(int i = 0; i < 1000; i++){
    somaDasTemperaturas += temp.tempC();                   // Le o valor no sensor 1000 vezes para melhorar a precisao
    delay(1);                                              // Atraso 1ms
  }
  tLM35 = somaDasTemperaturas/1000;         // Calcula a media dos valores de temperatura lidos
  Serial.print("Temperatura da placa: ");   // Mostra a mensagem no Monitor Serial
  Serial.print(tLM35);                      // Mostra o valor da temperatura no Monitor Serial
  Serial.println(" ºC");                    // Mostra a mensagem no Monitor Serial
}
