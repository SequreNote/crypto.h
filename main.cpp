#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "Database.h"
#include "Crypto.h"
#include <iostream>


QString userPassword; // Глобальный пароль для шифрования

// Запрос пароля у пользователя
bool requestPassword() {
    bool ok;
    QString password = QInputDialog::getText(nullptr, "Авторизация", 
                                             "Введите пароль:", 
                                             QLineEdit::Password, "", &ok);

    if (!ok || password.isEmpty()) {
        QMessageBox::critical(nullptr, "Ошибка", "Пароль не введён!");
        return false;
    }

    userPassword = password;
    return true;
}

// Консольный режим
void runConsoleMode() {
    if (!requestPassword()) return;
    QString key = userPassword.toStdString();

    while (true) {
        qStdOut << "\nМеню:\n";
        cout << "1. Добавить заметку\n";
        cout << "2. Показать заметки\n";
        cout << "3. Выйти\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            QString title, content;
            cout << "Введите заголовок: ";
            readLine(cin, title);
            cout << "Введите содержание: ";
            readLine(cin, content);

            QString encryptedContent = Crypto::encrypt(content, key);
            Database::saveNote(Note(title, encryptedContent));
            cout << "Заметка сохранена!\n";
        } 
        else if (choice == 2) {
            QVector<Note> notes = Database::loadNotes();
            cout << "\nСохранённые заметки:\n";

            for (const auto& note : notes) {
                cout << "Заголовок: " << note.getTitle() << "\n";
                cout << "Содержание: " << Crypto::decrypt(note.getContent(), key) << "\n";
                cout << "----------------------------\n";
            }
        } 
        else if (choice == 3) {
            break;
        } 
        else {
            cout << "Некорректный ввод. Попробуйте снова.\n";
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    if (argc > 1 && string(argv[1]) == "--console") {
        runConsoleMode();
        return 0;
    }

    if (!requestPassword()) return 0; // Запрос пароля перед GUI

    MainWindow w(userPassword);
    w.show();
    return app.exec();
}
