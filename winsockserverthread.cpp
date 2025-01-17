// Server sends stuff

// Protocol: TCP
#include "winsockserverthread.h"
//#include <QTextCodec>
#include <QtConcurrent>

int bufferSize;
using namespace std;

WinSockServerThread::WinSockServerThread() {

}

void WinSockServerThread::resolveLocalAddress() {
    // ↓ TESTING ↓
    char ac[80];
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        qDebug() << "Exiting: Error" << WSAGetLastError() << "when getting local host name." << endl;
        return;
    }
    qDebug() << "Host name is" << ac;
    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        qDebug() << "Exiting: Bad host lookup.";
        return;
    }
    int sizeOfList=sizeof(phe->h_addr_list)/sizeof(phe->h_addr_list[0]);
    struct in_addr addr;
    if (sizeOfList>2) {
        memcpy(&addr, phe->h_addr_list[2], sizeof(struct in_addr));
        qDebug() << "Address:" << inet_ntoa(addr);
    }
    // ↑ TESTING ↑
}

void WinSockServerThread::init() {
    qDebug() << "°º¤ø,¸¸,ø¤º°`°º¤ø,SERVER,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸";
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        qDebug() << "WSAStartup failed: " << iResult;
    } else {
        qDebug() << "WSAStartup succeeded!";
    }
    ConnectSocket = INVALID_SOCKET;
    // 1.
    //    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    QByteArray arrayP = myport.toLocal8Bit();
    char* bufferP = arrayP.data();
    iResult = getaddrinfo(NULL, bufferP, &hints, &result);


    // ↓ TESTING ↓
    //    char ac[80];
    //    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
    //        qDebug() << "Exiting: Error" << WSAGetLastError() << "when getting local host name." << endl;
    //        return;
    //    }
    //    qDebug() << "Host name is" << ac;
    //    struct hostent *phe = gethostbyname(ac);
    //    if (phe == 0) {
    //        qDebug() << "Exiting: Bad host lookup.";
    //        return;
    //    }
    //    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
    //        struct in_addr addr;
    //        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
    //        qDebug() << "Address" << i << ":" << inet_ntoa(addr);
    //    }
    // ↑ TESTING ↑


    if (iResult != 0) {
        qDebug() << "getaddrinfo failed: " << iResult;
        WSACleanup();
        return;
    }
    // 2.
    ListenSocket = INVALID_SOCKET;
    // 3. Create a SOCKET for the server to listen for client connections
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    // 4.
    if (ListenSocket == INVALID_SOCKET) {
        qDebug() << "Error at socket(): " << WSAGetLastError();
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
    // 5. Setup the TCP listening socket: DO NOT HARD CODE
    // ↓ TESTING ↓
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    QByteArray array = myip.toLocal8Bit();
    char* buffer = array.data();
    server.sin_addr.s_addr = inet_addr(buffer);
    server.sin_port = htons(myport.toInt());
    // ↑ TESTING ↑
    iResult = ::bind(ListenSocket, (struct sockaddr *)&server, (int)result->ai_addrlen); //result->ai_addr
    if (iResult == SOCKET_ERROR) {
        qDebug() << "bind failed with error: " << WSAGetLastError();
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    freeaddrinfo(result);
    // 6. To listen on a socket: "Will somebody please call me?"
    if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
        qDebug() << "Listen failed with error: " << WSAGetLastError();
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    qDebug() << "Winsock server has been successfully set up.";
    emit connected(myip, myport);
}

void WinSockServerThread::run() {
    session();
//    QFuture<void> future0 = QtConcurrent::run(this, &WinSockServerThread::session);
//    QFuture<void> future1 = QtConcurrent::run(this, &WinSockServerThread::session);
//    QFuture<void> future2 = QtConcurrent::run(this, &WinSockServerThread::session);
}

void WinSockServerThread::session() {
    // 7. Accept a client socket: "Thank you for calling port 3490."
    ClientSocket = INVALID_SOCKET;
    qDebug() << "All is well";
    //accept() is a blocking function, meaning that it will not finish until it accept()s a connection or an error occurs
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        qDebug() << "accept failed: " << WSAGetLastError();
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    qDebug() << "Woah! Don't panic.";

    ClientSocket0 = INVALID_SOCKET;
    qDebug() << "All is well";
    //accept() is a blocking function, meaning that it will not finish until it accept()s a connection or an error occurs
    ClientSocket0 = accept(ListenSocket, NULL, NULL);
    if (ClientSocket0 == INVALID_SOCKET) {
        qDebug() << "accept failed: " << WSAGetLastError();
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }


    // ***CRITICAL ERROR HERE: Receiving and Sending Data on the Server***
    //    char recvbuf[DEFAULT_BUFLEN];

    // Receive until the peer shuts down the connection
//    strcpy(sendbuf, QString("test").toStdString().c_str());
//    do {
//        iSendResult = send(ClientSocket, sendbuf, sizeof(sendbuf), 0);
//    } while (1);
    Sleep(4000);
    setMessageByPath("C:/Users/Alexandre Poon/Documents/sans_titre/example.json");



//    do {

//        iResult = recv(ClientSocket, recvbuf, sizeof(recvbuf), 0);
//        if (iResult > 0) {
//            //            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//            //            QString field = codec->toUnicode(recvbuf).trimmed();
//            QString field=recvbuf;
//            field=field.mid(0,field.indexOf("\t"));
//            qDebug() << "Receives (server):" << field << "(" << iResult << "bytes)";
//            this->label->setText(field);
//            // Echo the buffer back to the sender
//            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
//            if (iSendResult == SOCKET_ERROR) {
//                qDebug() << "send failed: " << WSAGetLastError();
//                closesocket(ClientSocket);
//                WSACleanup();
//                return;
//            }
//            qDebug() << "Bytes echoed (server): " << iSendResult;
//        } else if (iResult == 0) {
//            //            qDebug() << "Connection closing...";
//        } else {
//            qDebug() << "recv failed: " << WSAGetLastError();
//            closesocket(ClientSocket);
//            WSACleanup();
//            return;
//        }
//    } while (iResult > 0);
//    qDebug() << "°º¤ø,¸¸,ø¤º°`°º¤ø,SERVER-END,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸";
//    QString done;
//    emit resultReady(done);
}

void WinSockServerThread::setMessage(QString message) {
    message.append("\t");
    //    QByteArray tmp1=message.toUtf8();
    sendbuf=(char *) malloc(sizeof(message.toStdString().c_str()));
    strcpy(sendbuf, message.toStdString().c_str());
    qDebug() << "Original msg: " << sendbuf << "(" << sizeof(message.toStdString().c_str()) << "bytes)";
}

void WinSockServerThread::setMessageByPath(QString path) {
    qDebug() << path;
    QFile plainText(path);
    if (!plainText.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    while (plainText.size()>plainText.pos()+256) { //!plainText.atEnd()
//        char *buffer = (char *) malloc(256);
//        plainText.read(buffer, 256);
//        qDebug() << buffer;
//        free(buffer);
        sendbuf = (char *) malloc(256);
        plainText.read(sendbuf, 256);
//        if (plainText.size()>plainText.pos()+256) {
//            plainText.seek(plainText.pos()+256);
//        } else break;
        qDebug() << QLatin1String(sendbuf).left(256) << "\n**************\n";
        qDebug() << "Size:" << QLatin1String(sendbuf).size();
        sendPart(256);
        free(sendbuf);
    }
    int howManyLeft=plainText.size()-plainText.pos()-8;
    sendbuf = (char *) malloc(howManyLeft);
    plainText.read(sendbuf, howManyLeft);
    qDebug() << QLatin1String(sendbuf).left(howManyLeft) << "\n**************\n";
    qDebug() << "Size:" << QLatin1String(sendbuf).size();
    sendPart(howManyLeft);
    free(sendbuf);

    do {
    recvbuf = (char *) malloc(256);
    iResult = recv(ClientSocket, recvbuf, 256, 0);
    if (iResult > 0) { //Exit condition?
        qDebug() << "Server received command:" << QString::fromUtf8(recvbuf).left(iResult) << "(" << iResult << "bytes)\n\n\n";
        QString wavCrumbsPath=QString::fromUtf8(recvbuf).left(iResult).remove("REQUEST");
        sendWavCrumbs(wavCrumbsPath);
        free(recvbuf);
    } else if (iResult == 0)
        qDebug() << "Connection closed";
    else
        qDebug() << "recv failed: " << WSAGetLastError();
    } while (1);
}

void WinSockServerThread::sendWavCrumbs(QString path) {
    WavDeassembler *wavDeassembler=new WavDeassembler();
    wavDeassembler->setPath(path);
    wavDeassembler->start();
    //There should be a slot to receive mmioBuffer and send it to clients:
    connect(wavDeassembler, &WavDeassembler::fmtDataPrepared, this, &WinSockServerThread::onFmtDataExtracted);
    connect(wavDeassembler, &WavDeassembler::partitionMade, this, &WinSockServerThread::onPartitionMade);
    qDebug() << "sendWavCrumbs";
}

void WinSockServerThread::onFmtDataExtracted(QList<QString> *fmtList) {
    qDebug() << "FMT data extracted";
    for (int i=0; i<fmtList->length(); i++) {
//        sendbuf=(char *) malloc(fmtList->at(i).length());
        strcpy(sendbuf, fmtList->at(i).toStdString().c_str());
        sendPart(fmtList->at(i).length());
//        free(sendbuf);
    }
    bufferSize=fmtList->at(7).toInt();
//    qDebug() << QString::fromUtf8(partition).left(bufSize);
//    sendbuf=partition;
//    sendPart(strlen(partition));
}

void WinSockServerThread::onPartitionMade(char *partition) {
    qDebug() << "Partition made";
    qDebug() << "Second:" << QString::fromLatin1(partition);
//    qDebug() << QString::fromUtf8(partition).left(bufSize);
    sendbuf=partition;
    sendPart(bufferSize); //strlen(partition)
}

void WinSockServerThread::sendPart(int bufSize) {
    iResult=1;
    if (iResult > 0) {
        qDebug() << "Hello!";
        //            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        //            QString field = codec->toUnicode(recvbuf).trimmed();
//        QString field=recvbuf;
//        field=field.mid(0,field.indexOf("\t"));
//        qDebug() << "Receives (server):" << field << "(" << iResult << "bytes)";
//        this->label->setText(field);
        // Echo the buffer back to the sender
        iSendResult = send(ClientSocket, sendbuf, bufSize, 0);
//        iSendResult = send(ClientSocket0, sendbuf, bufSize, 0);
        if (iSendResult == SOCKET_ERROR) {
            qDebug() << "send failed: " << WSAGetLastError();
            closesocket(ClientSocket);
            WSACleanup();
            return;
        }
        qDebug() << "Bytes sent (server): " << iSendResult;
    }
}

void WinSockServerThread::setNextLabelPointer(QLabel *label) {
    this->label=label;
}

void WinSockServerThread::setIpLastFourBits(int ip) {
    myip = QString("127.0.0.%1").arg(ip);
    qDebug() << myip << ip;
    //    //1024 through 49151
}

void WinSockServerThread::setPortNumber(int port) {
    myport = QString::number(port);
}
