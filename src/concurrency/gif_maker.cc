#include "concurrency/gif_maker.h"
#include "external/gif.h"

namespace objv {

void GifMaker::run() {
  int delay = 100;
  GifWriter gif_wr;
  bool is_savable =
      GifBegin(&gif_wr, path_.toStdString().c_str(), 640, 480, 1, 8, false);
  if (!is_savable) {
    emit GifFailed();
    return;
  }
  for (int timer = 0; timer <= 5000; timer += delay) {
    emit MakinGif();
    bool is_written =
        GifWriteFrame(&gif_wr,
                      frame_.convertToFormat(QImage::Format_Indexed8)
                          .convertToFormat(QImage::Format_RGBA8888)
                          .constBits(),
                      640, 480, 1, 8, false);
    if (!is_written) {
      emit GifFailed();
      return;
    }
    QThread::msleep(delay);
  }
  bool is_succeed = GifEnd(&gif_wr);
  if (!is_succeed) {
    emit GifFailed();
  }
}

}  // namespace objv
