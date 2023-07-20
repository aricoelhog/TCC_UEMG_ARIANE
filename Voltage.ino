// Declaracao das variaveis

const int voltageSensorPin = 39;          // Definicao do pino GPIO39 que esta conectado ao sensor de tensao
float vIn;                                // Voltagem que sera medida, onde para alimentacao de 3.3V, mede-se no max. 16.5V, e para 5V, max 25V
float vOut;                               // Voltagem que sera medida no pino que esta conectado o sensor
float voltageSensorADC;                   // Valor analogico que sera lido no pino (0 - 4095)
float vCC = 3.3;                          // Voltagem no pino do ESP

/////////////////////////////////////////////

// Funcao da tensao que deve rodar no loop principal
void Voltage_loop() {

  float somaDasTensoes = 0;                           // Variavel que armazenara a soma das tensoes lidas
  for(int i = 0; i < 1000; i++){
    somaDasTensoes += analogRead(voltageSensorPin);   // Le o valor analogico no sensor 1000 vezes para melhorar a precisao
    delay(1);                                         // Atraso 1ms
  }
  voltageSensorADC = somaDasTensoes/1000;             // Calcula a media dos valores de tensao lidos
  vOut = (voltageSensorADC / 4095) * vCC;             // Calcula a voltagem correspondente ao valor analogico lido, de acordo com a tensao dos pinos do ESP (3.3V) e a resolucao(1023)
  
  vIn =  22.434*vOut + 2.9185;                        // Converte a voltagem do pino a tensao gerada correspondente

  if(vIn < 2.93){                                     // Com a equacao, 2.93V e o menor valor que o sensor consegue ler, ja que apos isso a tensao no pino e zero
    vIn = 0;
  }

  Serial.print("Voltagem: ");                         // Mostra a mensagem no Monitor Serial
  Serial.print(vIn);                                  // Mostra o resultado no Monitor Serial
  Serial.println(" V");                               // Mostra a mensagem no Monitor Serial
}
