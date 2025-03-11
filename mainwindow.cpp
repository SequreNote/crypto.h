#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString &password, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), userPassword(password) {
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveNote);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadNotes);
    connect(ui->notesList, &QListWidget::itemClicked, this, &MainWindow::selectNote);

    loadNotes();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::saveNote() {
    QString title = ui->titleEdit->text();
    QString content = ui->textEdit->toPlainText();

    if (title.isEmpty() || content.isEmpty()) {
        ui->statusBar->showMessage("Ошибка: пустая заметка!", 3000);
        return;
    }

    string encryptedContent = Crypto::encrypt(content.toStdString(), userPassword.toStdString());
    Database::saveNote(Note(title.toStdString(), encryptedContent));

    ui->statusBar->showMessage("Заметка сохранена!", 2000);
    loadNotes();
}

void MainWindow::loadNotes() {
    notes = Database::loadNotes();
    ui->notesList->clear();

    for (const auto &note : notes) {
        ui->notesList->addItem(QString::fromStdString(note.getTitle()));
    }
}

void MainWindow::selectNote(QListWidgetItem *item) {
    for (const auto &note : notes) {
        if (QString::fromStdString(note.getTitle()) == item->text()) {
            QString decryptedContent = QString::fromStdString(
                Crypto::decrypt(note.getContent(), userPassword.toStdString())
            );
            ui->titleEdit->setText(item->text());
            ui->textEdit->setText(decryptedContent);
            break;
        }
    }
}
