#ifndef GIFMAKER_H
#define GIFMAKER_H

#include <QFileDialog>
#include <QThread>

class GifMaker : public QThread {
  Q_OBJECT
 public:
  GifMaker(QImage &frame);

 private:
  QImage &frame_;
  void run() override;
 signals:
  void MakinGif();
  void GifDone();
};

inline GifMaker::GifMaker(QImage &frame) : frame_(frame) {}

#endif  // GIFMAKER_H
