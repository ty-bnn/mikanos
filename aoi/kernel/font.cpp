/**
 * @file font.cpp
 *
 * フォント描画のプログラムを集めたファイル.
 */

#include "font.hpp"

// 他のobjectファイル上の変数を参照（変数名はobjcopyの時に決まるため変更できない）
extern const uint8_t _binary_hankaku_bin_start;
extern const uint8_t _binary_hankaku_bin_end;
extern const uint8_t _binary_hankaku_bin_size;

/**
 * フォントのアドレスを返す。
 * 1フォント=1byte(8bit)×16で構成
 */
const uint8_t* GetFont(char c) {
  auto index = 16 * static_cast<unsigned int>(c);
  if (index >= reinterpret_cast<uintptr_t>(&_binary_hankaku_bin_size)) {
    return nullptr;
  }
  // uint8_t*型に整数値を足すと1byte(8bit)単位でアドレスが加算される
  return &_binary_hankaku_bin_start + index;
}

void WriteAscii(PixelWriter& writer, Vector2D<int> pos, char c, const PixelColor& color) {
  const uint8_t* font = GetFont(c);
  if (font == nullptr) {
    return;
  }
  for (int dy = 0; dy < 16; ++dy) {
    for (int dx = 0; dx < 8; ++dx) {
      if ((font[dy] << dx) & 0x80u) {
        writer.Write(pos + Vector2D<int>{dx, dy}, color);
      }
    }
  }
}

void WriteString(PixelWriter& writer, Vector2D<int> pos, const char* s, const PixelColor& color) {
  for (int i = 0; s[i] != '\0'; ++i) {
    WriteAscii(writer, pos + Vector2D<int>{8 * i, 0}, s[i], color);
  }
}