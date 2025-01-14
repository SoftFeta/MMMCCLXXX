#ifndef GENIUSMANAGER_H
#define GENIUSMANAGER_H

#include <QtNetwork>
#include <QtWidgets>
//#include <QtWebEngineWidgets>

class GeniusManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    GeniusManager(QLabel *label, QLabel *songArtL, QLabel *artistPhotoL, QLabel *albumArtL, QLabel *albumTitleL, QLabel *releaseDateL, QLabel *albumInfoL, QString artist, QString songTitle);
private slots:
    void result();
    void httpFinished();
    void artistPhotoFetched();
    void songArtFetched();
    void albumArtFetched();
    void getSongDetails();
    void getAlbumInfo();
private:
    void recursion(QJsonArray array);
    QString info;
};

#endif // GENIUSMANAGER_H
