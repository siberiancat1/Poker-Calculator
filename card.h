#include <vector>  
#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <locale>
using namespace std;
//это файл card.h

class Card {
    private:
        int val;
        int suit;
        bool joker;
    public:
        Card(): val(0),suit(0),joker(false) {};
        Card(int v, int s,bool j = false): val(v),suit(s),joker(j) {};
        void input() {
            cout<<endl<<"Введите значение карты"<<endl;
            cin>>val;
            cout<<endl<<"Введите масть"<<endl;
            cin>>suit;
        }
        const int get_suit() {
            return suit;
        }
        int get_val() {
            return val;
        };
        void print() {
            char chr_suit = 'B';
            switch (suit)
            {
            case 0:
                chr_suit = 'S';
                break;
            case 1:
                chr_suit = 'H';
                break;
            case 2:
                chr_suit = 'C';
                break;
            case 3:
                chr_suit = 'B';
                break;
            default:
                chr_suit = '?';
                break;
            }
            char chr_val = '?';
            switch (val)
            {
            case 10:
                chr_val = 'T';
                break;
            case 11:
                chr_val = 'J';
                break;
            case 12:
                chr_val = 'Q';
                break;
            case 13:
                chr_val = 'K';
                break;
            case 14:
                chr_val = 'A';
                break;
            default:
                chr_val = (char)(val + 48);
                break;
            }
            cout<<chr_val<<chr_suit<<" ";
        };
        Card operator+ (const int& other) {
            Card res = {val+other,suit,false};
            if (res.get_val() == 15) {
                res = {2,suit,false};
            }
            return res;
        }
        bool operator==(const Card& other) {
            return (val == other.val);
        };
        bool operator>(const Card& other) {
            return (val > other.val);
        };
        bool operator<(const Card& other) {
            return (val < other.val);
        };
        bool absolute_eq(Card card) {
            return (card.val == val && card.suit == suit && joker == card.joker);
        }
        
};
class Deck {
    protected:    
        vector<Card> deck;
    public:
        Deck(): deck({}){};
        Deck(vector<Card> Cards): deck(Cards) {};
        vector<Card> getDeck() {
            return deck;
        }
        void take(Deck& other,unsigned int N = 1) {
            for (unsigned int i = 0; i < N; i++) {
                deck.push_back(other.deck[0]);
                other.deck.erase(other.deck.begin());
            }
        }
        void sorted() {
        // Create a temporary vector and sort it using public methods
        vector<Card> temp = deck;
        
        for (size_t i = 0; i < temp.size(); i++) {
            for (size_t j = 0; j < temp.size() - i - 1; j++) {
                bool should_swap = false;
                
                // Get values using public methods
                int val_j = temp[j].get_val();
                int val_j1 = temp[j + 1].get_val();
                
                // Handle jokers (value 0)
                if (val_j == 0 && val_j1 == 0) {
                    continue; // Both jokers, no swap needed
                }
                if (val_j == 0) {
                    should_swap = true; // Joker should go after regular cards
                }
                else if (val_j1 == 0) {
                    should_swap = false; // Regular card should stay before joker
                }
                else {
                    // Compare by value
                    if (val_j < val_j1) {
                        should_swap = true;
                    }
                    else if (val_j == val_j1) {
                        // If values equal, compare by suit
                        int suit_j = temp[j].get_suit();
                        int suit_j1 = temp[j + 1].get_suit();
                        if (suit_j > suit_j1) {
                            should_swap = true;
                        }
                    }
                }
                
                if (should_swap) {
                    std::swap(temp[j], temp[j + 1]);
                }
            }
        }
    
    deck = temp;
}
        void SetDefault(){
            for (size_t i = 2; i < 15; i++)
            {
                for (size_t j = 0; j < 4; j++)
                {
                    deck.push_back(Card(i,j));
                };  
            };
            deck.push_back(Card(0,0,true));
            deck.push_back(Card(0,0,true));
        };
        void print() {
            for (int i = 0; i < deck.size();i++) {
                deck[i].print();
            };
        }
        void deck_shuffle() {
            auto rng = std::default_random_engine {};
            static std::random_device rd;
            static std::mt19937 g(rd());
            std::shuffle(std::begin(deck), std::end(deck), g);
            //print();
        }
        Deck& operator=(const Deck& other) = default;   
        Deck operator=(vector<Card> vec) {
            deck = vec;
            return *this; 
        }
        Card operator[](int index) {
            if (index<0 || index>=deck.size()) {
                throw out_of_range("ага да");
            }
            return deck[index];
        }
        Deck operator-(Deck& other) {
            Deck res;
            bool temp;
            for (int i = 0; i < deck.size(); i++) {
                temp = true;
                for (int j = 0;j < other.size(); j++) {
                    if (deck[i].absolute_eq(other.deck[j])) {
                        temp = false;    
                        break;
                    }
                }
                if (temp) {
                    res.append(deck[i]);
                }
            }
            return res;
        }
        Deck operator+(Deck& other) {
            Deck res;
            res = deck;
            for (int i = 0; i < other.size(); i++) {
                res.append(other.deck[i]);
            }
            return res;
        }
        Card max_card() {
            Card m = deck[0];
            for (int i = 1; i < deck.size(); i++) {
                if (deck[i] > m) {
                    m = deck[i];
                }
            }
            return m;
        }
        int find_card(int val) {
            for (int i = 0; i < deck.size();i++) {
                if (deck[i].get_val() == val) {
                    return i;
                }
            }
            return -1;
        }
        void append(Card card) {
            deck.push_back(card);
        }
        int size() {
            return deck.size();
        }
        void clear() {
            deck.clear();
        }
};  
class Hand: public Deck {
    private:
        Deck best_hand;
        Deck best_hand_combo;
        int best_combo = -1;
        vector<Deck> hands;
    protected:
        Deck find_same_value(Card card,Deck hand) {
            Deck res;
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i] == card) {
                    res.append(hand[i]);
                }
            }
            return res;
        }
        Deck find_pairs(Deck hand) {
            Deck t_best_hand;
                for (int i = 0; i < 5; i++) {
                    Deck a = find_same_value(hand[i],hand);
                    if (a.size() > t_best_hand.size()) {
                        t_best_hand = a;
                    }
                    else if (a.size() == t_best_hand.size()) {
                        if (a[0] > t_best_hand[0]) {
                            t_best_hand = a;
                        }
                    }
                    
                }
            return t_best_hand;
        }
        Deck find_two_pairs(Deck hand) {
            Deck temp,temp2,temp3,res;
            for (int i = 0; i < hand.size(); i++) {
                temp = find_same_value(hand[i],hand);
                temp2 = hand - temp;
                if (temp.size() == 2) {
                    for (int j = 0; j < temp2.size(); j++) {
                        temp3 = find_same_value(temp2[j],temp2);
                        if (temp3.size() > 1 && temp.size()+temp3.size() > res.size()) {
                            res = temp + temp3;
                        }
                    }
                }
            }
           return res;
        }
        Deck find_flash(Deck hand) {
            int s = hand[0].get_suit();
            for (int i = 1; i < hand.size(); i++) {
                if (s != hand[i].get_suit()) {
                    Deck temp;
                    return temp; //если хоть одна карта не совпадает с мастью 1 из 5, то флеша нет, возращаю пустую руку
                } 
            }
            return hand;
        }
        Deck find_strit(Deck hand) {
            Card m = hand.max_card();
            Card temp;
            for (int i = 0; i < 4; i++) {
                if (hand.find_card(m.get_val()-1) != -1) { //Обычный стрит
                    m = hand[hand.find_card(m.get_val()-1)];
                }
                else if ((m.get_val() == 14) && hand.find_card(5) != -1) { //колесо (А,2,3,4,5)
                    m = hand[hand.find_card(5)]; //правильно работает отъебись
                }
                else {
                    Deck t;
                    return t;
                }
            }
            return hand;
        }
        
        vector<Deck> all_hands() {
            vector<Deck> res;
            Deck temp;
            for (int i = 0; i < deck.size();i++) {
                for (int i2 = i+1; i2 < deck.size(); i2++) {
                    for (int i3 = i2 + 1; i3 < deck.size(); i3++) {
                        for (int i4 = i3 + 1; i4 < deck.size(); i4++) {
                            for (int i5 = i4+1; i5 < deck.size(); i5++) {
                                temp = {deck[i],deck[i2],deck[i3],deck[i4],deck[i5]};
                                res.push_back(temp);
                            }
                        }
                    }
                }
            }
            return res;
        }
        int find_better_hand(Deck full1,Deck combo1,Deck full2,Deck combo2,int N) {
            //вся эта функция нужна чтобы определить лучшую руку при одинаковой комбинации
            if ((N == 1) || (N == 0) || (N == 3) || (N == 5) || (N == 7) || (N == 9)) {
                //для пары,сета ...т.д и флеша реализация тривиальная
                if (combo1.max_card() > combo2.max_card()) {
                    return -1;
                }
                else if (combo1.max_card() < combo2.max_card()) {
                    return 1;
                }
                else {
                    //сравниваем все карты
                    full1.sorted(); full2.sorted();
                    for (int i = 0; i < 5; i++) {
                        if (full1[i] > full2[i]) {
                            return -1;
                        }
                        else if (full1[i] < full2[i]) {
                            return 1;
                        }
                    }
                    //все карты одинаковые
                    return 0;
                }
            } 
            else if (N == 6) {
                //с фуллхаусом дела сложнее
                full1.sorted(); full2.sorted();
                if (full1[2] > full2[2]) {
                    return -1;
                }
                else if (full1[2] < full2[2]) {
                    return 1;
                }
                else if (full1[0] > full2[0]) {
                    return -1;
                }
                else if (full1[0] < full2[0]) {
                    return 1;
                }
                else if (full1[4] > full2[4]) {
                    return -1;
                }
                else if (full1[4] < full2[4]) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else if (N==2) { //две пары
                combo1.sorted();combo2.sorted();
                if (combo1[0] > combo2[0]) {
                    return -1;
                }
                else if (combo1[0] < combo2[0]) {
                    return 1;
                }
                else if (combo1[2] > combo2[2]) {
                    return -1;
                }
                else if (combo1[2] < combo2[2]) {
                    return 1;
                }
                else if ((full1-combo1)[0] > (full2-combo2)[0]) {
                    return -1;
                }    
                else if ((full1-combo1)[0] < (full2-combo2)[0]) {
                    return 1;
                } 
                else {
                    return 0;
                }                           
            }
            if (N == 4  || N == 8) { //стриты
                //ищем колеса
                if ((full1.find_card(14) != -1) && (full1.find_card(2) != -1)) {
                    if ((full2.find_card(14) != -1) && (full2.find_card(2) != -1)) {
                        return 0;
                    }
                    else {
                        return 1;
                    }
                }
                if (full2.find_card(14) != -1 && full2.find_card(2) != -1) { 
                    return -1;
                }
                //просто сравниваем стрит
                if (full1.max_card() > full2.max_card()) {
                    return -1;
                }
                else if (full1.max_card() < full2.max_card()) {
                    return 1;
                }
                return 0;
            }
            //надо стрит дописать  
            return 0; 
        }
        void find_best_combo() {
            vector<Deck> all = all_hands();
            for (int i = 0; i < all.size(); i++)
            {
                int t_best_combo = 0;
                Deck temp;
                Deck only_combo;
                Deck now_hand = all[i];

                //ищем пару,сет и.т.д
                temp = find_pairs(now_hand);
                switch (temp.size())
                {
                case 2:
                    t_best_combo = 1;
                    break;
                case 3:
                    t_best_combo = 3;
                    break;
                case 4:
                    t_best_combo = 7;
                    break;
                case 5:
                    t_best_combo = 9;
                    break;
                }
                only_combo = temp;
                
                //ищем две пары и фуллхаус
                if (t_best_combo <= 6 && best_combo <= 6) {
                    Deck temp2 = find_two_pairs(now_hand);
                    switch (temp2.size())
                    {
                    case 4:
                        if (t_best_combo < 4) {
                            t_best_combo = 2;
                            temp = temp2;
                        }
                        break;
                    case 5: 
                        t_best_combo = 6;
                        temp = temp2;
                    }
                    only_combo = temp;
                }
                //ищем флеш
                if (t_best_combo <= 5 && best_combo <= 5) {
                    Deck temp = find_flash(now_hand);
                    if (temp.size() > 0) {
                        t_best_combo = 5;
                        only_combo = now_hand;
                    }
                } //strit
                if (t_best_combo <= 4 and best_combo <= 4) {
                    Deck temp = find_strit(now_hand);
                    if (temp.size() > 0) {
                        t_best_combo = 4;
                        only_combo = now_hand;
                    }
                }
                //стрит флеш
                if (t_best_combo >= 5 && t_best_combo <= 8) { 
                    if ((find_strit(now_hand).size()> 0) && (find_flash(now_hand).size() > 0)) {
                        t_best_combo = 8;
                        only_combo = now_hand;
                    }
                }
                //итог
                if (t_best_combo > best_combo) {
                    best_hand = now_hand;
                    best_hand_combo = only_combo;
                    best_combo = t_best_combo;
                }
                else if (t_best_combo == best_combo) {
                    int s;
                    s = find_better_hand(best_hand,best_hand_combo,now_hand,only_combo,best_combo);
                    if (s==1) {
                        best_hand = now_hand;
                        best_hand_combo = only_combo;
                    }
                }
                
            }
        }
    public:
        void clear() {
            best_hand.clear();
            best_hand_combo.clear();
            best_combo = -1;
            hands.clear();
        }
        int hands_matcher(const Hand& other) {
            if (best_combo > other.best_combo) {
                return -1;
            } 
            else if (best_combo < other.best_combo) {
                return 1;
            }
            else {
                return find_better_hand(best_hand,best_hand_combo,other.best_hand,other.best_hand_combo,best_combo);
            }
        }
        bool operator==(const Hand& other) {
            return (hands_matcher(other) == 0);
        }
        bool operator>(const Hand& other) {
            return (hands_matcher(other) == -1);
        }
        bool operator<(const Hand& other) {
            return (hands_matcher(other) == 1);
        }
        void calculate() {
            find_best_combo();
        }
        void print_solution() {
            best_hand.print();
            cout<<endl<<best_combo<<endl;
        }
        Hand operator=(Deck d) {
            deck = d.getDeck(); //хз как подругому получать доступ, видимо реально гетер надо писать
            find_best_combo();
            best_hand.sorted();
            return *this; 
        }
};

Deck max(vector<Deck> Z) {
    int m = 0;
    int mi = 0;
    for (int i=0; i < Z.size(); i++) {
        if (Z[i].size() > m) {
            m = Z[i].size();
            mi = i;
        }
    }
    return Z[mi];
}
