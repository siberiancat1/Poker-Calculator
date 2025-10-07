#include "card.h"
//это файл калькулятор
class Calculator {
private:
        unsigned long long N = 10000;
        Deck our_hand;
        Deck p2_hand;
        Deck flop;
        unsigned long long win = 0;
        unsigned long long lost = 0;
        unsigned long long draw = 0;
        unsigned long long iter = 0;
        Deck deck;
    public:
        Calculator(Deck your_hand,Deck player2_hand = {}, Deck now_flop = {}): 
        our_hand(your_hand),p2_hand(player2_hand),flop(now_flop) {

        };
        void print() {
            double eq = ((win * 1.0) + (draw * 0.5) ) / (iter * 1.0);
            cout<<"EQ: "<<eq<<endl;
            cout<<"Win "<<win<<endl<<"Lost "<<lost<<endl<<"Draw "<<draw<<endl;
        }
        void Calculate() {
            deck.SetDefault();
            deck = deck - our_hand - flop - p2_hand;

            for (unsigned long long i = 0; i < N; i++) {
                Hand hp2,hp1;
                Deck t_deck,tf,tp2;

                if (i%1000 == 0) {
                    cout<<(i*1.0*100/N*1.0)<<endl;
                }
                t_deck = deck;
                t_deck.deck_shuffle();
                tp2 = p2_hand;
                tf = flop;
                while (tp2.size() < 2)
                {
                    tp2.take(t_deck);
                }
                while (tf.size() < 5) {
                    tf.take(t_deck);
                }
                hp2 = tp2 + tf;
                hp1 = our_hand + tf;

                if (hp1 == hp2) {
                    draw+=1;
                }
                else if (hp1 > hp2) {
                    win+=1;
                }
                else {
                    lost+=1;
                }
                iter+=1;

                hp1.clear();
                hp2.clear();
                tp2.clear();
                tf.clear();
            }
        cout<<"iteration"<<iter<<endl;
        print();
        }
};