#include <iostream>
#include <vector>
#include <string>
#include "Subject.h"

#include <memory>

enum Action {
    ADD = 0, MANAGE = 1,  QUIT = 2, REMOVE = 3, CHANGE_NAME = 4, NOTHING = 5,
};

int read_int() {
    std::string str_input;
    int input;

    std::getline(std::cin, str_input);
    fflush(stdin);

    try {
        input = stoi(str_input);
    } catch (...) {
        input = -1;
    }

    return input;
}

void print_stringvec(const std::vector<Subject> &v) {
    int i = 0;
    for (const auto& value : v) {
        std::cout <<"[" << i << "] " << value.getName() << std::endl;
        i++;
    }
}

std::string get_input_name() {
    char confirm;
    volatile char discard;
    std::string name;
    bool invalid = true;
    do {
        std::getline(std::cin, name);
        fflush(stdin);

        std::cout << "Va bene \"" << name << "\"? [y/Y -> si | altro input -> no]" << std::endl;

        do {
            confirm = getchar();
            fflush(stdin);
            discard = getchar();
        } while (isspace(confirm));
        invalid = confirm != 'y' && confirm != 'Y';
        if (invalid) {
            std::cout << "Inserisci di nuovo: " << std::endl;
        }
    } while (invalid);

    return name;
}

void add_subject(std::vector<Subject>* v) {
    std::cout << "Inserisci il nome dell'argomento da studiare:" << std::endl;
    std::string name = get_input_name();
    std::cout << "\nInserisco \"" << name << "\" nella lista degli argomenti...\n" << std::endl;
    v->emplace_back(Subject(name));
    std::cout << "Ecco la nuova lista degli argomenti:" << std::endl;
    print_stringvec(*v);

};

void remove_subject(std::vector<Subject>* v, int position) {
    const auto iter = v->begin() + position;
    Subject removed = (*v)[position];
    v->erase(iter);

    std::cout << "\nHo rimosso \"" << removed.getName() << "\"\n" << std::endl;
}

void change_subject_name(std::vector<Subject>* v, int position) {
    std::cout << "Inserisci il nuovo nome dell'argomento:" << std::endl;
    std::string new_name = get_input_name();

    auto iter = v->begin() + position;
    (*v)[position].setName(new_name);

   /* std::string  removed = (*v)[position];
    v->emplace(iter, new_name);
    v->erase(++iter);*/


    //std::cout << "\nHo rimosso \"" << removed << "\"\n" << std::endl;

}

void manage_subject(std::vector<Subject>* v) {
    int input;
    int idx;
    bool valid = false;
    std::cout << "Quale argomento vuoi gestire? (inserisci il numero corrispondente" << std::endl;
    print_stringvec(*v);
    do {
        idx = read_int();

        if (idx >= 0 && idx < v->size()) {
            valid = true;
        } else {
            std::cout << "Input non valido, riprova:" << std::endl;
        }
    } while (!valid);

    std::cout << "Cosa vuoi fare con \"" << (*v)[idx].getName() <<"\"?" << std::endl;
    std::cout << "[0] Rimuovi" << std::endl;
    std::cout << "[1] Cambia nome" << std::endl;
    std::cout << "[2] Annulla" << std::endl;

    valid = false;
    do {
        input = read_int();

        if (input >= 0 && input <= 2) {
            valid = true;
        } else {
            std::cout << "Input non valido, riprova:" << std::endl;
        }

    } while (!valid);

    switch (input) {
        case 0:
            remove_subject(v, idx);
            std::cout << "Nuova lista degli argomenti:" << std::endl;
            print_stringvec(*v);

            break;
        case 1:
            change_subject_name(v, idx);
            std::cout << "Nuova lista degli argomenti:" << std::endl;
            print_stringvec(*v);
        default:
            break;

    }
}

Action get_action() {
    int input;
    Action result;
    bool valid = false;
        std::cout << "Cosa vuoi fare?" << std::endl;
        std::cout << "[0] Aggiungi argomento" << std::endl;
        std::cout << "[1] Gestisci argomento" << std::endl;
        std::cout << "[2] Esci" << std::endl;

    do {
        input = read_int();
        if (input >= ADD && input <= QUIT) {
            valid = true;
        } else {
            std::cout << "Input non valido, riprova:" << std::endl;
        }

    } while (!valid);

    switch (input) {
        case 0:
            result = ADD;
            break;
        case 1:
            result = MANAGE;
            break;
        case 2:
            result = QUIT;
            break;
        default:
            std::cout << "ERRORE SCONOSCIUTO";
            result = QUIT;
            break;
    }

    return result;
}

int main() {
    std::vector<Subject> names = std::vector<Subject>();
    std::string in = "Ciao Anna";
    names.emplace_back(Subject(in));
    in = "Ciao Pietro";
    names.emplace_back(Subject(in));

    print_stringvec(names);
    bool quit = false;

    while(!quit) {
        Action action = get_action();
        switch (action) {
            case ADD:
                add_subject(&names);
                break;
            case MANAGE:
                if (!names.empty()) {
                    manage_subject(&names);
                } else {
                    std::cout << "Non ci sono argomenti da gestire" << std::endl;
                }
                break;
            case QUIT:
                quit = true;
                break;
            default:
                break;
        }
    }



    /*int position = 1;
    const auto iter = names.begin() + position;
    std::string removed = names[position];
    names.erase(iter);



    for (const auto & name : names) {
        std::cout << name << std::endl;
    }*/


    //std::cout << "Hello, World!" << std::endl;
    return 0;
}