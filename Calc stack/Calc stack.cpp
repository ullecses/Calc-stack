#include <iostream>
#include <stack>

using namespace std;

struct leksema {
    char type; //0 - для чисел,"+" - сложение
    double value;
};
void compute(stack <leksema> & Stack_n, stack <leksema> & Stack_o, leksema item) {
    double a, b,c;
    a = Stack_n.top().value;
    Stack_n.pop();
    switch (Stack_o.top().type) {
        case '+':
            b = Stack_n.top().value;
            Stack_n.pop();
            c = a + b;
            item.value = c;
            Stack_n.push(item);
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    char ch;
    double value;

    stack <leksema> Stack_n;
    stack <leksema> Stack_o;
    leksema item;
    while (1) {
        ch = cin.peek();
        if (ch == '\n') break;
        if (ch >= '0' && ch <= '9') {
            cin >> value;
            item.type = '0';
            item.value = value;
            Stack_n.push(item);
            continue;
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            item.type = ch;
            item.value = 0;
            Stack_o.push(item);
            cin.ignore();
            continue;
        }
    }
    compute(Stack_n, Stack_o, item);
    cout << "Ответ: " << Stack_n.top().value << endl;
    return 0;
}
