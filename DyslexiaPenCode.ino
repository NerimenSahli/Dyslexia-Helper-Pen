#include "esp_camera.h"
#include <WiFi.h>
#include "esp_http_server.h"
// ===================
// WIFI CREDENTIALS
// ===================
const char* ssid = "";
const char* password = "";
// Static IP for STA (station) interface
IPAddress local_IP(192, 168, 43, 50); 
IPAddress gateway(192, 168, 43, 1);    // Router / hotspot gateway
IPAddress subnet(255, 255, 255, 0);

// ===================
// CAMERA PINS (AI Thinker)
// ===================
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

httpd_handle_t stream_httpd = NULL;

// ===================
// MJPEG STREAM HANDLER
// ===================
static esp_err_t stream_handler(httpd_req_t *req) {
  camera_fb_t * fb = NULL;
  esp_err_t res = ESP_OK;

  res = httpd_resp_set_type(req, "multipart/x-mixed-replace; boundary=frame");
  if (res != ESP_OK) return res;

  while (true) {
    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return ESP_FAIL;
    }

    char buf[64];
    size_t hlen = snprintf(buf, sizeof(buf),
      "--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n",
      fb->len);

    res = httpd_resp_send_chunk(req, buf, hlen);
    if (res == ESP_OK) res = httpd_resp_send_chunk(req, (const char *)fb->buf, fb->len);
    if (res == ESP_OK) res = httpd_resp_send_chunk(req, "\r\n", 2);

    esp_camera_fb_return(fb);
    if (res != ESP_OK) break;

    delay(30); // ~10–15 FPS
  }
  return res;
}

void startCameraServer() {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 81;

  httpd_uri_t stream_uri = {
    .uri       = "/stream",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };

  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &stream_uri);
  }
}

// ===================
// SETUP
// ===================
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  // Camera config
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size   = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count     = 2;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera init failed");
    return;
  }

  // ===================
  // WIFI AP + STA
  // ===================
  WiFi.mode(WIFI_AP_STA);

  // Static IP for STA
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Failed to configure static IP");
  }

  // Connect to existing Wi-Fi (STA)
  WiFi.begin(ssid, password);

  // Create ESP32 AP as fallback
  WiFi.softAP("ESP32_CAM_AP", "12345678");  // SSID and password of ESP32 AP

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("ESP32 STA IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP32 AP IP: ");
  Serial.println(WiFi.softAPIP());

  startCameraServer();

  Serial.println("MJPEG stream ready:");
  Serial.print("STA URL: http://");
  Serial.print(WiFi.localIP());
  Serial.println(":81/stream");
  Serial.print("AP URL: http://");
  Serial.print(WiFi.softAPIP());
  Serial.println(":81/stream");
}

void loop() {
  delay(1000);
}