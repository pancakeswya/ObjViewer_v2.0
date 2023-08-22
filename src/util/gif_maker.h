#ifndef GIFMAKER_H
#define GIFMAKER_H

#include <QFileDialog>
#include <QThread>
#include <utility>

namespace obj {

class GifMaker : public QThread {
  Q_OBJECT
 public:
  GifMaker(QImage &frame, QString path);

 private:
  QImage &frame_;
  QString path_;
  void run() override;
 signals:
  void GifFailed();
  void MakinGif();
};

inline GifMaker::GifMaker(QImage &frame, QString path) : frame_(frame), path_(std::move(path)) {}

} // namespace obj

#endif  // GIFMAKER_H
