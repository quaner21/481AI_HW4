#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <time.h> 

using namespace std;

// Define some constants/parameter settings
const float PI = 3.141593;
const float XOVER = 0.80;
const float MUTATION = 0.01;
const int POPUSIZE = 500;

// Global Variable
vector<char*> population;    

// Functions
void printString(char* str) {
	for (int i = 0; i < 22; i++) {                          // generate two children as copies of parents
		cout << str[i];
	}
	cout << endl;
}

double fitnessFunc(char* bitString) {
	double bitValue = 0.0;
	for (int i = 0; i < 22; i++) {
		//cout << bitString[i];
		bitValue += (bitString[21 - i] - '0') * pow(2.0, i); // convert bit to its base 2 value
	}
	//cout << endl;
	//cout << bitValue << endl;
	double value = bitValue * 3 / (pow(2.0, 22) - 1) - 1.0;   // map base 2 value to value on [-1,2] 
	//cout << value << endl;
	return (sin(10*PI*value)*value + 1);                     // fitness value -> goal: find the max
}

void crossOver(char* string1, char* string2) {
	char tempStr1[22];
	char tempStr2[22];
	for (int i = 0; i < 22; i++) {                          // generate two children as copies of parents
		tempStr1[i] = string1[i];
		tempStr2[i] = string2[i];
	}
	//cout << "parent strings for crossover: " << endl;
	//printString(&tempStr1[0]);
	//printString(&tempStr2[0]);

	float fitVStr1 = fitnessFunc(string1);
	float fitVStr2 = fitnessFunc(string2);
	float fitVtempStr1 = fitnessFunc(tempStr1);
	float fitVtempStr2 = fitnessFunc(tempStr2);

	int rateC = rand() % 100;
	//cout << "crossover rate: " << rateC << endl;
	if (rateC < XOVER*100) {                                         // 80% chance to crossover
		int numBits = rand() % 11 + 1;
		//cout << "number of bits to crossover: " << numBits << endl;
		int xoverPnt = rand() % (23 - numBits);
		//cout << "crossover occurs at bit " << xoverPnt << endl;

		for (int i = 0; i < numBits; i++) {                 // swap components in the two strings to create children
			tempStr1[xoverPnt + i] = string2[xoverPnt + i];
			tempStr2[xoverPnt + i] = string1[xoverPnt + i];
		}
		//cout << "after crossover, children strings: " << endl;
		//printString(&tempStr1[0]);
		//printString(&tempStr2[0]);

		if (fitVtempStr1 < fitVStr1 && fitVtempStr1 < fitVStr2 // if both children worse, do nothing
			&& fitVtempStr2 < fitVStr1 && fitVtempStr2 < fitnessFunc(string2)) {
		}
		else if (fitVtempStr1 > fitVStr1 && fitVtempStr1 > fitVStr2 // if both children better, replace
			&& fitVtempStr2 > fitVStr1 && fitVtempStr2 > fitVStr2) {
			for (int i = 0; i < 22; i++) {                          
				string1[i] = tempStr1[i];
				string2[i] = tempStr2[i];
			}
		}
		else if (fitVStr1 > fitVStr2 && fitVtempStr1 > fitVtempStr2) {
			for (int i = 0; i < 22; i++) {
				string2[i] = tempStr1[i];
			}
		}
		else if (fitVStr2 > fitVStr1 && fitVtempStr1 > fitVtempStr2) {
			for (int i = 0; i < 22; i++) {
				string1[i] = tempStr1[i];
			}
		}
		else if (fitVStr1 > fitVStr2 && fitVtempStr2 > fitVtempStr1) {
			for (int i = 0; i < 22; i++) {
				string2[i] = tempStr2[i];
			}
		}
		else if (fitVStr2 > fitVStr1 && fitVtempStr2 > fitVtempStr1) {
			for (int i = 0; i < 22; i++) {
				string1[i] = tempStr2[i];
			}
		}
		//cout << "after fitness selection, strings to keep in population: " << endl;
		//printString(string1);
		//printString(string2);
		return;
	}
}

