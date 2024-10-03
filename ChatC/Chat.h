#pragma once

#include "sha1.h"
#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10
typedef char Login[LOGINLENGTH];

enum Enstate {
    Free,
    engaged,
    deleted
};

struct logDat {
    logDat() : pass(0), state(Enstate::Free), login(""){}
    logDat(Login l, uint* p) : pass(p), state(Enstate::engaged) {
        strcpy_s(login, l);
    }
    ~logDat() {
        delete[] pass;
    }
    Enstate state;
    Login login;
    uint* pass;
    logDat& operator = (const logDat& other) {
        strcpy_s(this->login, other.login);
         state = other.state;
         pass = other.pass;
         return *this;
    }
};
class Chat {
public:
    Chat() : data(new logDat[SIZE]), count(0) {}
    void resize();
    void reg(Login _login, char _pass[], int pass_length); // TODO: накинуть хэш таблу
    bool login(Login _login, char _pass[], int pass_length); // TODO: накинуть проверку из хэш таблы
    int hash_func(Login login, int offset);
    void add(Login login, uint* password);
private:
    logDat* data;
    int mem_size = SIZE;
    int count;
};

