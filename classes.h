#include <iostream>
#include <vector>

class Card{
    public:
        Card(int cardNum, char cardSuit){
            if (cardNum < 1 || cardNum > 10){
                std::cout<<"You did not enter a valid value. Assigning you a 1\n";
                value = 1;   
                        
            } else {
                value = cardNum;
                suit = cardSuit;
            }
        }

        Card(char cardNum, char cardSuit){
            if(cardNum == 'J' || cardNum == 'j'){
                value = 11;
            } else if (cardNum =='Q' || cardNum == 'q'){
                value = 12;
            } else if (cardNum =='K' || cardNum == 'k'){
                value = 13;
            } else if (cardNum == 'A' || cardNum == 'a'){
                value = 14;
            } else {
                std::cout<<"You did not enter a valid value. Assigning you a 1\n";
                value = 1;
                
            }
            suit = cardSuit;
        }

        int value;
        char suit;
};

class Hand{
    public:
        Hand(const Card card1, const Card card2, const Card card3, const Card card4, const Card card5){
            myHand.push_back(card1);
            counter[card1.value]++;
            myHand.push_back(card2);
            counter[card2.value]++;
            myHand.push_back(card3);
            counter[card3.value]++;
            myHand.push_back(card4);
            counter[card4.value]++;
            myHand.push_back(card5);    
            counter[card5.value]++; 

            orderCards();        
            flushCheck();
            straightCheck();
            fourOfAKindCheck();
            threeOfAKindCheck();
            pair1Check();
            pair2Check();    
            getHandRank();
            highCard = myHand[0].value;    

            for (int i = 0; i < 5; i++){
               myHandValues[i] = myHand[i].value;
            }
        }

        int getRank(){
            return rank;
        }

        int getHighCard(){
            return highCard;
        }

    

    void displayCards(){
        for(int i = 0; i < 5; i++){
            if(myHand[i].value == 11){
                std::cout<<"[J of "<<myHand[i].suit<<"] ";
            } else if (myHand[i].value == 12){
                std::cout<<"[Q of "<<myHand[i].suit<<"] ";
            } else if (myHand[i].value == 13){
                std::cout<<"[K of "<<myHand[i].suit<<"] ";                
            } else if (myHand[i].value == 14){
                std::cout<<"[A of "<<myHand[i].suit<<"] ";
            } else {
                std::cout<<"["<<myHand[i].value<<" of "<<myHand[i].suit<<"] ";
            }            
        }
        std::cout<<"\n";
    }

    int fourOfAKindValue = -1;
    int threeOfAKindValue = -1;
    int pair1Value = -1;
    int pair2Value = -1;
    int myHandValues[5];


    private:
        std::vector<Card> myHand;
        
        bool isFlush = false;
        bool isStraight = false;
        bool isFourOfAKind = false;
        bool isThreeOfAKind = false;        
        bool isPair1 = false;        
        bool isPair2 = false;
        int highCard;
        int rank;
        int counter[15]={0};

        void orderCards(){
            Card holder(1,'s');
            for(int i = 0; i < 5; i++){
                for(int j=i+1; j < 5; j++){
                    if(myHand[i].value < myHand[j].value){
                        holder = myHand[i];
                        myHand[i] = myHand[j];
                        myHand[j] = holder;
                    }
                }
            }
        }

        void flushCheck(){
            bool allSameSuit = true;
            char suitCheck = myHand[0].suit;
            for (int i = 1; i < 5; i++){
                if(myHand[i].suit != suitCheck){
                    allSameSuit = false;
                }
            }
            isFlush = allSameSuit;
        }

        void straightCheck(){
            bool straight = true;
            int val = myHand[0].value;
            for(int i = 1; i < 5; i++){
                val--;
                if (myHand[i].value != val){
                    straight = false;
                }
            }
            isStraight = straight;
        }   

        void fourOfAKindCheck(){
            isFourOfAKind = false;
            for(int i = 0; i<14; i++){
                if (counter[i]==4){
                    isFourOfAKind = true;
                    fourOfAKindValue = i;
                }
            }
        }

        void threeOfAKindCheck(){
            isThreeOfAKind = false;
            for(int i = 0; i<15; i++){
                if (counter[i]==3){
                    isThreeOfAKind = true;
                    threeOfAKindValue = i;
                }
            }
        }

        void pair1Check(){
            for(int i = 0; i<15; i++){
                if (counter[i]==2){
                    isPair1 = true;
                    pair1Value = i;                    
                    break;
                }
            }
        }      

        void pair2Check(){
            for(int i = 0; i<15; i++){
                if (counter[i]==2 && ((i)!=pair1Value)){
                    isPair2 = true;
                    pair2Value = i;
                }
            }
        }    

