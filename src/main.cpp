
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <Hash.h>

#include "index.h"
#include "login.h"
#include "unauthorize.h"

#ifndef STASSID
#define STASSID "Network"
#define STAPSK "kazanci..1234"
#endif

//wifi bilgileri
const char *ssid = STASSID;
const char *password = STAPSK;
//giriş ekranı için giriş bilgileri
const char *userName = "admin";
const char *userPassword = "admin";
//giriş yetki değişkeni
bool isAuthorize = false;
//16 adet buton
bool buttons[16] = {false};
//dht için timer sayacı
unsigned long dhtTimer = 0;

ESP8266WiFiMulti WiFiMulti;
//http server
ESP8266WebServer server(80);
//socket server
WebSocketsServer webSocket = WebSocketsServer(81);

//fucntion declaration
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
void loginPage();
void logOut();
void controlPanelPage();
void sendButton();
void sendButtons(bool button[]);
void handleNotFound();
void login();

void setup(void)
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //http urlleri
  server.on("/", controlPanelPage);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.on("/login", loginPage);
  server.on("/controlpanel", login);
  server.on("/logout", logOut);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  //socket event
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("Socket server started");
  
}

void loop(void)
{
  webSocket.loop();
  server.handleClient();

  //her saniye dht oku ve client lere gönder
   if (millis() - dhtTimer > 1000)
  {
    double tempature = 20; //dht'den sıcaklık okunur
    double humidity = 20; //dht'den nem okunur
    //sıcaklık ve nem tüm bağlantıara gönderiliyor.
    //örneğin gönderilen değer sc-27 veya hu-85 şeklindedir
    webSocket.broadcastTXT("sc-"+String(tempature));//sıcaklık
    webSocket.broadcastTXT("hu-"+String(humidity));//nem
    dhtTimer = millis();                                                                         
  }
}
//index html'in döndüğü fonksiyon
void controlPanelPage()
{
  if (isAuthorize)
  {
    server.send(200, "text/html", indexHtml);
  }
  else
  {
    //eğer şifre girilmemiş ise yan yetki yok ise giriş sayfasına gönderiliyor
    loginPage();
  }
}
//loginprocess
void login()
{
  //url'den gelen argümanları okuyor
  if (server.arg(0) == userName && server.arg(1) == userPassword)
  {
    //eğer şifre ve kullanıcı adı doğruysa kontrol paneline yönlendiriliyor 
    isAuthorize = true;
    controlPanelPage();
  }
  else
  {
    //değilse hata sayfasına gönderiliyor
    server.send(200, "text/html", unauthorizePage);
  }
}
//sistemden çıkış yapılıyor
void logOut()
{
  isAuthorize = false;
  loginPage();
}
//giriş ekranına gönderiliyor
void loginPage()
{
  server.send(200, "text/html", loginPageHtml);
}
//eğer yanlış bir path girilmiş ise hata dönülüypr
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}
//indexi girilmiş butonun değerini web sayfasına gönderiyor
void sendButton(int buttonNumber, bool result)
{
  String text = "";
  if (result)
  {
    text = "btn" + String(buttonNumber) + "-1";
  }
  else
  {
    text = "btn" + String(buttonNumber) + "-0";
  }
  //örneğin btn10-1 veya btn1-0 şeklinde gönderiliyor
  webSocket.broadcastTXT(text);
}
//tüm butonların değerini web sayfasına gönderiliyor
void sendAllButtonsToAllConnect(bool button[])
{
  for (int i = 0; i < 16; i++)
  {
    sendButton(i + 1, button[i]);
  }
}
//websocket protokolü ile herhangi bir bağlantı olduğunda çalışan fonksiyon
void connectionInit()
{
  //kontrol paneline girildiğinde tüm buton değerleri karşı tarafa gönderiliyor
  sendAllButtonsToAllConnect(buttons);
}

//web sayfası tarafından esp'ye bir mesaj gönderilir ise bu fonksiyon içerisinde yönlendiriliyor
void checkInputForButtons(uint8_t *payload)
{
  //gelen değer btn1-0(1. buttona false ata) kalıbında ise işlem görüyor
  String temp = String((char *)payload);
  if (temp.substring(0, 3) == "btn")
  {
    if (temp.length() == 6)
    {
      int buttonNumber = temp.substring(3, 4).toInt();
      if (temp[5] == '0')
      {
        buttons[buttonNumber - 1] = false;
        sendButton(buttonNumber, false);
      }
      else if (temp[5] == '1')
      {
        buttons[buttonNumber - 1] = true;
        sendButton(buttonNumber, true);
      }
    }
    else if (temp.length() == 7)
    {
      int buttonNumber = temp.substring(3, 5).toInt();
      if (temp[6] == '0')
      {
        buttons[buttonNumber - 1] = false;
        sendButton(buttonNumber, false);
      }
      else if (temp[6] == '1')
      {
        buttons[buttonNumber - 1] = true;
        sendButton(buttonNumber, true);
      }
    }
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{

  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_CONNECTED:
  {
    IPAddress ip = webSocket.remoteIP(num);
    Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
    Serial.println(num);
    //ilk bağlantı kurulduğunda tüm butonlar karşı tarafa gönderiliyor 
    connectionInit();
  }
  break;
  case WStype_TEXT:
    Serial.printf("[%u] get Text: %s\n", num, payload);
    //web sayfasından gelen veri buttonlara set ediliyor
    checkInputForButtons(payload);
    break;
  case WStype_BIN:
    Serial.printf("[%u] get binary length: %u\n", num, length);
    hexdump(payload, length);
    break;
  default:
    break;
  }
}