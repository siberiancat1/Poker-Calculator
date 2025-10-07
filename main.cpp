#include <iostream>
#include <vector>
#include <locale>
#include "calculator.h"
#include <chrono>

using namespace std;
//это мэйн
int main() {
    cout<<"hello world"<<endl;
    Deck d;d.SetDefault();
    Hand a;
    vector<Card> b;
    /*
    int menu = 9;
    while (menu != 0) {
        cout<<"1 add card in hand"<<endl<<"2 calculate"<<endl;
        cin>>menu;
        cout<<menu;
        if (menu == 1) {
            int val = 111;
            int suit;
            while (val != 0) {
                cout<<"value of card"<<endl;
                cin>>val;
                if (val == 0) {
                    break;
                }
                cout<<"suit of card"<<endl;
                cin>>suit;
                Card n(val,suit,false);
                b.push_back(n);
            }
        }
        else if (menu == 2) {
            a = b;
            cout<<"your input:";
            a.print();
            cout<<endl<<"best combo"<<endl;
            a.print_solution();
        }
        }
        */
    int val = 999;
    while (val != 0) {
        Card c1;c1.input();
        Card c2;c2.input();
        Deck p1hand;p1hand = {c1,c2};
        Calculator C(p1hand);
        auto start = std::chrono::high_resolution_clock::now();
        C.Calculate();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;

        cout<<"Продолжить?"<<endl;
        cin>>val;
    }
    
}