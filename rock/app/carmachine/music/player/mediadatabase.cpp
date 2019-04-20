//#include "mediadatabase.h"
//#include <QtSql/qsqlquery.h>
//#include <QVariant>
//#include <QSqlError>

//// 连接music数据库
//void mediaDataBase::connectSongInfo()
//{
//    QSqlDatabase datebase;
//    if(QSqlDatabase::contains("qt_sql_default_connection"))
//        datebase = QSqlDatabase::database("qt_sql_default_connection");
//    else
//        datebase = QSqlDatabase::addDatabase("QSQLITE");
//    datebase.setDatabaseName("SongDateBase.db");
//    datebase.open();
//    datebase.exec(QString("create table if not exists songinfo(id INT ,songname TEXT,songurl TEXT,duration TEXT)"));
//}

//void mediaDataBase::addSong(const QString& songname,const QString& url,const QString& duration)
//{
//    connectSongInfo();
//    QSqlQuery query;
//    query.prepare(QString("select * from songinfo where id = (select max(id) from songinfo)"));
//    query.exec();

//    int  index=0;
//    while(query.next()) // 取最大值
//    {
//        index= query.value("id").toInt();
//        index++;
//    }

//    query.prepare(QString("INSERT INTO songinfo(id,songname,songurl,duration)"
//                          "VALUES (:id,:songname,:songurl,:duration)"));
//    query.bindValue(":id", index);
//    query.bindValue(":songname", songname);
//    query.bindValue(":songurl", url);
//    query.bindValue(":duration", duration);
//    query.exec();
//}

//QVector<QStringList> mediaDataBase::getSongInfo()
//{
//    connectSongInfo();
//    QStringList list1;
//    QStringList list2;
//    QStringList list3;

//    QSqlQuery sql_query;
//    sql_query.prepare(QString("select * from songinfo order by id"));

//    if(!sql_query.exec())
//    {
////        qDebug()<<sql_query.lastError();
//    }
//    else
//    {
//        while(sql_query.next())
//        {
//            QString songname = sql_query.value("songname").toString();
//            QString songurl = sql_query.value("songurl").toString();
//            QString songdur=sql_query.value("duration").toString();

//            list1<<songname;
//            list2<<songurl;
//            list3<<songdur;
//        }
//    }
//    QVector<QStringList> vec;
//    vec<<list1<<list2<<list3;
//    return vec;
//}