        void getHandRank(){
            if(isFlush && isStraight && highCard == 14){
                rank = 1;            
            } else if (isFlush && isStraight) {
                rank = 2;
            } else if (isFourOfAKind){
                rank = 3;
            } else if (isThreeOfAKind && isPair1){
                rank = 4;
            } else if (isFlush){
                rank = 5;
            } else if (isStraight){
                rank = 6;
            } else if (isThreeOfAKind){
                rank = 7;
            } else if (isPair1 && isPair2){
                rank = 8;
            } else if (isPair1){
                rank = 9;
            } else {
                rank = 10;
            }           
        }

};

class Compare{
    public:
        Compare(Hand hand1, Hand hand2){
            hand1Rank = hand1.getRank();
            hand1HighCard = hand1.getHighCard();
            hand2Rank = hand2.getRank();
            hand2HighCard = hand2.getHighCard();   
            handsToCompare.push_back(hand1);
            handsToCompare.push_back(hand2);   
        }
        int hand1Rank;
        int hand1HighCard;
        int hand2Rank;
        int hand2HighCard;
        std::vector<Hand> handsToCompare;




        void showWinner(){
            if(hand1Rank == hand2Rank){
                switch(hand1Rank){
                    case 2: //straight flush.  high card tie breaker                
                        if(hand1HighCard == hand2HighCard){
                            handsToCompare[0].displayCards();
                            std::cout<<"is the same value as \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Tie!\n";
                        } else if (hand1HighCard > hand2HighCard){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                    
                        } else if (hand1HighCard < hand2HighCard){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";                      
                        }
                        break;
                    case 3: //4 of a kind.  4ofakind value then high card
                        if(handsToCompare[0].fourOfAKindValue == handsToCompare[1].fourOfAKindValue){
                            handsToCompare[0].displayCards();
                            std::cout<<"is the same value as \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Tie!\n";
                        } else if (handsToCompare[0].fourOfAKindValue > handsToCompare[1].fourOfAKindValue){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                    
                        } else if (handsToCompare[0].fourOfAKindValue < handsToCompare[1].fourOfAKindValue){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";                      
                        }
                        break;   
                    case 4:      //full house.  three pair value , then 2 pair tiebreaker                
                        if(handsToCompare[0].threeOfAKindValue == handsToCompare[1].threeOfAKindValue){
                            if(handsToCompare[0].pair1Value == handsToCompare[1].pair1Value){
                                handsToCompare[0].displayCards();
                                std::cout<<"is the same value as \n";
                                handsToCompare[1].displayCards();
                                std::cout<<"Tie!\n";
                            } else if (handsToCompare[0].pair1Value > handsToCompare[1].pair1Value){
                                handsToCompare[0].displayCards();
                                std::cout<<"is greater than \n";
                                handsToCompare[1].displayCards();
                                std::cout<<"Hand 1 Wins!\n";                    
                            } else if (handsToCompare[0].pair1Value < handsToCompare[1].pair1Value){
                                handsToCompare[0].displayCards();
                                std::cout<<"is less than \n";
                                handsToCompare[1].displayCards();
                                std::cout<<"Hand 2 Wins!\n";
                            }
                        } else if (handsToCompare[0].threeOfAKindValue > handsToCompare[1].threeOfAKindValue){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                    
                        } else if (handsToCompare[0].threeOfAKindValue < handsToCompare[1].threeOfAKindValue){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";                      
                        }
                        break;
                    case 5: //flush.  high card descending                        
                        newTieBreaker = tieBreaker(handsToCompare[0], handsToCompare[1]);
                        if (newTieBreaker == 0){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                                 
                        } else if (newTieBreaker == 1){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";                                  
                        } else if (newTieBreaker == -1){
                            handsToCompare[0].displayCards();
                            std::cout<<"is the same value as \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Tie!\n";                                    
                        }
                        break;
                    case 6:  //straight.  high card
                        if(hand1HighCard == hand2HighCard){
                            handsToCompare[0].displayCards();
                            std::cout<<"is the same value as \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Tie!\n";
                        } else if (hand1HighCard > hand2HighCard){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                    
                        } else if (hand1HighCard < hand2HighCard){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";
                        }      
                        break;
                    case 7: //3 of a kind.  three pair value then high card descending
                        if(handsToCompare[0].threeOfAKindValue == handsToCompare[1].threeOfAKindValue){
                            newTieBreaker = tieBreaker(handsToCompare[0], handsToCompare[1]);
                            if (newTieBreaker == 0){
                                handsToCompare[0].displayCards();
                                std::cout<<"is greater than \n";
                                handsToCompare[1].displayCards();
                                std::cout<<"Hand 1 Wins!\n";                                 
                            } else if (newTieBreaker == 1){
                                handsToCompare[0].displayCards();
                                std::cout<<"is less than \n";
                                handsToCompare[1].displayCards();
                                std::cout<<"Hand 2 Wins!\n";                                  
                            } else if (newTieBreaker == -1){
                                handsToCompare[0].displayCards();
                                std::cout<<"is the same value as \n";
                                handsToCompare[1].displayCards();
                                std::cout<<"Tie!\n";                                    
                            }
                        } else if (handsToCompare[0].threeOfAKindValue > handsToCompare[1].threeOfAKindValue){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                    
                        } else if (handsToCompare[0].threeOfAKindValue < handsToCompare[1].threeOfAKindValue){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";
                        }
                        break;
                    case 8: //2 pair.  pair2 value then pair 1 value then high card descending
                        if(handsToCompare[0].pair2Value == handsToCompare[1].pair2Value){
                            if(handsToCompare[0].pair1Value == handsToCompare[1].pair1Value){
                                newTieBreaker = tieBreaker(handsToCompare[0], handsToCompare[1]);
                                if (newTieBreaker == 0){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is greater than \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Hand 1 Wins!\n";                                 
                                } else if (newTieBreaker == 1){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is less than \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Hand 2 Wins!\n";                                  
                                } else if (newTieBreaker == -1){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is the same value as \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Tie!\n";                                    
                                }
                            } else if (handsToCompare[0].pair1Value > handsToCompare[1].pair1Value){
                                handsToCompare[0].displayCards();
                                std::cout<<"is greater than \n";
                                handsToCompare[1].displayCards();
                                std::cout<<"Hand 1 Wins!\n";                    
                            } else if (handsToCompare[0].pair1Value < handsToCompare[1].pair1Value){
                                handsToCompare[0].displayCards();
                                std::cout<<"is less than \n";
                                handsToCompare[1].displayCards();
                                std::cout<<"Hand 2 Wins!\n";
                            }
                        } else if (handsToCompare[0].pair2Value > handsToCompare[1].pair2Value){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                    
                        } else if (handsToCompare[0].pair2Value < handsToCompare[1].pair2Value){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";
                        }
                        break;
                    case 9: // pair.  pair 1 value, then high card descending
                        if(handsToCompare[0].pair1Value == handsToCompare[1].pair1Value){
                            newTieBreaker = tieBreaker(handsToCompare[0], handsToCompare[1]);
                                if (newTieBreaker == 0){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is greater than \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Hand 1 Wins!\n";                                 
                                } else if (newTieBreaker == 1){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is less than \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Hand 2 Wins!\n";                                  
                                } else if (newTieBreaker == -1){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is the same value as \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Tie!\n";                                    
                                }
                        } else if (handsToCompare[0].pair1Value > handsToCompare[1].pair1Value){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                    
                        } else if (handsToCompare[0].pair1Value < handsToCompare[1].pair1Value){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";
                        }
                        break;
                    case 10:  //high card
                        if(hand1HighCard == hand2HighCard){
                            newTieBreaker = tieBreaker(handsToCompare[0], handsToCompare[1]);
                                if (newTieBreaker == 0){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is greater than \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Hand 1 Wins!\n";                                 
                                } else if (newTieBreaker == 1){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is less than \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Hand 2 Wins!\n";                                  
                                } else if (newTieBreaker == -1){
                                    handsToCompare[0].displayCards();
                                    std::cout<<"is the same value as \n";
                                    handsToCompare[1].displayCards();
                                    std::cout<<"Tie!\n";                                    
                                }
                        } else if (hand1HighCard > hand2HighCard){
                            handsToCompare[0].displayCards();
                            std::cout<<"is greater than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 1 Wins!\n";                    
                        } else if (hand1HighCard < hand2HighCard){
                            handsToCompare[0].displayCards();
                            std::cout<<"is less than \n";
                            handsToCompare[1].displayCards();
                            std::cout<<"Hand 2 Wins!\n";
                        }      
                        break;
                }                      


            } else if (hand1Rank < hand2Rank){
                    handsToCompare[0].displayCards();
                    std::cout<<"is greater than \n";
                    handsToCompare[1].displayCards();
                    std::cout<<"Hand 1 Wins!\n";                  
            } else if (hand1Rank > hand2Rank){
                    handsToCompare[0].displayCards();
                    std::cout<<"is less than \n";
                    handsToCompare[1].displayCards();
                    std::cout<<"Hand 2 Wins!\n";                   
            }
        }

    private:
        int tieBreaker(Hand hand0, Hand hand1){
            int winner = -1;
            for (int i = 0; i < 5; i++){
                if(hand0.myHandValues[i] > hand1.myHandValues[i]){
                    return 0;
                } else if (hand0.myHandValues[i] < hand1.myHandValues[i]){
                    return 1;
                }
            }
            return -1;
        }

        int newTieBreaker;
};