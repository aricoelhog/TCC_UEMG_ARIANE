/* Declaracao das variaveis dos valores que serao enviados a nuvem, definidos como externos 
 * pois seus valores sao coletados em outras abas
*/
extern float tLM35;                         // Temperatura da placa
extern float temperatura, umidade;          // Umidade e temperatura ambiente
extern float vIn;                           // Tensao da placa
extern double dc_current;                   // Corrente da placa
extern float potencia;                      // Potencia da placa do momento
extern float energia;                       // Energia gerada pela placa
extern float luminosidade;                  // Luminosidade do local da placa em lux
extern float irradiancia;                   // Irradiancia do local da placa (W/m2)

/* Variaveis que determinarao em que momento as mensagens serao publicadas*/
long TempoExecucao = 0;
int TempoParaPublicar = 300000;

/////////////////////////////////////////////

// Bibliotecas a serem utilizadas para conectar o ESP32 a AWS
#include "secrets.h"                        // Arquivo com informacoes de conexao WiFi, chaves de seguranca, politicas e certificados que permitem conexao segura
#include <WiFiClientSecure.h>               // Classe que implementa suporte para conexoes seguras usando TLS (SSL), necessarias para conexao com AWS
#include <PubSubClient.h>                   // Biblioteca para utilizacao do protocolo MQTT
#include <ArduinoJson.h>                    // Biblioteca para utilizacao de JSON
#include "WiFi.h"                           // Biblioteca WiFi para conexao com a internet

#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub" // Define o comando para publicar mensagens MQTT
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub" // Define o comando para inscrever ("receber") uma mensagens MQTT

WiFiClientSecure net = WiFiClientSecure();  // Criou o objeto 'net' do tipo WiFiClientSecure;
PubSubClient client(net);                   // Definiu-se o objeto de conexao da AWS como o cliente.*/

/////////////////////////////////////////////

// Funcao que conecta o ESP32 a AWS IOT
void connectAWS()
{
  delay(1000);                              // Atraso de 1 seg
  WiFi.mode(WIFI_STA);                      // Habilita o modo estacao para permitir conexao WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     // Inicia e tenta conectar ao WiFi, onde as variaveis (SSID e Senha) foram definidas no arquivo secrets.h
 
  Serial.println("Conectando ao Wi-Fi");    // Mostra a mensagem no Monitor Serial

 // Enquanto o status do WiFi for diferente de 'conectado', sera exibido um ponto no monitor serial a cada 500 mili-Segundos
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);                             // Atraso de 500ms
    Serial.print(".");                      // Mostra a mensagem no Monitor Serial
  }

  // Configura o objeto 'net' para utilizar as credenciais da coisa AWS IoT
  net.setCACert(AWS_CERT_CA);               // Certificado CA coletado da coisa ESP32 na AWS IoT
  net.setCertificate(AWS_CERT_CRT);         // Certificado digital da coisa ESP32 na AWS IoT
  net.setPrivateKey(AWS_CERT_PRIVATE);      // Chave privada da coisa ESP32 na AWS IoT
  
  client.setServer(AWS_IOT_ENDPOINT, 8883); // Conecta ao broker do MQTT da AWS por meio do endpoint
    
  client.setCallback(messageHandler);       // Cria um manipulador de mensagens

  Serial.println("Conectando a AWS IOT");   // Mostra a mensagem no Monitor Serial

 // Enquanto nao conectar a coisa ESP32 na AWS, sera exibido um ponto no monitor serial a cada 100 mili-Segundos
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");                      // Mostra a mensagem no Monitor Serial
    delay(100);                             // Atraso de 100ms
  }

 // Se nao for possivel conectar, sera exibido a mensagem abaixo no monitor serial
  if (!client.connected())
  {
    Serial.println("Nao foi possivel conectar a AWS IoT!");    // Mostra a mensagem no Monitor Serial
    return;
  }
 
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);                  // Inscrever em um topico
 
  Serial.println("Conexao a AWS IoT efetuada com sucesso!");  // Mostra a mensagem no Monitor Serial
}


