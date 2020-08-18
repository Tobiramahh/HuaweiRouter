#include "mainwindow.h"
#include <thread>
#include <node.h>
#include <QApplication>


void setLeftToSendRight(Channel& left, Channel& right) {
    using namespace std;
    thread initRecieverThread(&Channel::initReciever, &left);
    thread initSenderThread(&Channel::initSender, &right);
    initRecieverThread.join();
    initSenderThread.join();
}

void connectChannels(Channel& left, Channel& right) {
    using namespace std;
    setLeftToSendRight(left, right);
    setLeftToSendRight(right, left);
}

void startLeftToSendRight(Channel& left, Channel& right) {
    using namespace std;
        std::thread startSendingThread
                (&Channel::startSending, left);
        std::thread startRecievingThread
                (&Channel::startRecieving, right);
        startSendingThread.detach();
        startRecievingThread.detach();
}

std::string firstStorageName = "firstStorage.txt";
std::string secondStorageName = "secondStorage.txt";
std::string firstDataName = "firstData.txt";
std::string secondDataName = "secondData.txt";
void initFiles() {
    using namespace std;

    ofstream firstStorage(firstStorageName);
    ofstream secondStorage(secondStorageName);
    string nineA = "AAAAAAAAA";
    string nineB = "BBBBBBBBB";
    string nineC = "CCCCCCCCC";
    string nineD = "DDDDDDDDD";
    string firstData;
    string secondData;
    for(int i = 0; i < 10000; ++i) {
        firstData += nineA + nineA + nineB + nineA;
        secondData += nineC + nineD + nineD;
    }
    firstStorage << firstData;
    secondStorage << secondData;
}

int main(int argc, char *argv[]) {
    using namespace std;
    int port = 16006;
    int nodesAmount = 3;
    vector<pair<int,int>> adjList = { {0, 1}, {1, 2}, {0, 2}};

    Network n(adjList, port, nodesAmount);

    n.connectNetwork();
    n.startDebugNetwork();
    while (true) {

    }
}

//int main(int argc, char *argv[]) {   network works too
//    using namespace std;
//    int port = 31006;
//    int nodesAmount = 3;
//    vector<pair<int,int>> adjList = { {0, 1}, {1, 2}, {0, 2}};

//    Network n(adjList, port, nodesAmount);

//    n.connectNetwork();
//    while (true) {

//    }
//}


//int main(int argc, char *argv[]) {                     TEST DAT TIS ALL WORKIN
//    using namespace std;
//    initFiles();
//    int port1 = 7000;
//    int port2 = 8000;
//    Channel left(port1, port2);
//    Channel right(port2, port1);
//    connectChannels(left, right);

//    std::thread t1(&Channel::startSending, left);
//    std::thread t2(&Channel::startRecieving, right);
//    t1.detach();
//    t2.detach();
//    std::thread t3(&Channel::startSending, right);
//    std::thread t4(&Channel::startRecieving, left);
//    t3.detach();
//    t4.detach();
//    while (true) {

//    }
//}
