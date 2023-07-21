#ifndef GIFMAKER_H
#define GIFMAKER_H

#include <QFileDialog>
#include <QThread>

class GifMaker : public QThread {
  Q_OBJECT
 public:
  GifMaker(QImage &frame);

 private:
  QImage &m_frame;
  void run() override;
 signals:
  void MakinGif();
  void GifDone();
};

inline GifMaker::GifMaker(QImage &frame) : m_frame(frame) {}

#endif  // GIFMAKER_H
