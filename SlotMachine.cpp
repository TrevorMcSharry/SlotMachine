//Trevor McSharry
//10/07/2020
//Slot machine that uses RNG and keeps track of coins and allows players to bet and keeps track of play history

#include <iostream>
#include <random>
#include <limits>
#include <vector>

using namespace std;

int main(){
//Declares variables and prompts a user for a seed value
	int reel[3];
	unsigned int seed;
	int coins = 100;
	int bet;
//Sets up vectors to store wagers and winnings and find min and max of each
	vector<int> wagers;
	vector<int> winnings;
	int minWager;
	int maxWager;
	int minWinnings;
	int maxWinnings;
	//Error checking for seed
	cout << "Input seed: ";
	while(!(cin >> seed)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input seed: ";
	}
//Sets up the random integer based on seed and boundaries
	default_random_engine rng(seed);
//loop that executes until bet is 0 or runs out of coins
	do{
//Assigns random ints to reel array
		uniform_int_distribution<int> rand_int(2, 7);
		for(int i = 0; i < 3; i++){
			reel[i] = rand_int(rng);
		}

		int matches = 0;
//checks for how many matches in the array reel
		for(int i = 0; i < 3; i++){
			int temp = 0;
			for (int j = 0; j < 3; j++){
				if (reel[i] == reel[j]){++temp;}
			}
			if(temp >= matches){
				matches = temp;
			}
		}
//Prompts user for bet and takes bet
		cout << "You currently possess " << coins << " coins.\n";
		cout << "Bet how many coins? ";

//Error checking of bet
		while(!(cin >> bet)) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Not a valid bet. Try again. " << endl;
			cout << "Bet how many coins? ";
		}
//Error checking if bet is larger than current coins
		while( bet > coins ){
			cout << "You can't bet more than you have." << endl;
			cout << "Bet how many coins? ";
			bet = 0;
			cin >> bet;
		}

		coins -= bet;
//Outputs reel if bet is smaller than amount of coins and bet isn't 0
		if (bet != 0 || bet > coins){
			cout << " " << reel[0] << " " << reel[1] << " " << reel[2] << "\n";
//Sets prize winnings based on winning conditions and stores values into vector
			if (reel[0] == 7 && reel[1] == 7 && reel[2] == 7){
				coins = coins + (bet*10);
				cout << "You won " << bet*10 << " coins!\n\n";
				winnings.push_back(bet*10);
				wagers.push_back(bet);
			}
			else if( matches == 3){
				coins = coins + (bet*5);
				cout << "You won " << bet*5 << " coins!\n\n";
				winnings.push_back(bet*5);
				wagers.push_back(bet);
			}
			else if( matches == 2){
				coins = coins + (bet*2);
				cout << "You won " << bet*2 << " coins!\n\n";
				winnings.push_back(bet*2);
				wagers.push_back(bet);
			}
			else{
				cout << "You did not win.\n\n";
				winnings.push_back(0);
				wagers.push_back(bet);
			}
		}	
	}while( bet !=0 && coins > 0);
//Outputs play by play summarry of wagers and winnings
	cout << "Play summary:\n";
	for(unsigned int k = 0; k < wagers.size(); k++){
		cout << k+1 << ". Your wager was " << wagers.at(k) << " coins, and you won was " << winnings.at(k) << " coins.\n";
	}
//Finds and outputs min and max of wager and winnings from the session
	minWager = wagers.at(0);
	maxWager = wagers.at(0);
	minWinnings = winnings.at(0);
	maxWinnings = winnings.at(0);

	for(unsigned int k = 0; k < wagers.size(); k++){
		if(maxWager < wagers.at(k)){
			maxWager = wagers.at(k);
		}

		if(minWager > wagers.at(k)){
			minWager = wagers.at(k);
		}

		if(maxWinnings < winnings.at(k)){
			maxWinnings = winnings.at(k);
		}

		if(minWinnings > winnings.at(k)){
			minWinnings = winnings.at(k);
		}
	}
	cout << endl;
	cout << "Your min wager was " << minWager << " coins.\n";
	cout << "Your max wager was " << maxWager << " coins.\n";
	cout << "Your min win was " << minWinnings << " coins.\n";
	cout << "You max win was " << maxWinnings << " coins.\n";
	
	return 0;

}
