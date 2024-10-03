#include "Chat.h"
#include "iostream"
#include "string.h"

bool eq(uint* p, uint* op, const int lenght) {
    
    for (int i = 0; i < lenght; ++i) {
        if (p[i] != op[i]) return false;
    }
    return true;
}

void Chat::reg(Login _login, char _pass[], int pass_length) {
    add(_login, sha1(_pass, pass_length));
}

bool Chat::login(Login _login, char _pass[], int pass_length) {
    int index = -1, i = 0;
    uint* hash = sha1(_pass, pass_length);
    for (; i < SIZE; i++) {
        index = hash_func(_login, i);
        if (data[index].state == Enstate::engaged ||  eq(data[index].pass, hash, SHA1HASHLENGTHUINTS)) {
            return true;
        }
    }

    return false;
}

int Chat::hash_func(Login fr_name, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < strlen(fr_name); i++) {
        sum += fr_name[i];
    }
    // квадратичные пробы
    return (sum % SIZE + offset * offset) % SIZE;
}

void Chat::resize() {

    logDat* save = data;
    int save_ms = mem_size;

    mem_size *= 2;
    data = new logDat[mem_size];
    count = 0;

    for (int i = 0; i < save_ms; i++) {
        logDat& old_pair = save[i];
        if (old_pair.state == Enstate::engaged) {
            add(old_pair.login, old_pair.pass);
        }
    }

    delete[] save;
}

void Chat::add(Login log, uint* password) {

    int index = -1, i = 0;
    for (; i < SIZE; i++) {
        index = hash_func(log, i);
        if (data[index].state == Enstate::Free) {
            break;
        }
    }

    if (i >= SIZE) {
        resize();
        add(log, password);
    }
    else {
        data[index] = logDat(log, password);
        count++;
    }
}
