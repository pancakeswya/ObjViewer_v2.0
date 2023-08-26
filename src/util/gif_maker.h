#ifndef OBJVIEWER_V2_SRC_UTIL_GIFMAKER_H
#define OBJVIEWER_V2_SRC_UTIL_GIFMAKER_H

#include <QFileDialog>
#include <QThread>
#include <utility>

namespace obj {

class GifMaker : public QThread {
  Q_OBJECT
 public:
  GifMaker(const QImage &frame, QString path);

 private:
  const QImage &frame_;
  QString path_;
  void run() override;
 signals:
  void GifFailed();
  void MakinGif();
};

inline GifMaker::GifMaker(const QImage &frame, QString path)
    : frame_(frame), path_(std::move(path)) {}

}  // namespace obj

#endif  // OBJVIEWER_V2_SRC_UTIL_GIFMAKER_H
