#include <iostream>
#include <ctime>
#include <cstring>
#include "utils.h"

using namespace std;

template <typename T>
class Deque {
    public:
        Deque() { head = tail = NULL; }
        Deque(int n) {
            head = tail = NULL;
            for (int i = 0; i < n; i++)
                this->pushFront(rand() % 10);
        };
        ~Deque() {
            if (!isEmpty()) {
                Node *tmp = head, *next_node;
                do {
                    next_node = tmp->next;
                    delete tmp;
                } while (next_node != NULL, tmp = next_node);
            }
        }
        bool isEmpty() { return head == NULL; }
        struct Node {
            T data;
            struct Node* next;
            struct Node* prev;
        };
        void pushFront(T val) {
            Node *tmp = new Node;
            tmp->data = val;
            tmp->next = tmp->prev = NULL;

            if (isEmpty()) {
                head = tmp;
                tail = tmp;
            } else {
                tmp->next = head;
                head->prev = tmp;
                head = head->prev;
            }
        }
        void pushRear(T val) {
            Node *tmp = new Node;
            tmp->data = val;
            tmp->next = tmp->prev = NULL;

            if (isEmpty()) {
                head = tmp;
                tail = tmp;
            } else {
                tmp->prev = tail;
                tail->next = tmp;
                tail = tail->next;
            }
        }
        T popFront() {
            if (isEmpty()) 
                throw out_of_range("empty");

            Node *tmp = head;
            T data = tmp->data;
            if (head->next != NULL) {
                head = tmp->next;
                head->prev = NULL;
            } else {
                head = tail = NULL;
            }
            delete tmp;
            return data;

        };
        T popRear() {
            if (isEmpty()) 
                throw out_of_range("empty");

            Node *tmp = tail;
            T data = tmp->data;
            if (tail->prev != NULL) {
                tail = tmp->prev;
                tail->next = NULL;
            } else {
                head = tail = NULL;
            }
            delete tmp;
            return data;
        }
        Deque& operator=(Deque &d) {
            if (this == &d)
                return *this;

            if (!isEmpty()) {
                Node *tmp = head, *next_node;
                do {
                    next_node = tmp->next;
                    delete tmp;
                } while (next_node != NULL, tmp = next_node);
                head = tail = NULL;
            }

            Node *tmp = d.head;
            do
                pushRear(tmp->data);
            while (tmp != NULL, tmp = tmp->next);

            return *this;
        }
        Deque& operator-() {
            popRear();
            return *this;
        };
        friend Deque operator+(Deque& d1, Deque& d2) {
            if (d1 < d2 || d2 < d1)
                throw length_error("Sizes of deques aren't equal\n");
            Deque res, d2_copy;
            res = d1; d2_copy = d2;
            while (!d2_copy.isEmpty())
                res.pushRear(res.popFront() + d2_copy.popFront());
            return res;
        }
        friend bool operator<(Deque& d1, Deque& d2) {
            int c1 = 0, c2 = 0;
            Deque::Node *tmp = d1.head;
            do
                c1++;
            while (tmp != NULL, tmp = tmp->next);
            tmp = d2.head;
            do
                c2++;
            while (tmp != NULL, tmp = tmp->next);
            return c1 < c2;
        }
        friend ostream& operator<<(ostream& os, const Deque& d) {
            Deque::Node *tmp = d.head;
            if (tmp == NULL)
                throw out_of_range("Deque is empty\n");
            do
                os << tmp->data << " ";
            while (tmp != NULL, tmp = tmp->next);
            os << endl;
            return os;
        }
        friend istream& operator>>(istream& is, Deque& d) {
            int size;
            T val;
            cout << "Type how many elements to push rear:\n>> ";
            is >> size;
            for (int i = 0; i < size; i++) {
                cout << "Type the value:\n>> ";
                is >> val;
                d.pushRear(val);
            }
            return is;
        };
    private:
        Node *head, *tail;
};

