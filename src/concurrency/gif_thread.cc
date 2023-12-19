#include "concurrency/gif_thread.h"

#include "base/gif_settings.h"
#include "third_party/gif.h"

namespace objv {

void GifThread::run() {
  GifWriter gif_wr;
  bool is_savable = GifBegin(&gif_wr, path_.toStdString().c_str(), kGifWidth,
                             kGifHeight, kGifDelay, kGifBitWidth, kGifDither);
  if (!is_savable) {
    emit Failed();
    return;
  }
  for (unsigned int timer = 0; timer <= kGifDuration; timer += kGifFrameDelay) {
    emit Running();
    bool is_written = GifWriteFrame(
        &gif_wr, frame_.convertToFormat(QImage::Format_RGBA8888).constBits(),
        kGifWidth, kGifHeight, kGifDelay, kGifBitWidth, kGifDither);
    if (!is_written) {
      emit Failed();
      return;
    }
    QThread::msleep(kGifFrameDelay);
  }
  bool is_succeed = GifEnd(&gif_wr);
  if (!is_succeed) {
    emit Failed();
  }
}

}  // namespace objv
