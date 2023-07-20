#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32"                         

const char WIFI_SSID[] = "NOME WIFI";               
const char WIFI_PASSWORD[] = "SENHA WIFI";           

const char AWS_IOT_ENDPOINT[] = "a1ayq36cmvn1pq-ats.iot.us-east-2.amazonaws.com";      
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                              
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)KEY";
 
// Device Private Key                                             
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----

)KEY";
