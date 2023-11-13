/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: kboss
 *
 * Created on October 25, 2023, 6:47 PM
 */

#include <cstdlib>
#include "Deck.h"
#include "Hand.h"
#include <string>
#include <map>

#include <iostream>
using namespace std;

/*
 *
 */

void playBlackJack(); 

void playWar(); 
  

int main(int argc, char** argv) {
    
    srand(time(0)); 
    
    
    bool playing= true; 
    
    while(playing)
    {
        cout<<"Would you like to play Blackjack or War ? (b/w): "<<endl; 
        
        char response ; 
        
        cin>> response ; 
        
        while(response!='b' && response!='w' )
        {
            cout<<"Not a valid response try again"<<endl; 
            cin>> response ; 
        }
        
        if(response == 'b')
        {
            playBlackJack(); 
        }else
        {
            playWar(); 
        }
        
        
        cout<<"Would you like to keep play another game? (y/n): "; 
        cin>>response; 
        
        
        while(response!='y' && response != 'n')
        {
            cout<<"Not a valid response try again"<<endl; 
            cout<<"Would you like to keep play another game? (y/n): "; 
            cin>>response ; 
        }
        if(response!='y')
        {
            cout<<"Ok good games, see you later!"<<endl; 
            playing = false; 
        }
        
    }
    return 0;
}


void playBlackJack(){
    cout<<endl<<"BLACKJACK SIMULATION"<<endl<<endl; 
    cout<<"(WIKIHOW) In Blackjack, every player is competing against the dealer—not each other. In a given round, the player’s ultimate goal is to get a hand that’s higher than the dealer’s (without being higher than 21, or \"busting\"). Only by beating the dealer can a player win their bet. Players determine the value of their hand by tallying up the point values of their cards:"<<endl; ; 
    cout<<"2 through 10: The number listed on the card (e.g., 2 is worth 2 points)"<<endl; 
    cout<<"Jack, Queen, King: 10 points"<<endl; 
    cout<<"Ace: 1 or 11 points (the player gets to choose)"<<endl; 
    cout<<"An Ace and a 10, Jack, Queen, or King equals 21 points and is known as a Blackjack."<<endl; 
    
    bool gameOver= false ; 
    
    map<string,int> scoreMap ; // using a map to take scare of score 
    scoreMap["Computer"]= 0; 
    scoreMap["Player"] = 0 ; 
 
    // main game loop 
    while(!gameOver)
    {
        cout<<endl<<endl<<"ROUND START, SHUFFLING CARDS..."<<endl ;
        Deck deck; 
        
        // a hand is going to be a queue for both the computer and the player 
        // deal cards between both the player and the computer until the deck is empty 
        Hand computerHand; 
        Hand playerHand; 
        
        //deal to all players 
        
        
        for(int i =0; i< 2 ; i++)
        {
            computerHand.addCard(deck.dealCard()); 
            playerHand.addCard(deck.dealCard()); 
        }
        
        //show dealers first card 
        cout<<"Here is the dealers first card: "; 
        computerHand.showTop(); 
        cout<<endl; 
        
        
        int playerHandVal = playerHand.calcHand(); 
        
        if(playerHandVal == 21 )
        {
            cout<<"Woah you drew 21 on first round very lucky :)"<<endl; 
            cout<<"YOU WIN"<<endl; 
            scoreMap["Player"] ++; 
        }else{
            
            // ask the player if they would like to draw can continue asking until they bust or say no 
            bool confirmation =true; 
            
            while(playerHandVal <21 && confirmation==true)
            {
                cout<<"Your hand is :" ; 
                playerHand.printHand(); 
                cout<<endl; 
                cout<<"The current value of your hand is: "<< playerHandVal<<endl; 
                cout<<"Would you like another hit? (y/n): "; 
                char response; 
                cin>>response ; 
                
                while(response!='y' && response != 'n')
                {
                    cout<<"Not a valid response try again"<<endl; 
                    cout<<"Would you like another hit? (y/n): "; 
                    cin>>response ; 
                }
                
                if(response == 'y')
                {
                    // give player another card 
                    playerHand.addCard(deck.dealCard()); 
                    playerHandVal = playerHand.calcHand(); 
                }else{
                    confirmation = false; 
                }
            }
            
            
            if(playerHandVal > 21)
            {
                cout<<"Oh no you busted with a val of: " <<playerHandVal<<endl; 
                cout<<"YOU LOSE"<<endl; 
                // computer wins the game 
                scoreMap["Computer"]++; 
            }else if(playerHandVal==21)
            {
                cout<<"You hand has a value of 21"<<endl; 
                cout<<"YOU WIN"<<endl; 
                scoreMap["Player"] ++; 
            }
            else
            {
                cout<<"Your final hand is: "; 
                
                playerHand.printHand(); 
                
                cout<<" With a final val of "<<playerHandVal<<endl; 
                
                // if the dealers hand isn't greater than 16 they have to draw another 
                cout<<"The dealer's hand is: "; 
                computerHand.printHand(); 
                
                int computerHandVal = computerHand.calcHand(); 
                cout<<" With a current value of: "<< computerHandVal<<endl; 
                
                while(computerHandVal <=16)
                {
                    computerHand.addCard(deck.dealCard()); 
                    cout<<"The dealer's new hand is: "; 
                    computerHand.printHand(); 
                
                     computerHandVal = computerHand.calcHand(); 
                    cout<<" With a new value of: "<< computerHandVal<<endl; 
                }
                
                if(computerHandVal > 21)
                {
                    cout<<"The dealer busted with a value of: "<<computerHandVal<<endl;
                    cout<<"YOU WIN"<<endl; 
                    scoreMap["Player"] ++; 
                }else{
                    // now we have to see who has the higher hand 
                    if(computerHandVal == playerHandVal)
                    {
                        cout<<"You and the dealer drew with a hand value of: "<< playerHandVal<<endl; 
                    }else if ( playerHandVal > computerHandVal)
                    {
                        cout<<"YOU WIN"<<endl; 
                        scoreMap["Player"] ++; 
                    }else{
                        cout<<"YOU LOSE"<<endl; 
                        scoreMap["Computer"] ++; 
                    }
                        
                }
            }
             
        }
        
        
        // ask the player if they would like to continue playing
        // then clear screen and go again
        char response ; 
        cout<<"SCORES:   PLAYER: "<<scoreMap["Player"]<<" |  DEALER: "<<scoreMap["Computer"]<<endl; 
        cout<<"Would you like to keep playing BlackJack? (y/n): "; 
        cin>>response; 
        
        
        while(response!='y' && response != 'n')
        {
            cout<<"Not a valid response try again"<<endl; 
            cout<<"Would you like to keep playing? (y/n): "; 
            cin>>response ; 
        }
        if(response!='y')
        {
            cout<<"Ok good games, see you later!"<<endl<<endl; 
            gameOver = true; 
        }
        
       
        
    }
    
}


