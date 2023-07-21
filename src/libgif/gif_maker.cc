#include "gif_maker.h"

#include "gif.h"

void GifMaker::run() {
  QString file_name = QDir::homePath() + "/gif_image.gif";
  if (QFile::exists(file_name)) {
    QFile::remove(file_name);
  }
  int delay = 100;
  GifWriter gif_wr;
  GifBegin(&gif_wr, file_name.toStdString().c_str(), 640, 480, 1, 8, false);
  for (int timer = 0; timer <= 5000; timer += delay) {
    emit MakinGif();
    GifWriteFrame(&gif_wr,
                  m_frame.convertToFormat(QImage::Format_Indexed8)
                      .convertToFormat(QImage::Format_RGBA8888)
                      .constBits(),
                  640, 480, 1, 8, false);
    QThread::msleep(delay);
  }
  GifEnd(&gif_wr);
  emit GifDone();
}
