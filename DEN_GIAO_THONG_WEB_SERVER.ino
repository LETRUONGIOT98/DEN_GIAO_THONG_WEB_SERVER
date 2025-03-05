#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "tên_wifi";
const char *password = "mật_khẩu_wifi";
bool denTrangThai = false;
AsyncWebServer server(80);
#define x1 5
#define d1 19
#define v1 18

#define x2 21
#define d2 23
#define v2 22
long time1, time2, time3;
long Td = 8000, Tx = 5000, Tv = 3000; //tổng Tx + Tv phải = Td
long Td1, Tx1, Tv1; //tổng Tx + Tv phải = Td
#define Mode 4
#define tang 2
#define giam 15

#define cambien 34
int s = 0;
#include <ShiftRegister74HC595.h>
#define SDI 14
#define SCLK 12
#define LOAD 27
#define DIGITS 2


int i = 0, j = 0;
// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (DIGITS, SDI, SCLK, LOAD);




//led tuyen 2
#define SDI1 25
#define SCLK1 26
#define LOAD1 33
#define DIGITS1 2
// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr1 (DIGITS1, SDI1, SCLK1, LOAD1);
int value, digit1, digit2, digit3, digit4;
uint8_t  digits[] = {B11000000, //0
                     B11111001, //1
                     B10100100, //2
                     B10110000, //3
                     B10011001, //4
                     B10010010, //5
                     B10000010, //6
                     B11111000, //7
                     B10000000, //8
                     B10010000 //9
                    };

int dem1 = 0, dem2, dem3;
int dem11 = 0, dem22, dem33;
int gpio16Value;
String header;
int denvang, len, xuong;

