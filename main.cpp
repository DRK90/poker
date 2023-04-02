#include "classes.h"

int main(){
    Card card1(8,'d');
    Card card2(10,'d');
    Card card3(7,'d');
    Card card4(6,'s');
    Card card5(4,'h');

    Card card6(8,'c');
    Card card7(10,'c');
    Card card8(7,'c');
    Card card9(6,'s');
    Card card10(4,'d');

    Hand hand1(card1, card2, card3, card4, card5);
    Hand hand2(card6, card7, card8, card9, card10);

    Compare comparison1(hand1, hand2);
    comparison1.showWinner();
    

    return 0;
}