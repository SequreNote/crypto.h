#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QString>
#include "Note.h"
#include "Database.h"
#include "Crypto.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(const QString &password, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveNote();
    void loadNotes();
    void selectNote(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    std::vector<Note> notes;
    QString userPassword;
};

#endif // MAINWINDOW_H
