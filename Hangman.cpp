#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>  //for std::vector
#include <time.h>

using namespace std;

string fileName = "words.txt";
int errors = 0; //Count the errors of tries on the game
int hits = 0; //Count the hits of tries on the game


//count quantity of lines and return this quantity
int countLines(){
	int countLines = 0;
	string line;
	
	ifstream myfile ("words.txt"); 
  if (myfile.is_open()){
    while (! myfile.eof()){ 
    	getline (myfile,line);
      countLines++;
    }
    myfile.close();
  }
  return countLines;
}

//Read the file and write on array
void loadWords(string words[]){
	string textLine;
	int count = 0;
	
  ifstream myfile ("words.txt"); 
  if (myfile.is_open()){
    while (! myfile.eof()){
	  getline (myfile,textLine);
      	words[count] = textLine;
      	count++;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
  
}

//Return a aleatory word
string chooseWord(string words[]){
	time_t t;
    srand((unsigned) time(&t));
    int qttLines = countLines();
    int sortNumber = rand() % qttLines;	
	
	return words[sortNumber];
}

//Count the quantity of letters on the word
int countLetter(string word){
	int i = 0;
	while (word[i] != NULL){
		i++;
	}
	return i;
}

//Calculate erros using the quantity of letters on the word
int sumErrors(){
	return errors++; 
}

//Calculate erros using the quantity of letters on the word
int sumHits(){
	return hits ++; 
}

//Receive a letter by the user
char getLetter(){
	char letter;
	cout << endl << "Set a letter: ";
	cin >> letter;
	return letter;
}

//startVetor with _
void startVetor(char playWordSecret[], string playWord){
	for (int i = 0; i < countLetter(playWord); i++){
		playWordSecret[i] = 95;
	}
}

//Show de hangman
void hangman(string playWord){
	
	if(errors == 0){
		cout << endl;
		cout << "  +----+" << endl;
  		cout << "  |    |" << endl;
      	cout << "       |" << endl;
      	cout << "       |" << endl;
      	cout << "       |" << endl;
      	cout << "       |" << endl;
		cout << "========" << endl;
	} else if(errors == 1){
		cout << endl;
		cout << "  +----+" << endl;
  		cout << "  |    |" << endl;
      	cout << "  O    |" << endl;
      	cout << "       |" << endl;
      	cout << "       |" << endl;
      	cout << "       |" << endl;
		cout << "========" << endl;
	} else if(errors == 2){
		cout << endl;
		cout << "  +----+" << endl;
  		cout << "  |    |" << endl;
      	cout << "  O    |" << endl;
      	cout << "  |    |" << endl;
      	cout << "       |" << endl;
      	cout << "       |" << endl;
		cout << "========" << endl;
	} else if(errors == 3){
		cout << endl;
		cout << "  +----+" << endl;
  		cout << "  |    |" << endl;
      	cout << "  O    |" << endl;
      	cout << " /|    |" << endl;
      	cout << "       |" << endl;
      	cout << "       |" << endl;
		cout << "========" << endl;
	} else if(errors == 4){
		cout << endl;
		cout << "  +----+" << endl;
  		cout << "  |    |" << endl;
      	cout << "  O    |" << endl;
      	cout << " /|\\   |" << endl;
      	cout << "       |" << endl;
      	cout << "       |" << endl;
		cout << "========" << endl;
	} else if(errors == 5){
		cout << endl;
		cout << "  +----+" << endl;
  		cout << "  |    |" << endl;
      	cout << "  O    |" << endl;
      	cout << " /|\\   |" << endl;
      	cout << " /     |" << endl;
      	cout << "       |" << endl;
		cout << "========" << endl;
	}
	else if(errors == 6){
		cout << endl;
		cout << "  +----+" << endl;
  		cout << "  |    |" << endl;
      	cout << "  O    |" << endl;
      	cout << " /|\\   |" << endl;
      	cout << " / \\   |" << endl;
      	cout << "       |" << endl;
		cout << "========" << endl;
		cout << "YOU LOSE!!!!!!" << endl;
		cout << "The correct word is: " << playWord << endl;
		cout << "Really you are a loser..." << endl;
		exit(0);
	}
	
	if (hits == countLetter(playWord)){
		cout << "You won something on your life..." << endl;
	}
}

//Receive a letter, compare with the sort word
void processLetter(string playWord, char playWordSecret[]){
	
	char playWordSecretCompare[countLetter(playWord)];
	int countLettersEqualsBefore = 0;
	for(int i = 0; i < countLetter(playWord); i++){
		playWordSecretCompare[i] = playWordSecret[i];
		countLettersEqualsBefore++;
	}
	
	char letter = getLetter();
	
	for(int i = 0; i < countLetter(playWord); i++){
		if(playWord[i] == letter){
			playWordSecret[i] = letter; 
			sumHits();
		} 
	}

	int countLettersEqualsAfter = 0;
	
	for(int i = 0; i < countLetter(playWord); i++){
		if(playWordSecretCompare[i] == playWordSecret[i]){
			countLettersEqualsAfter++;
		}
	}
	
	int difference = countLettersEqualsAfter - countLettersEqualsBefore;
	//Compare equals letters before and after operations
	if(difference == 0){
		sumErrors();
	}

}

//Refresh the console
void refreshScreen(string playWord, char playWordSecret[]){
	hangman(playWord);
	
	for(int i = 0; i < countLetter(playWord); i++){
		cout << playWordSecret[i] << " ";
	}
	
	if (hits == countLetter(playWord)){
		exit(0);	
	}
	processLetter(playWord, playWordSecret);
}

//Start the game
void startGame(){
	string words[countLines()];
	loadWords(words);
	string playWord = chooseWord(words);
	
	//cout << playWord << endl;
	char playWordSecret[countLetter(playWord)];
	
	startVetor(playWordSecret, playWord);
	//cout << playWordSecret;
	
	while (errors <= 6){
		refreshScreen(playWord, playWordSecret);
		system("cls");
	}
}

int main () {

	startGame();

  return 0;
}