/////////////////////////////////////////////
// Reconecta ao broker
void reconnect() {
  // Loop ate reconectar novamente
  while (!client.connected()) {
    Serial.print("A conexao foi perdida...");
    Serial.println("Tentando reestabelecer a conexao...");
    
    // Tentativa de reconexao
    if (client.connect(THINGNAME)) {
      Serial.println("Conectado e dados publicados!");
      Serial.println("          ");
      
      publishMessage();                                     // Quando conectado, publica no cliente
      
      client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);            // E inscreve
    } else {
      Serial.print("Falha ao reconectar, rc=");             // Mostra a mensagem no Monitor Serial
      Serial.print(client.state());                         // Mostra a mensagem no Monitor Serial
      Serial.println(" Tentando novamente em 3 segundos");  // Mostra a mensagem no Monitor Serial
      delay(3000);                                          // Atraso de 3s para tentar reconectar
    }
  }
}

/////////////////////////////////////////////


// Envia os dados para AWS IOT, publica a mensagem no formato JSON
void publishMessage()
{
  StaticJsonDocument<200> doc;              // Define um documento JSON do tipo estatico
  
  // Escreve as variaveis separadamente no doc
  doc["Temperatura_placa_C"] = tLM35; 
  doc["Temperatura_ambiente_C"] = temperatura;
  doc["Umidade"] = umidade;
  doc["Luminosidade_lux"] = luminosidade;
  doc["Irradiancia_W_m2"] = irradiancia;
  doc["Voltagem"] = vIn;
  doc["Corrente_mA"] = dc_current;
  doc["Potencia_W"] = potencia;
  doc["Energia_Wh"] = energia;
  char jsonBuffer[512];                     // Define vetor de caracteres que sera convertida em JSON
  serializeJson(doc, jsonBuffer);           // Converte o documento em string utilizando o buffer
  
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);      // Publica(Escreve, mostra) o documento no cliente (AWS IoT) utilizando o buffer
}



/////////////////////////////////////////////


// Recebe os dados da AWS IOT
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Chegando mensagem: ");      // Mostra a mensagem no Monitor Serial
  Serial.println(topic);                    // Mostra o topico no Monitor Serial
 
  StaticJsonDocument<200> doc;              // Define um documento JSON do tipo estatico
  deserializeJson(doc, payload);            // Converte a string no documento JSON
  const char* message = doc["message"];     // Define a variavel constante que armazena a mensagem recebida
  Serial.println(message);                  // Mostra a mensagem no Monitor Serial
}


/////////////////////////////////////////////

// Funcao da AWS que deve rodar no setup principal
void AWS_setup() {
  connectAWS();                             // Conecta ESP32 a AWS IOT
}

/////////////////////////////////////////////

// Funcao da AWS que deve rodar no loop principal
void AWS_loop() {
   
  if(millis() - TempoExecucao > TempoParaPublicar){       // Executa de acordo com o intervalo de publicacao
    publishMessage();                                     // Envia os dados para AWS IOT, publica a mensagem no formato JSON
    client.loop();                                        // Permite que o cliente processe mensagens recebidas para enviar dados de publicacao e faz uma atualizacao da conexao
    Serial.println("Tentando publicar dados...");         // Mostra a mensagem no Monitor Serial
    Serial.println("--------");                           // Mostra a mensagem no Monitor Serial
    
    TempoExecucao = millis();                             // Recebe o tempo que o programa esta executando
    
    if (!client.connected()) {
      reconnect();                                        // Caso perca a conexao, ha uma tentativa de reconectar
    } else {
      Serial.println("Dados publicados com sucesso!");    // Mostra a mensagem no Monitor Serial
    }
  }
  
  Serial.println("      ");
  Serial.println("Tempo de execucao: ");
  Serial.println(millis());
  Serial.println("      ");
}
