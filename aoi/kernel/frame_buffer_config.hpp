#pragma once

#include <stdint.h>

enum PixelFormat {
  kPixelRGBResv8BitPerColor,
  kPixelBGRResv8BitPerColor,
};

struct FrameBufferConfig {
  uint8_t* frame_buffer;
  uint32_t pixels_per_scan_line; // 余白を含めた横のピクセル数（余白が無ければhorizontal_resolutionと同じになる）
  uint32_t horizontal_resolution;
  uint32_t vertical_resolution;
  enum PixelFormat pixel_format;
};