#ifndef SERIALIZATIONHUB_H
#define SERIALIZATIONHUB_H

#include <QHBoxLayout>
#include <QWidget>

class SerializationHub : public QWidget
{
    Q_OBJECT
public:
    explicit SerializationHub(QWidget *parent = nullptr);
    QHBoxLayout *layout;

signals:
    void saveLayoutRequested(const QUrl &file_url);
    void loadLayoutRequested(const QUrl &file_url);
private slots:
    void saveLayoutPressed();
    void loadLayoutPressed();
};

#endif // SERIALIZATIONHUB_H
