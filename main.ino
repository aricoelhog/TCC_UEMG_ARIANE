//Declaracao das funcoes das outras abas para funcionarem em conjunto no codigo principal

// AWS
extern void AWS_setup();                                                      // Funcao da AWS que deve rodar no setup principal
extern void AWS_loop();                                                       // Funcao da AWS que deve rodar no loop principal

// LM35 - Temperatura da placa
extern void LM35_loop();                                                      // Funcao do LM35 que deve rodar no loop principal

// DHT22 - Temperatura e umidade ambiente
extern void DHT22_setup();                                                    // Funcao do DHT22 que deve rodar no setup principal
extern void DHT22_loop();                                                     // Funcao do DHT22 que deve rodar no loop principal

// Voltage Sensor - Tensao da placa
extern void Voltage_loop();                                                   // Funcao da tensao que deve rodar no loop principal

// ACS712 - Corrente da placa
extern void Current_loop();                                                   // Funcao da corrente que deve rodar no loop principal

// Potencia do momento
extern void Pot_loop();                                                       // Funcao da potencia que deve rodar no loop principal

// Energia total
extern void Energia_loop();                                                   // Funcao da energia que deve rodar no loop principal

// TSL2561 - Luminosidade do local da placa
extern void TSL2561_setup();                                                  // Funcao do TSL2561 que deve rodar no setup principal
extern void TSL2561_loop();                                                   // Funcao do TSL2561 que deve rodar no loop principal

/////////////////////////////////////////////

// Funcao setup que configura o sistema para funcionamento
void setup() {
  Serial.begin(115200);                     // Inicia o Monitor Serial para visualizacao dos dados via USB no computador
  AWS_setup();                              // Chamada da funcao
  DHT22_setup();                            // Chamada da funcao
  TSL2561_setup();                          // Chamada da funcao
  Serial.println("--------");               // Mostra a mensagem no Monitor Serial
}

/////////////////////////////////////////////

// Funcao loop que e executada o tempo todo
void loop() {
  LM35_loop();                              // Chamada da funcao
  Serial.println("--------");               // Mostra a mensagem no Monitor Serial
  
  DHT22_loop();                             // Chamada da funcao
  Serial.println("--------");               // Mostra a mensagem no Monitor Serial
  
  TSL2561_loop();                           // Chamada da funcao
  Serial.println("--------");               // Mostra a mensagem no Monitor Serial
  
  Voltage_loop();                           // Chamada da funcao
  Serial.println("--------");               // Mostra a mensagem no Monitor Serial
  
  Current_loop();                           // Chamada da funcao
  Serial.println("--------");               // Mostra a mensagem no Monitor Serial
  
  Pot_loop();                               // Chamada da funcao
  Serial.println("--------");               // Mostra a mensagem no Monitor Serial
  
  Energia_loop();                           // Chamada da funcao
  Serial.println("--------");               // Mostra a mensagem no Monitor Serial
  
  Serial.println("        ");               // Pula uma linha no Monitor Serial
  
  AWS_loop();                               // Chamada da funcao
  
  delay(2000);                              // Atraso de 500ms
