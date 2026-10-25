#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialiserBaseDeDonnees();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialiserBaseDeDonnees()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("gestion_salles.db");

    if (!db.open()) {
        qDebug() << "Erreur SQLite :" << db.lastError().text();
        return;
    }

    QSqlQuery query;

    QString sql = R"(
        CREATE TABLE IF NOT EXISTS salle (
            id_salle INTEGER PRIMARY KEY AUTOINCREMENT,
            nom_salle TEXT NOT NULL,
            capacite INTEGER NOT NULL,
            equipement TEXT
        )
    )";

    if (!query.exec(sql)) {
        qDebug() << "Erreur creation table :"
                 << query.lastError().text();
        return;
    }

    qDebug() << "Base de donnees et table salle creees avec succes.";
}
