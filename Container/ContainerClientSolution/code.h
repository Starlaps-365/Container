#ifndef CODE_H
#define CODE_H

class QString;

class Code
{
public:
    Code();
    static QString getCode(QString type);
private:
    static int count;
};

#endif // CODE_H
