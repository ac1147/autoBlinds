#include <WiFi.h>

#define RELAY_PIN 14     // Motor Left
#define RELAY_PIN2 27    // Motor Right

const char* ssid     = "########";
const char* password = "########";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(RELAY_PIN2, LOW);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  // Motor Left (GPIO 14)
  if (request.indexOf("/LON") != -1)  digitalWrite(RELAY_PIN, HIGH);
  if (request.indexOf("/LOFF") != -1) digitalWrite(RELAY_PIN, LOW);

  // Motor Right (GPIO 27)
  if (request.indexOf("/RON") != -1)  digitalWrite(RELAY_PIN2, HIGH);
  if (request.indexOf("/ROFF") != -1) digitalWrite(RELAY_PIN2, LOW);

  // HTML response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println("body { font-family: Arial; text-align: center; }");
  client.println("button { width: 150px; height: 60px; font-size: 20px; margin: 10px; }");
  client.println(".section { margin-bottom: 40px; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");

  client.println("<h1>ESP32 Motor Control</h1>");

  // Motor Left
  client.println("<div class='section'>");
  client.println("<h2>Motor Left (GPIO 14)</h2>");
  client.println("<a href='/LON'><button>ON</button></a>");
  client.println("<a href='/LOFF'><button>OFF</button></a>");
  client.println("</div>");

  // Motor Right
  client.println("<div class='section'>");
  client.println("<h2>Motor Right (GPIO 27)</h2>");
  client.println("<a href='/RON'><button>ON</button></a>");
  client.println("<a href='/ROFF'><button>OFF</button></a>");
  client.println("</div>");

  client.println("</body>");
  client.println("</html>");

  delay(1);
  client.stop();
}