long timet;
int currentMinute,currentHour;
int currentSecond;
int ttd1, ttd2, ttx1, ttx2, ttv1, ttv2, ttxb1, ttxb2, ttdb1, ttdb2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(x1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(v1, OUTPUT);
  pinMode(x2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(v2, OUTPUT);
  Td1 = Td;
  Tx1 = Tx;
  Tv1 = Tv;
  dem1 = Tx;
  dem2 = Tv;
  dem3 = Td;
  dem11 = Tx;
  dem22 = Tv;
  dem33 = Td;
  time1 = millis();
  pinMode(tang, INPUT_PULLUP);
  pinMode(giam, INPUT_PULLUP);
  pinMode(Mode, INPUT_PULLUP);
  pinMode(cambien, INPUT_PULLUP);
  ///////////////////////////////////////////
  // Kết nối với WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  startWebServer();
}



void loop() {
  if (denTrangThai == true) { //Sau 6h chiều đèn sẽ chỉ nháy vàng)
    sr.setAllHigh(); // set all pins LOW
    sr1.setAllHigh(); // set all pins LOW
    digitalWrite(d2, LOW);
    digitalWrite(x2, LOW);
    digitalWrite(v2, HIGH);
    digitalWrite(d1, LOW);
    digitalWrite(x1, LOW);
    digitalWrite(v1, HIGH);
    delay(300);
    digitalWrite(d2, LOW);
    digitalWrite(x2, LOW);
    digitalWrite(v2, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(x1, LOW);
    digitalWrite(v1, LOW);
    delay(300);
  }
  if (denTrangThai == false) { //Trước 6 h tối đèn giao thôgn bình thường
    //tuyến 2
    if (millis() - time1 <= Td1) {
      digitalWrite(d2, HIGH);
      ////////////////////////////////////////////
      ttx2 = 0;
      ttd2 = 1;
      ttv2 = 0;
      ttdb2 = 0;
      ttxb2 = 1;
      dem11 = Tx;
      dem22 = Tv;
      if (millis() - time3 >= 1000) {
        dem33 = (dem33 - 1000);
        showNumber2(dem33 / 1000);
        
        time3 = millis();
      }
    }
    else {
      digitalWrite(d2, LOW);
    }
    if (millis() - time1 > Td1 && millis() - time1 <= Td1 + Tx1) {
      digitalWrite(x2, HIGH);
      
      
      ttx2 = 1;
      ttd2 = 0;
      ttv2 = 0;
      ttdb2 = 1;
      ttxb2 = 0;
      dem22 = Tv;
      dem33 = Td;
      if (millis() - time3 >= 1000) {
        dem11 = (dem11 - 1000);
        showNumber2(dem11 / 1000);
        
        time3 = millis();
      }
    }
    else {
      digitalWrite(x2, LOW);
    }
    if (millis() - time1 > Td1 + Tx1 && millis() - time1 <= Td1 + Tx1 + Tv1) {
      digitalWrite(v2, HIGH);
      
      
      ttx2 = 0;
      ttd2 = 0;
      ttv2 = 1;
      ttdb2 = 1;
      ttxb2 = 0;
      dem11 = Tx;
      dem33 = Td;
      if (millis() - time3 >= 1000) {
        dem22 = (dem22 - 1000);
        showNumber2(dem22 / 1000);
        time3 = millis();
      }
    }
    else {
      digitalWrite(v2, LOW);
    }


    //tuyến 1
    if (millis() - time1 <= Tx) {
      digitalWrite(x1, HIGH);
      
      
      ttx1 = 1;
      ttd1 = 0;
      ttv1 = 0;
      ttxb1 = 0;
      ttdb1 = 1;
      dem2 = Tv;
      dem3 = Td;
      if (millis() - time2 >= 1000) {
        dem1 = (dem1 - 1000);
        showNumber(dem1 / 1000);
        time2 = millis();
      }
    }
    else {
      digitalWrite(x1, LOW);
    }
    if (millis() - time1 > Tx && millis() - time1 <= Tx + Tv) {
      digitalWrite(v1, HIGH);
      ttx1 = 0;
      ttd1 = 0;
      ttv1 = 1;
      ttxb1 = 0;
      ttdb1 = 1;
      dem1 = Tx;
      dem3 = Td;
      if (millis() - time2 >= 1000) {
        dem2 = (dem2 - 1000);
        showNumber(dem2 / 1000);
        time2 = millis();
      }
    }
    else {
      digitalWrite(v1, LOW);
    }
    if (millis() - time1 > Tx + Tv && millis() - time1 <= Td + Tx + Tv) {
      digitalWrite(d1, HIGH);
      ttx1 = 0;
      ttd1 = 1;
      ttv1 = 0;
      ttxb1 = 1;
      ttdb1 = 0;
      dem1 = Tx;
      dem2 = Tv;
      if (millis() - time2 >= 1000) {

        dem3 = (dem3 - 1000);
        showNumber(dem3 / 1000);
         
        time2 = millis();
      }
    }
    else {
      digitalWrite(d1, LOW);
    }
    if (millis() - time1 > Td1 + Tx1 + Tv1) {
      time1 = millis();
    }
  }
  
}
void showNumber(int num)
{
  digit2 = num % 10 ;
  digit1 = (num / 10) % 10 ;
  //Send them to 7 segment displays
  uint8_t numberToPrint[] = {digits[digit2], digits[digit1]};
  sr.setAll(numberToPrint);
}
void showNumber2(int num2)
{
  digit4 = num2 % 10 ;
  digit3 = (num2 / 10) % 10 ;
  //Send them to 7 segment displays
  uint8_t numberToPrint1[] = {digits[digit4], digits[digit3]};
  sr1.setAll(numberToPrint1);
}
// Hàm bắt đầu máy chủ web
void startWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/tang", HTTP_GET, handleTang);
  server.on("/giam", HTTP_GET, handleGiam);
  server.on("/bat", HTTP_GET, handleBatDen);
  server.on("/tat", HTTP_GET, handleTatDen);

  server.begin();
}

void handleRoot(AsyncWebServerRequest *request) {
  String html = "<html><head>";
  html += "<style>";
  html += ".button {";
  html += "  display: inline-block;";
  html += "  margin: 10px;";
  html += "  padding: 10px 20px;";
  html += "  font-size: 16px;";
  html += "  text-decoration: none;";
  html += "  border: 2px solid #008CBA;";
  html += "  color: #008CBA;";
  html += "  border-radius: 5px;";
  html += "}";
  html += ".button-on {";
  html += "  background-color: #008CBA;";
  html += "  color: white;";
  html += "}";
  html += ".button-off {";
  html += "  background-color: #FF4040;";
  html += "  color: white;";
  html += "}";
  html += "</style>";
  html += "<script>";
  html += "function sendRequest(url) {";
  html += "  var xhttp = new XMLHttpRequest();";
  html += "  xhttp.onreadystatechange = function() {";
  html += "    if (this.readyState == 4 && this.status == 200) {";
  html += "      document.getElementById('content').innerHTML = this.responseText;";
  html += "    }";
  html += "  };";
  html += "  xhttp.open('GET', url, true);";
  html += "  xhttp.send();";
  html += "}";
  html += "</script></head><body>";

  html += "<h1>Web Server Control</h1>";
  html += "<p>Thoigian: " + String((Td + Tx + Tv) / 1000) + "</p>";
  html += "<a href='javascript:void(0);' class='button' onclick=\"sendRequest('/tang')\">+</a>";
  html += "<a href='javascript:void(0);' class='button' onclick=\"sendRequest('/giam')\">-</a>";
  html += "<a href='javascript:void(0);' class='button button-on' onclick=\"sendRequest('/bat')\">Bat Den</a>";
  html += "<a href='javascript:void(0);' class='button button-off' onclick=\"sendRequest('/tat')\">Tat Den</a>";
  html += "<div id='content'></div>";

  html += "</body></html>";
  request->send(200, "text/html", html);
}

void handleTang(AsyncWebServerRequest *request) {
  Td = Td + 2000; Tx = Tx + 1000; Tv = Tv + 1000;
  Td1 = Td1 + 2000; Tx1 = Tx1 + 1000; Tv1 = Tv1 + 1000;
  showNumber((Td + Tx + Tv) / 1000);
  showNumber2((Td + Tx + Tv) / 100000);
  updatePage(request);
}

void handleGiam(AsyncWebServerRequest *request) {
  Td = Td - 2000; Tx = Tx - 1000; Tv = Tv - 1000;
  Td1 = Td1 - 2000; Tx1 = Tx1 - 1000; Tv1 = Tv1 - 1000;
  showNumber((Td + Tx + Tv) / 1000);
  showNumber2((Td + Tx + Tv) / 100000);
  updatePage(request);
}

void handleBatDen(AsyncWebServerRequest *request) {
  denTrangThai = true;
  updatePage(request);
}

void handleTatDen(AsyncWebServerRequest *request) {
  denTrangThai = false;
  updatePage(request);
}

void updatePage(AsyncWebServerRequest *request) {
  String html = "<h1>Web Server Control</h1>";
  html += "<p>Thoigian: " + String((Td + Tx + Tv) / 1000) + "</p>";
  html += "<a href='javascript:void(0);' class='button' onclick=\"sendRequest('/tang')\">+</a>";
  html += "<a href='javascript:void(0);' class='button' onclick=\"sendRequest('/giam')\">-</a>";
  html += "<a href='javascript:void(0);' class='button button-on' onclick=\"sendRequest('/bat')\">Bat Den</a>";
  html += "<a href='javascript:void(0);' class='button button-off' onclick=\"sendRequest('/tat')\">Tat Den</a>";
  html += "<div id='content'></div>";

  request->send(200, "text/html", html);
}
