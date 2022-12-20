#include <WiFi.h>
#include <string>
#include <HTTPClient.h>
#include <SparkFun_MMA8452Q.h>
#include <Wire.h>
#include <iostream>
#include <ArduinoJson.h>
using namespace std;
#define ACE_SDA 4
#define ACE_SCL 5
MMA8452Q acelerometro(0x1C);
int led = 9;
int buzzer = 6;
bool movimento = 0;  //1=TRUE, 0=FALSE
bool activated = 0;  //1=TRUE, 0=FALSE
int last_x = 0;
int last_y = 0;
int last_z = 0;
int x = 0;
int y = 0;

const char* SSIDS[4] = { "Inteli-COLLEGE", "beacon1", "beacon2", "beacon3" };
const char* PWD[4] = { "QazWsx@123", "beacon123", "beacon123", "beacon123" };
const char* serverName = "http://10.128.64.139:8000/api/tags";

unsigned long lastTime = 0;
unsigned long timerDelay = 2000;
//Variável para medir a distância
int distancia[3] = { 0, 0, 0 };
int indice = 0;
// Definições para o FTM
// Number of FTM frames requested in terms of 4 or 8 bursts (allowed values - 0 (No pref), 16, 24, 32, 64)
const uint8_t FTM_FRAME_COUNT = 16;
// Requested time period between consecutive FTM bursts in 100’s of milliseconds (allowed values - 0 (No pref) or 2-255)
const uint16_t FTM_BURST_PERIOD = 2;
// Semaphore to signal when FTM Report has been received
xSemaphoreHandle ftmSemaphore;
// Status of the received FTM Report
bool ftmSuccess = true;
/////////////////////////////////////////////////////
#define NB_APS 3
#define MAX_PONTOS 10
#define DIST_PONTO_A1y 8
#define DIST_PONTO_A3x 13
// Classe ponto apenas para encapsular as coordenadas x e Y e facilitar a construção do ARRAY
class Ponto {
private:
  float coordX = 0;
  float coordY = 0;
public:
  // Constroi o ponto colocando os valores nos atributos
  Ponto(float x, float y) {
    coordX = x;
    coordY = y;
  };
  Ponto(){};  // Construtor vazio por requisição do compilador
  void put(float x, float y) {
    coordX = x;
    coordY = y;
  };
  float x() {
    return coordX;
  };
  float y() {
    return coordY;
  };
};
// Classe representa um componente que armazena os 3 pontos (nos objetos da classe Ponto)
// assim como as 3 distâncias a cada um desses pontos
// Para facilitar, chamamos os beacons de A1, A2, A3, etc mas eles são armazenados na verdade
// nos pontos 0,1, 2, etc dos respectivos vetores onde eles são armazenados
//  A2(0,y2)  |\
//            | \->dA2
//            |  \
//            |   \ b(xMedio,yMedio)
//            |   /
//            |  /->dA1
//   A1(0,0)  | /                       A3(x3,0)
//            --------------------------|-----
// Funções extras para construir o objeto sem usar o construtor
class Triangulacao {
private:
  Ponto listaPontos[MAX_PONTOS];      // Lista de objetos Ponto com as coordenadas dos 3 pontos
  float listaDistancias[MAX_PONTOS];  // Lista das distancias a cada um dos pontos A1, A2 e A3
  float yPonto_A1_A2() {              // Formula que calcula a coordenada y do Ponto B usando apenas A1 e A2
    float dA1_2 = pow(listaDistancias[0], 2);
    float dA2_2 = pow(listaDistancias[1], 2);
    float y2_2 = pow(listaPontos[1].y(), 2);
    float y2_x2 = 2 * (listaPontos[1].y());
    if (y2_x2 == 0) {
      y2_x2 = 1;
    }
    float yb = (dA1_2 - dA2_2 + y2_2) / y2_x2;
    return (yb);
  };
  float xPonto_A1_A2() {  // Formula que calcula a coordenada x do Ponto B usando apenas A1 e A2
    float dA1_2 = pow(listaDistancias[0], 2);
    float yb = yPonto_A1_A2();
    float xb = sqrt(abs(dA1_2 - yb));
    return (xb);
  };
  float yPonto_A1_A3() {  // Formula que calcula a coordenada x do Ponto B usando apenas A1 e A3
    float dA1_2 = pow(listaDistancias[0], 2);
    float dA2_2 = pow(listaDistancias[2], 2);
    float y2_2 = pow(listaPontos[2].x(), 2);
    float y2_x2 = 2 * (listaPontos[2].x());
    if (y2_x2 == 0) {
      y2_x2 = 1;
    }
    float yb = (dA1_2 - dA2_2 + y2_2) / y2_x2;
    return (yb);
  };
  float xPonto_A1_A3() {  // Formula que calcula a coordenada y do Ponto B usando apenas A1 e A3
    float dA1_2 = pow(listaDistancias[0], 2);
    float yb = yPonto_A1_A3();
    float xb = sqrt(abs(dA1_2 - yb));
    return (xb);
  };
public:
  Triangulacao(){};
  // Constroi o componente (objeto) de triangulação preenchendo a posição dos 2 beacons da ponta
  // o central é sempre (0,0) e as 3 distancias aos 3 pontos A1, A2 e A3
  Triangulacao(float yA1, float xA3, float d1, float d2, float d3) {
    adicionaPonto(0, 0, 0);
    adicionaPonto(1, 0, yA1);  // SE EU QUISER ADICIONAR UM BEACON COLOCO AQUI
    adicionaPonto(2, xA3, 0);
    putDistancia(0, d1);
    putDistancia(1, d2);
    putDistancia(2, d3);
  };
  void adicionaPonto(int nr, float x, float y) {
    listaPontos[nr].put(x, y);
  };
  void putDistancia(int nrPonto, float d) {
    listaDistancias[nrPonto] = d;
  };
  /////// Calculo dos valores de x e y medios combinando os valores achados atraves de A1 e A2 com A1 e A3
  float pontoXMedio() {
    Serial.println("pontoXMedio");
    float xMedio = (xPonto_A1_A2() + xPonto_A1_A3()) / 2;
    return (xMedio);
  };
  float pontoYMedio() {
    Serial.println("pontoYMedio");
    float yMedio = (yPonto_A1_A2() + yPonto_A1_A3()) / 2;
    return (yMedio);
  }
};
Triangulacao* t = NULL;
////////////////////////////////////////////////////////////
void postDataToServer() {
  if (activated == 1) {
    // Serial.println(activated);
    digitalWrite(led, HIGH);
    tone(buzzer, 845, 40);
    delay(300);
    digitalWrite(led, LOW);
    noTone(buzzer);
  }
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    // Envio de dados do acelerometro para o servidor em JSON
    StaticJsonDocument<200> doc;
    doc["macAddress"] = String(WiFi.macAddress());
    doc["isMoving"] = String(movimento);
    JsonArray lastPosition = doc.createNestedArray("lastPosition");
    lastPosition.add(x);
    lastPosition.add(y);
    String requestBody;
    serializeJson(doc, requestBody);
    int httpResponseCode = http.POST(requestBody);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("HTTP Response Body: ");
      Serial.println(response);
      deserializeJson(doc, response);
      activated = int(doc["activated"]);
      Serial.print("resposta activated: ");
      Serial.println(activated);
    }
    // Free resources
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}
//Uma função para ler todos os dados da conexão WiFi
void DadosConexao() {
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.println("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("DNS IP: ");
  Serial.println(WiFi.dnsIP());
  Serial.println("BroadCast: ");
  Serial.println(WiFi.broadcastIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("Network ID: ");
  Serial.println(WiFi.networkID());
  Serial.println("PSK: ");
  Serial.println(WiFi.psk());
  Serial.println("BSSID: ");
  Serial.println(WiFi.BSSIDstr());
  Serial.println("RSSI: ");
  Serial.println(WiFi.RSSI());
}
// FTM report handler with the calculated data from the round trip
void onFtmReport(arduino_event_t* event) {
  const char* status_str[5] = { "SUCCESS", "UNSUPPORTED", "CONF_REJECTED", "NO_RESPONSE", "FAIL" };
  wifi_event_ftm_report_t* report = &event->event_info.wifi_ftm_report;
  // Set the global report status
  ftmSuccess = report->status == FTM_STATUS_SUCCESS;
  if (ftmSuccess) {
    // The estimated distance in meters may vary depending on some factors (see README file)
    distancia[indice] = (float)(report->dist_est - 4000) / 100;
    Serial.printf("FTM Estimate: Distance RAW: %.4f,Distance: %.4f m, Return Time: %u ns\n", (float)report->dist_est, (float)(report->dist_est - 4000) / 100, report->rtt_est);
    // Pointer to FTM Report with multiple entries, should be freed after use
    //free(report->ftm_report_data);
  } else {
    Serial.print("FTM Error: ");
    Serial.println(status_str[report->status]);
  }
  // Signal that report is received
  xSemaphoreGive(ftmSemaphore);
}
// Initiate FTM Session and wait for FTM Report
bool getFtmReport() {
  if (!WiFi.initiateFTM(FTM_FRAME_COUNT, FTM_BURST_PERIOD)) {
    Serial.println("FTM Error: Initiate Session Failed");
    return false;
  }
  // Wait for signal that report is received and return true if status was success
  return xSemaphoreTake(ftmSemaphore, portMAX_DELAY) == pdPASS && ftmSuccess;
}
//Função para um Menu de escolha cujo intuito é mostrar todas as possibilidades do Wifi.
//Conectar separadamente nos APs e depois fazer a triangulação
int menu() {
  Serial.println(F("1 - Conectar nos 3 beacons e medir a triagulação  \n"));
  //fica aguardando enquanto o usuário nao enviar algum dado
  while (!Serial.available()) {};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while (Serial.available()) {
    if (Serial.read() == '\n') break;
    Serial.read();
  }
  return (op - 48);  //do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}
//Função para conectar em APs sem medição FTM
void Conectar(int rede) {
  Serial.println("Conectando na rede: ");
  // Serial.println(rede);
  WiFi.begin(SSIDS[0], PWD[0]);
  while (WiFi.status() != WL_CONNECTED) {
    if (activated == 1) {
      // Serial.println(activated);
      digitalWrite(led, HIGH);
      tone(buzzer, 845, 40);
      delay(300);
      digitalWrite(led, LOW);
      noTone(buzzer);
    }
    delay(500);
    Serial.print(".");
    WiFi.disconnect();
    delay(500);
    WiFi.reconnect();
    delay(500);
  }
  Serial.println("WiFi connected");
  postDataToServer();
}
//Função para conectar num AP sem medição FTM. Futuramente para conectar na internet e enviar
//os dados dos sensores
void MedirDistancia(int rede) {
  if (activated == 1) {
    // Serial.println(activated);
    digitalWrite(led, HIGH);
    tone(buzzer, 845, 40);
    delay(300);
    digitalWrite(led, LOW);
    noTone(buzzer);
  }
  // Create binary semaphore (initialized taken and can be taken/given from any thread/ISR)
  ftmSemaphore = xSemaphoreCreateBinary();
  // Listen for FTM Report events
  WiFi.onEvent(onFtmReport, ARDUINO_EVENT_WIFI_FTM_REPORT);
  // Connect to AP that has FTM Enabled
  Serial.println("Connecting to FTM Responder");
  WiFi.begin(SSIDS[rede], PWD[rede]);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    WiFi.disconnect();
    delay(500);
    WiFi.reconnect();
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("Initiating FTM session with Frame Count ");
  Serial.print(FTM_FRAME_COUNT);
  Serial.print(" and Burst Period ");
  Serial.print(FTM_BURST_PERIOD * 100);
  Serial.println(" ms");
  getFtmReport();
}
void setup() {
  Serial.begin(115200);
  acelerometro.init();
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(led, LOW);
  WiFi.mode(WIFI_STA);
  t = new Triangulacao(DIST_PONTO_A1y, DIST_PONTO_A3x, distancia[0], distancia[1], distancia[2]);
}
void loop() {
  Serial.print("Activated: ");
  Serial.println(activated);

  if (activated == 1) {
    // Serial.println(activated);
    digitalWrite(led, HIGH);
    tone(buzzer, 845, 40);
    delay(300);
    digitalWrite(led, LOW);
    noTone(buzzer);
  }

  acelerometro.read();
  int new_x = acelerometro.x;
  int new_y = acelerometro.y;
  int new_z = acelerometro.z;
  if (abs(last_x - new_x) > 150 || abs(last_y - new_y) > 150 || abs(last_z - new_z) > 150) {
    movimento = 1;
    last_x = new_x;
    last_y = new_y;
    last_z = new_z;
  } else {
    movimento = 0;
  }
  // Serial.println(movimento);
  // if ((millis() - lastTime) > timerDelay) {
  for (int i = 1; i < 4; i++) {
    indice = i - 1;
    MedirDistancia(i);
  }
  Serial.println("Triangulando");
  t = new Triangulacao(DIST_PONTO_A1y, DIST_PONTO_A3x, distancia[0], distancia[1], distancia[2]);
  x = abs(t->pontoXMedio());
  y = abs(t->pontoYMedio());
  Serial.println(abs(t->pontoXMedio()));
  Serial.println(abs(t->pontoYMedio()));
  /////////////////////////////////////
  Conectar(0);
  ///////////////////////////////////////
  Serial.println("Dados enviados para o Backend");
}
// lastTime = millis();
