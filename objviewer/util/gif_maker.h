#ifndef OBJVIEWER_UTIL_GIFMAKER_H_
#define OBJVIEWER_UTIL_GIFMAKER_H_

#include <QImage>
#include <QThread>
#include <utility>

namespace objv {

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

}  // namespace objv

#endif  // OBJVIEWER_UTIL_GIFMAKER_H_
