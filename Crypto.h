#ifndef CRYPTO_H
#define CRYPTO_H

#include <QString>



class Crypto {
public:
    static QString encrypt(const QString &text, const QString &key);
    static QString decrypt(const QString &text, const QString &key);
};

#endif // CRYPTO_H
