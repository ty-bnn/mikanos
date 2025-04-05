/**
 * @file main.cpp
 * 
 * カーネル本体のプログラムを書いたファイル
 */

#include <cstdint>
#include <cstddef>
#include <cstdio>

#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "console.hpp"

/**
 * 配置newの宣言
 */
void* operator new(size_t size, void* buf) {
  return buf;
}

/**
 * deleteを宣言しないとコンパイルエラー
 */
void operator delete(void* obj) noexcept {
}

/**
 * 予めPixelWriterを格納する領域を確保しておく
 * mallocなどの動的にメモリを確保する機能が使えないため予め静的に確保する必要がある
 * （KernelMain内で定義してスタック上に登録しておいてもOK）
 */
char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

char console_buf[sizeof(Console)];
Console* console;

/**
 * カーネル内ならどこからでもメッセージを出力できる関数
 */
int printk(const char* format, ...) {
  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsprintf(s, format, ap);
  va_end(ap);

  console->PutString(s);
  return result;
}

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
  switch (frame_buffer_config.pixel_format) {
    case kPixelRGBResv8BitPerColor:
      pixel_writer = new(pixel_writer_buf)
        RGBResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
    case kPixelBGRResv8BitPerColor:
      pixel_writer = new(pixel_writer_buf)
        BGRResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
  }

  for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
  for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
      pixel_writer->Write(x, y, {255, 255, 255});
    }
  }

  console = new(console_buf) Console{*pixel_writer, {0, 0, 0}, {255, 255, 255}};

  for (int i = 0; i < 27; ++i) {
    printk("printk: %d\n", i);
  }

  while (1) __asm__("hlt");
}
