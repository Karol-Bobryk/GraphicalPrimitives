#include "serializationhub.h"
#include <QFileDialog>
#include <QPushButton>

SerializationHub::SerializationHub(QWidget *parent)
    : QWidget{parent}
    , layout{new QHBoxLayout(this)}
{
    auto load_button = new QPushButton("Load");
    layout->addWidget(load_button);
    layout->addSpacing(5);
    auto save_button = new QPushButton("Save");
    layout->addWidget(save_button);

    connect(load_button, &QPushButton::clicked, this, &SerializationHub::loadLayoutPressed);
    connect(save_button, &QPushButton::clicked, this, &SerializationHub::saveLayoutPressed);
}

void SerializationHub::saveLayoutPressed()
{
    QString filter = "JSON files (*.json)";
    QString caption = "Save layout to a file";
    QUrl file_url = QFileDialog::getSaveFileUrl(this, caption, QUrl(), filter);

    if (file_url.isEmpty())
        return;

    emit saveLayoutRequested(file_url);
}

void SerializationHub::loadLayoutPressed()
{
    QString filter = "JSON files (*.json)";
    QString caption = "Load layout from a file";
    QUrl file_url = QFileDialog::getOpenFileUrl(this, caption, QUrl(), filter);

    if (file_url.isEmpty())
        return;

    emit loadLayoutRequested(file_url);
}
