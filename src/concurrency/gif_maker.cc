#include "concurrency/gif_maker.h"

#include "third_party/gif.h"
#include "types/gif_settings.h"

namespace objv {

void GifMaker::run() {
  GifWriter gif_wr;
  bool is_savable = GifBegin(&gif_wr, path_.toStdString().c_str(), kGifWidth,
                             kGifHeight, kGifDelay, kGifBitWidth, kGifDither);
  if (!is_savable) {
    emit GifFailed();
    return;
  }
  for (unsigned int timer = 0; timer <= kGifDuration; timer += kGifFrameDelay) {
    emit MakinGif();
    bool is_written = GifWriteFrame(
        &gif_wr,
        frame_.convertToFormat(QImage::Format_Indexed8)
            .convertToFormat(QImage::Format_RGBA8888)
            .constBits(),
        kGifWidth, kGifHeight, kGifDelay, kGifBitWidth, kGifDither);
    if (!is_written) {
      emit GifFailed();
      return;
    }
    QThread::msleep(kGifFrameDelay);
  }
  bool is_succeed = GifEnd(&gif_wr);
  if (!is_succeed) {
    emit GifFailed();
  }
}

}  // namespace objv
