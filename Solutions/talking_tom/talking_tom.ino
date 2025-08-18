#include <Arduino.h>
#include "driver/i2s.h"

// Pin mapping (based on your wiring)
#define I2S_BCLK   26   // SCK shared
#define I2S_LRCL   25   // WS shared
#define I2S_DOUT   27   // MAX98357A DIN
#define I2S_DIN    34   // INMP441 DOUT

#define I2S_SAMPLE_RATE   16000   // Lower sample rate to match INMP441
#define I2S_BUFFER_SIZE   1024

// Configure I2S for mic (RX) and speaker (TX)
void i2s_init() {
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = I2S_BUFFER_SIZE
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRCL,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_DIN
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_set_clk(I2S_NUM_0, I2S_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

void setup() {
  Serial.begin(115200);
  i2s_init();
  Serial.println("I2S mic-to-speaker passthrough started...");
}

void loop() {
  static int16_t buffer_in[I2S_BUFFER_SIZE];
  static int16_t buffer_out[I2S_BUFFER_SIZE];
  size_t bytes_read = 0;
  size_t bytes_written = 0;

  // Read raw data from mic (16-bit samples)
  i2s_read(I2S_NUM_0, (char *)buffer_in, sizeof(buffer_in), &bytes_read, portMAX_DELAY);

  int samples_read = bytes_read / 2;

  // Apply simple gain and clamp
  for (int i = 0; i < samples_read; i++) {
    int32_t sample = buffer_in[i] * 5;    // gain
    if (sample > 32767) sample = 32767;
    if (sample < -32768) sample = -32768;
    buffer_out[i] = (int16_t)sample;
  }

  // Write to speaker
  i2s_write(I2S_NUM_0, (const char *)buffer_out, samples_read * sizeof(int16_t), &bytes_written, portMAX_DELAY);
}