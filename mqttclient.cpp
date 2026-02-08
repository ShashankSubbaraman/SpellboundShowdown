#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include <new_imu_model_inferencing.h>
#include <eloquent_edgeimpulse.h>

using eloq::edgeimpulse::impulse;

/* ========= WiFi / MQTT ========= */
const char* ssid     = "eduroam";
const char* identity = "et18722";
const char* username = "et18722";
const char* password = "GoldyLocks4!";

const char* mqtt_server = "172.21.114.5";
const int   mqtt_port   = 1883;
const char* mqtt_topic  = "pi/messages";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

/* ========= MPU6050 ========= */
#define MPU_ADDR 0x68
#define SMPLRT_DIV   0x19
#define PWR_MGMT_1   0x6B
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47

/* ========= MPU Functions ========= */
void MPU6050_Write(uint8_t reg, uint8_t data) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

int16_t MPU6050_Read(uint8_t reg) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 2, true);
  return (Wire.read() << 8 | Wire.read());
}

void MPU6050_Init() {
  MPU6050_Write(SMPLRT_DIV, 0x07);
  MPU6050_Write(PWR_MGMT_1, 0x01);
  MPU6050_Write(CONFIG, 0x00);
  MPU6050_Write(GYRO_CONFIG, 0x18);
  MPU6050_Write(INT_ENABLE, 0x01);
}

/* ========= WiFi / MQTT ========= */
void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, WPA2_AUTH_PEAP, identity, username, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");
    if (mqttClient.connect("ESP32_EI")) {
      Serial.println("connected!");
    } else {
      delay(1000);
    }
  }
}

/* ========= SETUP ========= */
void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22);
  Wire.setClock(400000); // Fast I2C
  MPU6050_Init();

  connectWiFi();
  mqttClient.setServer(mqtt_server, mqtt_port);

  Serial.println("System ready");
  Serial.print("Model expects ");
  Serial.print(impulse.numInputs);
  Serial.println(" inputs");
}

/* ========= LOOP ========= */
void loop() {
  if (!mqttClient.connected()) connectMQTT();
  mqttClient.loop();

  impulse.buffer.clear();

  const int values_per_sample = 6;
  const int samples_needed = impulse.numInputs / values_per_sample; // 600 / 6 = 100

  // Collect IMU samples as fast as possible
  for (int i = 0; i < samples_needed; i++) {
    float Ax = MPU6050_Read(ACCEL_XOUT_H) / 16384.0;
    float Ay = MPU6050_Read(ACCEL_YOUT_H) / 16384.0;
    float Az = MPU6050_Read(ACCEL_ZOUT_H) / 16384.0;

    float Gx = MPU6050_Read(GYRO_XOUT_H) / 131.0;
    float Gy = MPU6050_Read(GYRO_YOUT_H) / 131.0;
    float Gz = MPU6050_Read(GYRO_ZOUT_H) / 131.0;

    impulse.buffer.push(Ax);
    impulse.buffer.push(Ay);
    impulse.buffer.push(Az);
    impulse.buffer.push(Gx);
    impulse.buffer.push(Gy);
    impulse.buffer.push(Gz);

    // Minimal delay to allow I2C to keep up
    delayMicroseconds(500); // ~2 kHz theoretical, adjust if needed
  }

  // Run Edge Impulse inference
  if (!impulse.classify().isOk()) {
    Serial.println(impulse.exception.toString());
    return;
  }

  // Get prediction
  String prediction = impulse.label();
  Serial.print("Prediction: ");
  Serial.println(prediction);

  // Send MQTT
  mqttClient.publish(mqtt_topic, prediction.c_str());

  // Optional: tiny pause to avoid overloading MQTT broker
  delay(10);
}