void playWar()
{
    cout<<endl<<"WAR SIMULATION"<<endl<<endl; 
    
    cout<<"In war the objective of the game is to win all the cards in the deck"<<endl; 
    cout<<"At the start of the game, the deck is split between the two players"<<endl; 
    cout<<"Then each round both player show the top card of their individual decks"<<endl; 
    cout<<"Whoever has the higher card gets both of the cards and puts them at the bottom of their decks."<<endl; 
    cout<<"This continues until every card is in one player's deck which would make them the winner"<<endl; 
    
    cout<<"If both the players cards equal each other when they are shown, then three more cards from each player are set aside"<<endl; 
    cout<<"Then the players once more show their top card"<<endl; 
    cout<<"Whoever wins that round gets all 10 cards"<<endl; 
    cout<<"Good Luck!"<<endl; 
    
    
    
    bool gameOver= false ; 
    
    map<string,int> scoreMap ; // using a map to take scare of score 
    scoreMap["Computer"]= 0; 
    scoreMap["Player"] = 0 ; 
    
    while(!gameOver)
    {
        
        //first create a new shuffled deck

        Deck deck ; 

        // then split deck between both players 

        Hand playerHand; 
        Hand computerHand ; 

        for(int i = 0 ; i<26 ; i++ )
        {
            playerHand.addCard(deck.dealCard()); 
            computerHand.addCard(deck.dealCard()); 
        }
        
        
        // now the rounds can start 
        while(!playerHand.isEmpty() && !computerHand.isEmpty())
        {
           
            // each player deals from their deck 
            cout<<"Press enter to draw from the top of your deck."
        }
    }
    
}