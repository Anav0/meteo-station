#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char *ssid = "NodeMCU";      // Enter SSID here
const char *password = "12345678"; //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);
uint8_t leds[3] = {4, 5, 0};
bool ledStatuses[3] = {LOW, LOW, LOW};

void setup()
{
    Serial.begin(115200);
    for (int i = 0; i < sizeof(leds), i++;)
    {
        pinMode(leds[i], OUTPUT);
    }
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);

    server.on("/", onConnect);
    for (int i = 0; i < sizeof(leds), i++;)
    {
        server.on("/\"leds[i]\"-on", turnOn);
        server.on("/\"leds[i]\"off", turnOff);
    }
    server.onNotFound(handle_NotFound);

    server.begin();
    Serial.println("HTTP server started");
}
void loop()
{
    server.handleClient();
    for (int i = 0; i < sizeof(ledStatuses), i++;)
    {
        if (ledStatuses[i])
        {
            digitalWrite(led[i], HIGH);
        }
        else
        {
            digitalWrite(led[i], LOW);
        }
    }
}

void onConnect()
{
    for (int i = 0; i < sizeof(ledStatuses), i++;)
    {
        ledStatuses[i] = LOW;
    }
    server.send(200, "text/html", SendHTML(ledStatuses));
}

void turnOn(bool status, bool ledStatuses[])
{
    status = HIGH;
    server.send(200, "text/html", SendHTML(ledStatuses));
}

void turnOff(bool status, bool ledStatuses[])
{
    status = LOW;
    server.send(200, "text/html", SendHTML(ledStatuses));
}

void handle_NotFound()
{
    server.send(404, "text/plain", "Not found");
}

String SendHTML(bool ledStats[])
{
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<title>LED Control</title>\n";
    ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    ptr += ".button-on {background-color: #1abc9c;}\n";
    ptr += ".button-on:active {background-color: #16a085;}\n";
    ptr += ".button-off {background-color: #34495e;}\n";
    ptr += ".button-off:active {background-color: #2c3e50;}\n";
    ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    ptr += "</style>\n";
    ptr += "</head>\n";
    ptr += "<body>\n";
    ptr += "<h1>ESP8266 Web Server</h1>\n";
    ptr += "<h3>Using Access Point(AP) Mode</h3>\n";

    for (int i = 0; i < sizeof(ledStats); i++)
    {
        if (ledStats[i])
        {
            ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
        }
        else
        {
            ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
        }
    }

    ptr += "</body>\n";
    ptr += "</html>\n";
    return ptr;
}