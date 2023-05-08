#include "cardClasses.h"

int main(){

    std::cout<<"Welcome to Poker...\n";
    std::cout<<"Press 0 if player 2 is human, 1 if it's a computer\n";
    int check2; //used to determine AI or human
    std::cin >> check2;


    Player player1(100, 1);
    Player player2(100, check2);

    while (player1.GetChips()>0 and player2.GetChips()>0){
        int handPot = 0;
        int temp; //used only for pauses in cin
        int p1Bet = 0;
        int p2Bet = 0;
        int p1Bet2 = 0;
        int p2Bet2 = 0;
        player1.tempHand_.ClearHand();
        player1.hand_.clearHand();
        player2.tempHand_.ClearHand();
        player2.hand_.clearHand();

        Deck deck;
        deck.Shuffle();
        std::cout<<"Player 1 is dealt: \n";
        for (int i = 0; i < 5; ++i) {
            deckCard card = deck.DealCard();
            Card tempCard(card.rank, card.suit);
            std::cout << "Dealt card: " << card.rank << " of " << card.suit << std::endl;  
            player1.tempHand_.AddCard(tempCard);  
        }

        std::cout<<"\nPlayer 2 is dealt: \n";

        for (int i = 0; i < 5; ++i) {
            deckCard card = deck.DealCard();
            Card tempCard(card.rank, card.suit);
            std::cout << "Dealt card: " << card.rank << " of " << card.suit << std::endl;  
            player2.tempHand_.AddCard(tempCard);  
        }

        std::cout<<"\nPlayer 1 bet("<<player1.GetChips()<<" chips remaining): \n";   
        std::cin>>p1Bet;     
        std::cout<<"\nPlayer 2 bet("<<player2.GetChips()<<" chips remaining) must match or exceed or GO ALL IN: "<< p1Bet<< ".\n";   
        if(player2.humanOrAi==0){
            std::cin>>p2Bet; 
        } else {
            if(player2.GetChips()>=player1.GetChips()){
                std::cout<<"beep boop, i call with "<<p1Bet<<" chips.\n";
                p2Bet = p1Bet;
            } else {
                std::cout<<"beep boop, i go all in with "<<player2.GetChips()<<" chips.\n";
                p2Bet = player2.GetChips();                
            }
        }
           

        if (p2Bet > p1Bet){
            std::cout<<"\nPlayer 1 bet must match or GO ALL IN: "<< p2Bet<< ".\n";               
            std::cin>>p1Bet;              
        }

        player1.RemoveChips(p1Bet);
        player2.RemoveChips(p2Bet);

        //if the bets are equal or one of the players went all in
        if (p1Bet == p2Bet || (p1Bet == player1.GetChips() && p2Bet > 0) || (p2Bet == player2.GetChips() && p1Bet > 0)){
            bool p1Discard = true;
            int discardCheck;
            std::vector<int> discardCounter = {};
            while(p1Discard){
                std::cout<<"\nPlayer 1 would you like to discard additional cards? 0=no 1=yes: ";
                std::cin>>discardCheck;
                if(discardCheck == 1){
                    int chooseCard;
                    std::cout<<"\nEnter the index of card to discard (starting at 0): ";
                    std::cin>>chooseCard;
                    discardCounter.push_back(chooseCard);                    
                } else {
                    p1Discard = false;
                }
            }
            if (discardCounter.size() > 0){
                for (int i = 0; i < discardCounter.size(); i++){
                    player1.tempHand_.RemoveCard(discardCounter[i]);
                }
                for (int i = 0; i < discardCounter.size()-1; i++){
                    deckCard card = deck.DealCard();
                    Card tempCard(card.rank, card.suit);
                    std::cout << "Newly Dealt card: " << card.rank << " of " << card.suit << std::endl;  
                    player1.tempHand_.AddCard(tempCard);  
                }        
            } 

            if(player2.humanOrAi == 0){
                bool p2Discard = true;
                discardCheck=0;
                discardCounter = {};
                while(p2Discard){
                    std::cout<<"\nPlayer 2 would you like to discard additional cards? 0=no 1=yes: ";
                    std::cin>>discardCheck;
                    if(discardCheck == 1){
                        int chooseCard;
                        std::cout<<"\nEnter the index of card to discard (starting at 0): ";
                        std::cin>>chooseCard;
                        discardCounter.push_back(chooseCard);                    
                    } else {
                        p2Discard = false;
                    }
                }
                if (discardCounter.size() > 0){
                    for (int i = 0; i < discardCounter.size()-1; i++){
                        player2.tempHand_.RemoveCard(discardCounter[i]);
                    }
                    for (int i = 0; i < discardCounter.size(); i++){
                        deckCard card = deck.DealCard();
                        Card tempCard(card.rank, card.suit);
                        std::cout << "Newly Dealt card: " << card.rank << " of " << card.suit << std::endl;  
                        player2.tempHand_.AddCard(tempCard);  
                    }        
                }
            } else {
                std::cout << "Beep boop, im bad at poker, i'll keep my cards this time ;) \n";
            }
        } 

        std::cout<<"\nDRAW BET Player 1 bet("<<player1.GetChips()<<" chips remaining): \n";   
        std::cin>>p1Bet2;     
        std::cout<<"\nDRAW BET Player 2 bet("<<player2.GetChips()<<" chips remaining) must match or exceed or GO ALL IN: "<< p1Bet2<< ".\n";   
        if(player2.humanOrAi==0){
            std::cin>>p2Bet; 
        } else {
            if(player2.GetChips()>=player1.GetChips()){
                std::cout<<"beep boop, i call with "<<p1Bet2<<" chips.\n";
                p2Bet2 = p1Bet2;
            } else {
                std::cout<<"beep boop, i go all in with "<<player2.GetChips()<<" chips.\n";
                p2Bet2 = player2.GetChips();                
            }
        } 

        if (p2Bet > p1Bet){
            std::cout<<"\nPlayer 1 bet must match or GO ALL IN: "<< p2Bet2<< ".\n";               
            std::cin>>p1Bet2;              
        }

        player1.RemoveChips(p1Bet2);
        player2.RemoveChips(p2Bet2);
        handPot += (p1Bet+p2Bet+p1Bet2+p2Bet2);
        
        player1.hand_.buildHand(player1.tempHand_.GetHand());
        player2.hand_.buildHand(player2.tempHand_.GetHand());

        Compare comparison1(player1.hand_, player2.hand_);
        int winner = comparison1.showWinner();
        if (winner == 1){
            player1.AddChips(handPot);
            std::cout<<"Player 1 Wins this hand and "<<handPot<<" chips. Press any number key to contnue.\n";
            std::cin>>temp;
        } else if (winner == 2) {
            player2.AddChips(handPot);
            std::cout<<"Player 2 Wins this hand and "<<handPot<<" chips. Press any number key to contnue.\n";
            std::cin>>temp;
        } else {
            player1.AddChips(p1Bet);
            player2.AddChips(p2Bet);
            std::cout<<"This hand was a tie. "<<handPot<<" chips returned. Press any number key to contnue.\n";
            std::cin>>temp;
        }
    }

    return 0;
}