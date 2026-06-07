#pragma once

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class OpenAIService : public QObject
{
    Q_OBJECT

public:
    explicit OpenAIService(QObject* parent = nullptr);

    void setApiKey(const QString& key);

    bool tieneApiKey() const;

    void preguntar(const QString& mensaje);

signals:
    void respuestaRecibida(const QString& texto);

    void errorOcurrido(const QString& detalle);

private slots:
    void procesarRespuesta(QNetworkReply* reply);

private:
    QNetworkAccessManager* manager;

    QString apiKey;
};