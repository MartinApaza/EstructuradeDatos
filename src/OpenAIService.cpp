#include "OpenAIService.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QUrl>

OpenAIService::OpenAIService(QObject* parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(
        manager,
        &QNetworkAccessManager::finished,
        this,
        &OpenAIService::procesarRespuesta
    );
}

void OpenAIService::setApiKey(const QString& key)
{
    apiKey = key.trimmed();
}

bool OpenAIService::tieneApiKey() const
{
    return !apiKey.isEmpty();
}

void OpenAIService::preguntar(const QString& mensaje)
{
    if (apiKey.isEmpty())
    {
        emit errorOcurrido(
            "No hay una API Key configurada."
        );
        return;
    }

    QUrl url(
        QString(
            "https://generativelanguage.googleapis.com/v1beta/models/"
            "gemini-2.5-flash:generateContent?key=%1"
        ).arg(apiKey)
    );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
    );

    QJsonObject root;

    QJsonArray contents;

    QJsonObject content;

    QJsonArray parts;

    QJsonObject part;

    part["text"] =
        "Eres un asistente virtual experto de un gimnasio premium. "
        "Respondes en español de forma motivadora, breve y práctica "
        "sobre entrenamiento, nutrición y hábitos saludables.\n\n"
        + mensaje;

    parts.append(part);

    content["parts"] = parts;

    contents.append(content);

    root["contents"] = contents;

    QByteArray data =
        QJsonDocument(root).toJson();

    manager->post(request, data);
}

void OpenAIService::procesarRespuesta(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();

    if (reply->error() != QNetworkReply::NoError)
    {
        QString detalle = reply->errorString();

        QJsonDocument doc =
            QJsonDocument::fromJson(data);

        if (doc.isObject())
        {
            QJsonObject obj = doc.object();

            if (obj.contains("error"))
            {
                QJsonObject errorObj =
                    obj["error"].toObject();

                QString apiMsg =
                    errorObj["message"].toString();

                if (!apiMsg.isEmpty())
                    detalle = apiMsg;
            }
        }

        emit errorOcurrido(detalle);

        reply->deleteLater();
        return;
    }

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    QJsonObject root =
        doc.object();

    QString texto;

    if (root.contains("candidates"))
    {
        QJsonArray candidates =
            root["candidates"].toArray();

        if (!candidates.isEmpty())
        {
            QJsonObject candidate =
                candidates[0].toObject();

            QJsonObject content =
                candidate["content"].toObject();

            QJsonArray parts =
                content["parts"].toArray();

            if (!parts.isEmpty())
            {
                texto =
                    parts[0]
                    .toObject()["text"]
                    .toString();
            }
        }
    }

    if (texto.isEmpty())
    {
        texto =
            "No se recibió una respuesta válida de Gemini.";
    }

    emit respuestaRecibida(
        texto.trimmed()
    );

    reply->deleteLater();
};
