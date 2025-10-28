#include "mainwindow.h"

#include <QApplication>
//#include <QVector>
//#include <iostream>
//#include "json/json.h"

int main(int argc, char *argv[])
{
//    Json::Reader reader;
//    Json::Value root;
//    reader.parse(R"({"Age": 20, "Name": "colin"})", root);
//    std::cout << root["Age"] << std::endl;
//    root["Age"] = 234;
//    std::cout << root["Name"] << std::endl;
//    return 0;

//    QVector<double> data;
//    data.resize(10);
//    for( int i=0 ; i<10 ; i++ )
//        data[i] = i;
//    data.resize(4);
//    for( int i=0 ; i<data.length() ; i++ )
//        std::cout << data[i] << std::endl;
//    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
