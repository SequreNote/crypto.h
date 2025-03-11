#include "Crypto.h"
#include <iostream>

using namespace std;

QString Crypto::encrypt(const QString &text, const QString &key) {
    QString encryptedText = text;
    for (size_t i = 0; i < text.size(); ++i) {
        encryptedText[i] ^= key[i % key.size()]; // Простое шифрование XOR
    }
    return encryptedText;
}

QString Crypto::decrypt(const QString &text, const QString &key) {
    return encrypt(text, key); // XOR работает в обе стороны
}