void mutation(){
	for (int i = 0; i < POPUSIZE; i++){
		for (int j = 0; j < 22; j++){
			int rateM = rand() % 100;
			//cout << "mutation rate: " << rateM << endl;
			if (rateM < MUTATION * 100){
				if (population[i][j] == '0'){        // flip the bit
					population[i][j]++;
				}
				else {
					population[i][j]--;
				}  
			}
		}
	}
}


int main() {
	srand(time(NULL));

	double x;

	// **************First Generation************
	for (int j = 0; j < POPUSIZE; j++) {                    
		char* temp;
		temp = new char[22];
		for (int i = 0; i < 22; i++) {                       // randomly generate bitstrings representing x
			temp[i] = '0' + rand() % 2;
			//cout << temp[i];
		}
		//cout << endl;
		//cout << fitnessFunc(temp) << endl;
		population.push_back(temp);
	}
	cout << "population size " << population.size() << endl; 

	// debug
	/*cout << "first generation population: " << endl;
	for (int i = 0; i < POPUSIZE; i++) {
		for (int j = 0; j < 22; j++) {
			cout << population[i][j];
		}
		cout << endl;
	}*/
	// end debug

	int index = 0;
	float maxOutcome = fitnessFunc("0000000000000000000000"); // Not sure if it's a good way to initialize
	for (int i = 0; i < POPUSIZE; i++) {
		if (fitnessFunc(population[i]) > maxOutcome) {
			maxOutcome = fitnessFunc(population[i]);
			index = i;
		}
	}

	double tempBitValue = 0.0;
		for (int i = 0; i < 22; i++) {
			tempBitValue += (population[index][21 - i] - '0') * pow(2.0, i); // convert bit to its base 2 value
		}
		x = tempBitValue * 3 / (pow(2.0, 22) - 1) - 1.0;

	cout << "Max output after generation 0: " << setprecision(7) << maxOutcome << " at " << x << endl;
	float lastGenMax = maxOutcome;
	int lastGenX = x;
	float lastGenInc = lastGenMax;
	//***********End First Generation******************

	//cout << "start crossover, input two strings are: " << endl;
	//printString(population[0]);
	//printString(population[1]);
	//crossOver(population[0], population[1]);

	//cout << "after crossover, strings in population: " << endl;
	//printString(population[0]);
	//printString(population[1]);

	// *********Start Offspring Generations*****************
	int genCounter = 0;
	
	do {   
		genCounter++;
		lastGenInc = maxOutcome - lastGenMax;
		lastGenMax = maxOutcome;
		lastGenX = x;
		for (int i = 0; i < POPUSIZE; i++) {                 // apply crossovers
			crossOver(population[i % POPUSIZE], population[(i+genCounter) % POPUSIZE]);
		}
		mutation();                                               // apply mutation
		for (int i = 0; i < POPUSIZE; i++) {
			if (fitnessFunc(population[i]) > maxOutcome) {
				maxOutcome = fitnessFunc(population[i]);
				index = i;
			}
		}
		
		double tempBitValue = 0.0;
		for (int i = 0; i < 22; i++) {
			tempBitValue += (population[index][21 - i] - '0') * pow(2.0, i); // convert bit to its base 2 value
		}
		x = tempBitValue * 3 / (pow(2.0, 22) - 1) - 1.0;

		cout << "Max output after generation " << genCounter << ": " << setprecision(7) << maxOutcome << " at " << x << endl;
	
	} while (((maxOutcome - lastGenMax) > 0.000001 || (lastGenX - x) > 0.1 || (lastGenX - x) < -0.1) && genCounter < 3000); // precision: 6 digits after decimal point
	
	cout << endl;	
	cout << "final output: " << setprecision(7) << maxOutcome << " at " << x << endl;


	return 0;
}
