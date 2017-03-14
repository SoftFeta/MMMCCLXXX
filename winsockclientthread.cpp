#include "winsockclientthread.h"

//void WinSockClientThread::setPortNumber() {
//    //1024 through 49151
//}

void WinSockClientThread::run() {
    //    addrinfo.sin_addr.s_addr = INADDR_ANY;

    QString done;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        qDebug() << "getaddrinfo failed: " << iResult;
        WSACleanup();
        return;
    }
    qDebug() << "Winsock client has been successfully set up.";
    // Attempt to connect to the first address returned by the call to getaddrinfo
    ptr=result;
    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        qDebug() << "Error at socket(): " << WSAGetLastError();
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
    iResult = ::connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }
    freeaddrinfo(result);
    if (ConnectSocket == INVALID_SOCKET) {
        qDebug() << "Unable to connect to server!";
        WSACleanup();
        return;
    }
    //***Receiving and Sending Data on the Client***
    int recvbuflen = DEFAULT_BUFLEN;

//    char *sendbuf = QString("I am a client, short and stout").toLatin1().data();
    QByteArray tmp=QString::fromUtf8("2017年2月22號，天文學家宣布圍繞 TRAPPIST-1 嘅外行星加多四個。\0").toUtf8();
    char *sendbuf = tmp.data();
    qDebug()<<"Fuck:"<<sendbuf;
//    char *sendbuf = QString("2017年2月22號，天文學家宣布圍繞 TRAPPIST-1 嘅外行星加多四個。").toUtf8().data();

    char recvbuf[DEFAULT_BUFLEN];

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int) strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        qDebug() << "send failed: " << WSAGetLastError();
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }

    qDebug() << "Bytes Sent: " << iResult;

    // shutdown the connection for sending since no more data will be sent
    // the client can still use the ConnectSocket for receiving data
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        qDebug() << "shutdown failed: " << WSAGetLastError();
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }

    // Receive data until the server closes the connection
    do {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            qDebug() << "Client received message:" << QString::fromUtf8(recvbuf) << "(" << iResult << "bytes)";
        else if (iResult == 0)
            qDebug() << "Connection closed";
        else
            qDebug() << "recv failed: " << WSAGetLastError();
    } while (iResult > 0);

    emit resultReady(done);
}

void WinSockClientThread::sendMessage(QByteArray message) {

}
