#ifndef SQLITEDBOPERATOR_H
#define SQLITEDBOPERATOR_H


#include <QSqlDatabase>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class SqliteDbOperator
{
public:
    // 打开数据库
    static bool openDb(QString dbName, QSqlDatabase& db);

    // 查询模板
    template<typename T>static QList<T> query(QSqlDatabase& db, QString& sql, QList<QVariant> params, T(*fullFunc)(QSqlQuery&));

    template<typename T>static T queryOne(QSqlDatabase& db, QString& sql, QList<QVariant> params, T(*fullFunc)(QSqlQuery&));

    template<typename T>static QList<T> query(QSqlDatabase& db, QString& sql, T(*fullFunc)(QSqlQuery&));

    // 删除模板
    static void deleteF(QSqlDatabase& db, QString& sql,QList<QVariant> params);


    // 添加模板
    template<typename T> static int insertOne(QSqlDatabase& db, QString& sql, T data, QList<QVariant> (*fullParams)(T&));

    template<typename T> static int insertSome(QSqlDatabase& db, QString& sql, QList<T> datas, QList<QVariant> (*fullParams)(T&));


    // 更新模板
    static int update(QSqlDatabase& db, QString& sql,QList<QVariant> params);


    // 通用执行
    static QSqlQuery exec(QSqlDatabase& db, QString& sql,QList<QVariant> params);

    static QSqlQuery exec(QSqlDatabase& db, QString& sql);
};


bool SqliteDbOperator::openDb(QString dbName, QSqlDatabase& db){
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(dbName);
    bool isOpend = db.open();
    return isOpend;
}

template<typename T>QList<T> SqliteDbOperator::query(QSqlDatabase& db, QString& sql, QList<QVariant> params, T(*fullFunc)(QSqlQuery&)){
    QList<T> list;
    QSqlQuery query = exec(db,sql,params);
    while (query.next()) {
        list.append(fullFunc(query));
    }
    return list;
}

template<typename T> T SqliteDbOperator::queryOne(QSqlDatabase& db, QString& sql, QList<QVariant> params, T(*fullFunc)(QSqlQuery&)){
    QSqlQuery query = exec(db,sql,params);
    return fullFunc(query);
}

template<typename T> QList<T> SqliteDbOperator::query(QSqlDatabase& db, QString& sql, T(*fullFunc)(QSqlQuery&)){
    QList<QVariant> params;
    QSqlQuery query = exec(db,sql,params);
    QList<T> list;
    while (query.next()) {
        list.append(fullFunc(query));
    }
    return list;
}

void SqliteDbOperator::deleteF(QSqlDatabase& db, QString& sql,QList<QVariant> params){
    exec(db,sql,params);
}

template<typename T> int SqliteDbOperator::insertOne(QSqlDatabase& db, QString& sql, T data, QList<QVariant> (*fullParams)(T&)){
    QList<QVariant> params = fullParams(data);
    exec(db,sql,params);
    return 0;
}

template<typename T> int SqliteDbOperator::insertSome(QSqlDatabase& db, QString& sql, QList<T> datas, QList<QVariant> (*fullParams)(T&)){
    QList<QVariant> params;
    for (int i = 0; i < datas.size(); ++i) {
        params.append(fullParams(datas[i]));
    }
    exec(db,sql,datas);
}

int SqliteDbOperator::update(QSqlDatabase &db, QString &sql, QList<QVariant> params){
    exec(db,sql,params);
    return 0;
}


QSqlQuery SqliteDbOperator::exec(QSqlDatabase &db, QString &sql, QList<QVariant> params){
    QSqlQuery query(db);
    query.prepare(sql);
    for (int i = 0; i < params.size(); ++i) {
        query.bindValue(i,params[i]);
    }
    query.exec();
//    QSqlError er = query.lastError();
//    qDebug()<< er;
    return query;
}

QSqlQuery SqliteDbOperator::exec(QSqlDatabase& db, QString& sql){
    QSqlQuery query(db);
    query.prepare(sql);
    query.exec();
    return query;
}


#endif // SQLITEDBOPERATOR_H
