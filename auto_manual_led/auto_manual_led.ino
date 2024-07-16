#include <ESP8266WiFi.h>

const char* ssid = "Yans";
const char* pass = "sijitekowolu";

WiFiServer server(80);
String header;
String output1State = "off";
String mode = "manual"; 

const int relay = D5;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeOutTime = 2000;
const long autoInterval = 5000; 

void setup() {
    Serial.begin(115200);
    pinMode(relay, OUTPUT);
    digitalWrite(relay, HIGH);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop() {
    if (mode == "otomatis") {
        currentTime = millis();
        if (currentTime - previousTime >= autoInterval) {
            previousTime = currentTime;
            if (output1State == "off") {
                output1State = "on";
                digitalWrite(relay, LOW);
            } else {
                output1State = "off";
                digitalWrite(relay, HIGH);
            }
        }
    }

    WiFiClient client = server.available();
    if (client) {
        Serial.println("New Client.");
        String currentLine = "";
        currentTime = millis();
        previousTime = currentTime;
        while (client.connected() && currentTime - previousTime <= timeOutTime) {
            currentTime = millis();
            if (client.available()) {
                char c = client.read();
                header += c;
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connection: close");
                        client.println();
                        
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        client.println("<style>html {font-family: Arial, Helvetica, sans-serif; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println("button {background-color: #4CAF50; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println("button.manual {background-color: " + String((mode == "manual" ? "#4CAF50" : "#555555")) + ";}");
                        client.println("button.otomatis {background-color: " + String((mode == "otomatis" ? "#4CAF50" : "#555555")) + ";}");
                        client.println("button.off {background-color: #555555;}</style></head>");

                        client.println("<body><h1>ESP8266 Web Server</h1>");
                        client.println("<p>Mode: " + mode + "</p>");
                        client.println("<p>Status: " + output1State + "</p>");
                        client.println("<p><a href=\"/mode=manual\"><button class=\"manual\">Manual</button></a>");
                        client.println("<a href=\"/mode=otomatis\"><button class=\"otomatis\">Otomatis</button></a></p>");
                        if (mode == "manual") {
                            if (output1State == "off") {
                                client.println("<p><a href=\"/LED=ON\"><button>ON</button></a></p>");
                            } else {
                                client.println("<p><a href=\"/LED=OFF\"><button class=\"off\">OFF</button></a></p>");
                            }
                        }
                        client.println("</body></html>");
                        
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /LED=ON") && mode == "manual") {
                    output1State = "on";
                    digitalWrite(relay, LOW);
                } else if (currentLine.endsWith("GET /LED=OFF") && mode == "manual") {
                    output1State = "off";
                    digitalWrite(relay, HIGH);
                } else if (currentLine.endsWith("GET /mode=manual")) {
                    mode = "manual";
                } else if (currentLine.endsWith("GET /mode=otomatis")) {
                    mode = "otomatis";
                    previousTime = millis(); 
                }
            }
        }
        header = "";
        client.stop();
        Serial.println("Client Disconnected.");
        Serial.println("");
    }
}
