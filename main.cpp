#include <iostream>
#include <cstring>
#include <ctime>
#include "utils.h"
#include "Deque.h"

using namespace std;

enum types {INT = 1, CHAR, FLOAT, DOUBLE, CHAR_ARR};

const char *menu[] = { "Choose a task -- 1: Template Function, 2: Deque\n",
                       "1: Display array; 2: Display array avg; c: Change type; b: Back to choosing task; h: help\n",
                       "1: Display deques; 2: assignment `=`; 3: cin/cout ops `>>`/`<<`; 4: pop last `-`;\n5: elementwise sum `+`; 6: compare lengths of arrays of selected type h: help\nc: Change type; b: Back to choosing task; h: help\n",
                       "Choose type -- 1: int; 2: char; 3: float; 4: double; 5: char*;\n"};

void in() {
    printf(">> ");
}

void help(int type) {
    printf(menu[type]);
}

int getInt(const char *msg = "Type the value:\n") {
    int result;
    printf(msg);
    in();
    scanf("%d", &result);
    return result;
}

char getChar(FILE *fp = stdin) {
    char result;
    if (fp == stdin) {
        printf("Type the char:\n");
        in();
    }
    fscanf(fp, "%c\n", &result);
    return result;
}

char selectTask() {
    help(0);
    in();
    return getchar();
}

template <typename T>
float avg(T* arr, int size) {
    float res = 0;
    for (int i = 0; i < size; i++)
        res += arr[i];
    return res/size;
}

template <>
float avg(char** arr, int size) {
    float res = 0;
    for (int i = 0; i < size; i++)
        res += strlen(arr[i]);
    return res/size;
}

template <typename T>
T* array(int size) {
    T *a = (T*)calloc(size, sizeof(T));
    for (int i = 0; i < size; i++)  
        a[i] = rand() % 100;
    return a;
}

template <>
char** array(int size) {
    char **a = (char**)calloc(size, sizeof(char*));
    for (int i = 0; i < size; i++)  
        a[i] = random_str(rand() % 100 + 1);
    return a;
}

void display(int* a, int size) {
    for (int i = 0; i < size; i++) 
        printf("%d ", a[i]);
    printf("\nsize: %d\n", size);
}

void display(float* a, int size) {
    for (int i = 0; i < size; i++) 
        printf("%f ", a[i]);
    printf("\nsize: %d\n", size);
}

void display(double* a, int size) {
    for (int i = 0; i < size; i++) 
        printf("%lf ", a[i]);
    printf("\nsize: %d\n", size);
}

void display(char* a, int size) {
    for (int i = 0; i < size; i++) 
        printf("%d ", a[i]);
    printf("\nsize: %d\n", size);
}

void display(char** a, int size) {
    for (int i = 0; i < size; i++) {
        printf(a[i]);
        printf("  len: %d\n", strlen(a[i]));
    }
    printf("\nsize: %d\n", size);
}

template <typename T>
char task1(T* a, int size) {
    help(1);
    while (1) {
        char c = getchar();
        if (c == '\n') 
            in();
        if (c == 'h')
            help(1);
        else if (c == '1')
            display(a, size);
        else if (c == '2')
            printf("avg: %.2f\n", avg(a, size));
        else if (c == 'c') {
            getchar();
            return '1';
        } else if (c == 'b') {
            getchar();
            return selectTask();
        }
    }
}

template <typename T>
char task2(Deque<T> d1, Deque<T> d2, int size) {
    help(2);
    while (1) {
        char c = getchar();
        Deque<T> d3(size);
        if (c == '\n') 
            in();
        if (c == 'h')
            help(2);
        else if (c == '1') {
            cout << "d1:\n" << d1 << "d2:\n" << d2;
        } else if (c == '2') {
            d3 = d1;
            cout << "d1:\n" << d1 << "d3:\n" << d3;
        } else if (c == '3') {
            cin >> d1;
            cout << d1;
        } else if (c == '4') {
            try {
                -d1;
            } catch(out_of_range& e) {
                cout << e.what();
            }
            try {
                cout << "Removing last element of d1, remaining deque:\n" << d1;
            } catch(out_of_range& e) {
                cout << e.what();
            }
        } else if (c == '5') {
            try {
               Deque<T> d4 = d2 + d1;
               try {
                    cout << "d1:\n" << d1 << "d2:\n" << d2 << "d4:\n" << d4;
                } catch(out_of_range& e) {
                    cout << e.what();
                }
            } catch(length_error& e) {
                cout << e.what();
            }
            
        } else if (c == '6') {
            cout << (d1 < d2 ? "d1 length is shorter than length of d2\n" : "d1 length is larger than length of d2 or equal to it\n");
        } else if (c == 'c') {
            getchar();
            return '2';
        } else if (c == 'b') {
            getchar();
            return selectTask();
        }
    }
}

int main() {
    srand(time(0));
    char task = selectTask();
    while (task) {
        if (task == '1') {
            help(3);
            int t = getInt();
            int size = rand() % 10 + 1;
            if (t == INT) {
                task = task1(array<int>(size), size);
            } else if (t == CHAR) {
                task = task1(array<char>(size), size);
            } else if (t == FLOAT) {
                task = task1(array<float>(size), size);
            } else if (t == DOUBLE) {
                task = task1(array<double>(size), size);
            } else if (t == CHAR_ARR) {
                task = task1(array<char*>(size), size);
            }
        }
        else if (task == '2') {
            help(3);
            int t = getInt();
            int size = rand() % 10 + 1;
            if (t == INT) {
                task = task2(Deque<int>(size), Deque<int>(size), size);
            } else if (t == CHAR) {
                task = task2(Deque<char>(size), Deque<char>(size), size);
            } else if (t == FLOAT) {
                task = task2(Deque<float>(size), Deque<float>(size), size);
            } else if (t == DOUBLE) {
                task = task2(Deque<double>(size), Deque<double>(size), size);
            } else if (t == CHAR_ARR) {
                task = task2(Deque<char*>(size), Deque<char*>(size), size);
            }
        }
        else {
            printf("No such option. Try again.\n");
            getchar();
            task = selectTask();
        }
    }
    return 0;
}