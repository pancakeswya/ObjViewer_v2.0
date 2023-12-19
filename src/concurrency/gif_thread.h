#ifndef SRC_CONCURRENCY_GIF_THREAD_H_
#define SRC_CONCURRENCY_GIF_THREAD_H_

#include <QImage>
#include <QString>
#include <QThread>

namespace objv {

class GifThread : public QThread {
  Q_OBJECT
 public:
  GifThread(const QImage &frame, QString path);
 signals:
  void Failed();
  void Running();

 private:
  const QImage &frame_;
  QString path_;
  void run() override;
};

inline GifThread::GifThread(const QImage &frame, QString path)
    : frame_(frame), path_(std::move(path)) {}

}  // namespace objv

#endif  // SRC_CONCURRENCY_GIF_THREAD_H_
