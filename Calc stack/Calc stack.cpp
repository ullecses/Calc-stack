#include <iostream>
#include <stack>

using namespace std;

struct leksema {
    char type; //0 - для чисел,"+" - сложение
    double value;
};

bool compute(stack <leksema> & Stack_n, stack <leksema> & Stack_o, leksema item) {
    double a, b,c;
    a = Stack_n.top().value;
    Stack_n.pop();
    switch (Stack_o.top().type) {
        case '+':
            b = Stack_n.top().value;
            Stack_n.pop();
            c = a + b;
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;
        case '-':
            b = Stack_n.top().value;
            Stack_n.pop();
            c = b - a;
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;
        case '*':
            b = Stack_n.top().value;
            Stack_n.pop();
            c = a * b;
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;
        case '/':
            b = Stack_n.top().value;
                if (a == 0) 
                    cerr << "На 0 делить нельзя! ";
            Stack_n.pop();
            c = b / a;
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;
        default:
            cerr << "Ошибка! ";
            return false;
            break;
    }
    return true;
};

int Rang(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    return 0;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    cout << " Введите выражение: ";

    char ch;
    double value;
    bool flag = 1;

    stack <leksema> Stack_n;
    stack <leksema> Stack_o;
    leksema item;
    while (1) {
        ch = cin.peek();
        if (ch == '\n') break;
        if (ch == ' ') {
            cin.ignore();
            continue;
        }
        if (ch >= '0' && ch <= '9'|| ch == '-' && flag == 1) {
            cin >> value;
            item.type = '0';
            item.value = value;
            Stack_n.push(item);
            flag = 0;
            continue;
        }
        if (ch == '+' || ch == '-' && flag ==0 || ch == '*' || ch == '/') {
            if (Stack_o.size() == 0) {
                item.type = ch;
                item.value = 0;
                Stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (Stack_o.size() != 0 && Rang(ch) > Rang(Stack_o.top().type)) {
                item.type = ch;
                item.value = 0;
                Stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (Stack_o.size() != 0 && Rang(ch) <= Rang(Stack_o.top().type)) {
                if (compute(Stack_n, Stack_o, item) == false) {
                    system("pause");
                    return 0;
                }
                continue;
            }
        }
        if (ch == '(') {
            item.type = ch;
            item.value = 0;
            Stack_o.push(item);
            cin.ignore();
            continue;
        }
        if (ch == ')') {
            while (Stack_o.top().type != '(') {
                if (compute(Stack_n, Stack_o, item) == false) {
                    system("pause");
                    return 0;
                }
                else continue;
            }
            Stack_o.pop();
            cin.ignore();
            continue;
        }
        else {
            cout << "\nНеверное выражение!\n";
            system("payse");
            return 0;
        }
    }
   while (Stack_o.size() != 0) {
        compute(Stack_n, Stack_o, item);
    }
    cout << "Ответ: " << Stack_n.top().value << endl;
    return 0;
}