template <>
class Deque<char*> {
    public:
        Deque() { head = tail = NULL; }
        Deque(int n) {
            head = tail = NULL;
            for (int i = 0; i < n; i++)
                this->pushFront(random_str(10));
        };
        ~Deque() {
            if (!isEmpty()) {
                Node *tmp = head, *next_node;
                do {
                    next_node = tmp->next;
                    delete tmp->data;
                    delete tmp;
                } while (next_node != NULL, tmp = next_node);
            }
        }
        bool isEmpty() { return head == NULL; }
        struct Node {
            char* data;
            struct Node* next;
            struct Node* prev;
        };
        void pushFront(char* val) {
            Node *tmp = new Node;
            tmp->data = val;
            tmp->next = tmp->prev = NULL;

            if (isEmpty()) {
                head = tmp;
                tail = tmp;
            } else {
                tmp->next = head;
                head->prev = tmp;
                head = head->prev;
            }
        }
        void pushRear(char* val) {
            Node *tmp = new Node;
            tmp->data = val;
            tmp->next = tmp->prev = NULL;

            if (isEmpty()) {
                head = tmp;
                tail = tmp;
            } else {
                tmp->prev = tail;
                tail->next = tmp;
                tail = tail->next;
            }
        }
        char* popFront() {
            if (isEmpty()) 
                throw out_of_range("Cannot pop empty deque\n");

            Node *tmp = head;
            char* data = tmp->data;
            if (head->next != NULL) {
                head = tmp->next;
                head->prev = NULL;
            } else {
                head = tail = NULL;
            }
            delete tmp;
            return data;

        };
        char* popRear() {
            if (isEmpty()) 
                throw out_of_range("Cannot pop empty deque\n");

            Node *tmp = tail;
            char* data = tmp->data;
            if (tail->prev != NULL) {
                tail = tmp->prev;
                tail->next = NULL;
            } else {
                head = tail = NULL;
            }
            delete tmp;
            return data;
        }
        Deque& operator=(Deque &d) {
            if (this == &d)
                return *this;

            if (!isEmpty()) {
                Node *tmp = head, *next_node;
                do {
                    next_node = tmp->next;
                    delete tmp;
                } while (next_node != NULL, tmp = next_node);
                head = tail = NULL;
            }

            Node *tmp = d.head;
            do
                pushRear(tmp->data);
            while (tmp != NULL, tmp = tmp->next);

            return *this;
        }
        Deque& operator-() {
            popRear();
            return *this;
        };
        friend Deque operator+(Deque& d1, Deque& d2) {
            Deque res, d1_copy, d2_copy;
            if (d1 < d2 || d2 < d1)
                throw length_error("Sizes of deques aren't equal\n");
            d1_copy = d1; d2_copy = d2;
            while (!d1_copy.isEmpty() && !d2_copy.isEmpty()) {
                char *s1 = d1_copy.popFront(), *s2 = d2_copy.popFront();
                char *new_s = (char*)calloc(strlen(s1) + strlen(s2), sizeof(char));
                strcpy(new_s, s1);
                strcat(new_s, s2);
                res.pushRear(new_s);
            }
            return res;
        }
        friend bool operator<(Deque& d1, Deque& d2) {
            int c1 = 0, c2 = 0;
            Deque::Node *tmp = d1.head;
            if (tmp != NULL)
                do
                    c1++;
                while (tmp != NULL, tmp = tmp->next);
            tmp = d2.head;
            if (tmp != NULL)
                do
                    c2++;
                while (tmp != NULL, tmp = tmp->next);
            return c1 < c2;
        }
        friend ostream& operator<<(ostream& os, const Deque& d) {
            Deque::Node *tmp = d.head;
            if (tmp == NULL)
                throw out_of_range("Deque is empty\n");
            do
                os << tmp->data << " ";
            while (tmp != NULL, tmp = tmp->next);
            os << endl;
            return os;
        }
        friend istream& operator>>(istream& is, Deque& d) {
            int size, val;
            cout << "Type the amount of elements to push to d1\n>> ";
            is >> size;
            for (int i = 0; i < size; i++) {
                cout << "Type string length of the element\n>> ";
                is >> val;
                d.pushRear(random_str(val));
            }
            return is;
        }
    private:
        Node *head, *tail;
};

// int main() {
//     srand(time(0));
//     Deque<char*> d1(5);
//     -d1;
//     cout << d1;
//     Deque<char*> d2(5);
//     cout << d2;
//     cout << (d1 < d2);
//     return 0;
// }