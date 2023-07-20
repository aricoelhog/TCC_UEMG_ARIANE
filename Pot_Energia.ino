/* Declaracao das variaveis que serao utilizadas para o calculo de potencia e energia, 
 * definidos como externos pois seus valores sao coletados em outras abas
*/ 
extern double dc_current;                                // Corrente da placa
extern float vIn;                                       // Tensao da placa
/////////////////////////////////////////////
float potencia;                                         // Variavel que armazena o valor da potencia
float energia;                                          // Variavel que armazena o valor da energia

/*
 * Energia
 * Ep = PM \cdot HS eq(2)
 * Onde:
 * Ep = Energia produzida pelo modulo diariamente (Wh);
 * PM = Potencia do modulo (W);
 * HS = Horas diarias e insolacao (horas);
 * 
 * Potencia
 * PM = ISC · VBAT eq(3)
 * Onde:
 * PM = Potencia do modulo (W);
 * ISC = Corrente do modulo (A);
 * VBAT = Tensao (V);
 */
 
/////////////////////////////////////////////

// Funcao da potencia que deve rodar no loop principal
void Pot_loop(){
  potencia = abs(dc_current * vIn);                   // Calculo do valor absoluto da potencia armazenado na variavel

  Serial.print("Potencia: ");                         // Mostra a mensagem no Monitor Serial
  Serial.print(potencia);                             // Mostra o resultado no Monitor Serial
  Serial.println(" W");                               // Mostra a mensagem no Monitor Serial
}

/////////////////////////////////////////////

// Funcao da energia que deve rodar no loop principal
void Energia_loop(){
  energia = potencia * (millis()*0.000000277777777); // Calculo da potencia em Wh, onde ha a conversao do tempo de execucao em hora (1 ms = 0.000000277777777 h)
  Serial.print("Energia: ");                         // Mostra a mensagem no Monitor Serial
  Serial.print(energia);                             // Mostra o resultado no Monitor Serial
  Serial.println(" Wh");                             // Mostra a mensagem no Monitor Serial
}
