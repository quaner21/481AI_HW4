#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <time.h> 

using namespace std;

// Define some constants/parameter settings
const double PI = 3.141593;
const double XOVER = 0.8;
const double MUTATION = 0.02;
const int POPUSIZE = 500;

struct PopulationMember{
	char* bitString;
	double fitness;
};

// Global Variable
vector<PopulationMember> population; 

void Sort(vector<PopulationMember> &pop);   



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

void crossOver(PopulationMember member1, PopulationMember member2) {
	char tempStr1[22];
	char tempStr2[22];
	for (int i = 0; i < 22; i++) {                          // generate two children as copies of parents
		tempStr1[i] = member1.bitString[i];
		tempStr2[i] = member2.bitString[i];
	}
	//cout << "parent strings for crossover: " << endl;
	//printString(&tempStr1[0]);
	//printString(&tempStr2[0]);

	int rateC = rand() % 100;
	//cout << "crossover rate: " << rateC << endl;
	if (rateC < XOVER*100) {                                         // 80% chance to crossover
		int numBits = rand() % 11 + 1;
		//cout << "number of bits to crossover: " << numBits << endl;
		int xoverPnt = rand() % (23 - numBits);
		//cout << "crossover occurs at bit " << xoverPnt << endl;

		for (int i = 0; i < numBits; i++) {                 // swap components in the two strings to create children
			tempStr1[xoverPnt + i] = member2.bitString[xoverPnt + i];
			tempStr2[xoverPnt + i] = member1.bitString[xoverPnt + i];
		}

		PopulationMember child1,child2;
		child1.bitString = &tempStr1[0];
		child1.fitness = fitnessFunc(tempStr1);
		population.push_back(child1);

		child2.bitString = &tempStr2[0];
		child2.fitness = fitnessFunc(tempStr2);
		population.push_back(child2);


		cout << tempStr1 << " | " << tempStr2 << endl;
		Sort(population);
		
		
		//cout << "after crossover, children strings: " << endl;
		//printString(&tempStr1[0]);
		//printString(&tempStr2[0]);



		// if (fitVtempStr1 < fitVStr1 && fitVtempStr1 < fitVStr2 // if both children worse, do nothing
		// 	&& fitVtempStr2 < fitVStr1 && fitVtempStr2 < fitnessFunc(string2)) {
		// }
		// else if (fitVtempStr1 > fitVStr1 && fitVtempStr1 > fitVStr2 // if both children better, replace
		// 	&& fitVtempStr2 > fitVStr1 && fitVtempStr2 > fitVStr2) {
		// 	for (int i = 0; i < 22; i++) {                          
		// 		string1[i] = tempStr1[i];
		// 		string2[i] = tempStr2[i];
		// 	}
		// }
		// else if (fitVStr1 > fitVStr2 && fitVtempStr1 > fitVtempStr2) {
		// 	for (int i = 0; i < 22; i++) {
		// 		string2[i] = tempStr1[i];
		// 	}
		// }
		// else if (fitVStr2 > fitVStr1 && fitVtempStr1 > fitVtempStr2) {
		// 	for (int i = 0; i < 22; i++) {
		// 		string1[i] = tempStr1[i];
		// 	}
		// }
		// else if (fitVStr1 > fitVStr2 && fitVtempStr2 > fitVtempStr1) {
		// 	for (int i = 0; i < 22; i++) {
		// 		string2[i] = tempStr2[i];
		// 	}
		// }
		// else if (fitVStr2 > fitVStr1 && fitVtempStr2 > fitVtempStr1) {
		// 	for (int i = 0; i < 22; i++) {
		// 		string1[i] = tempStr2[i];
		// 	}
		// }
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
				if (population[i].bitString[j] == '0'){        // flip the bit
					population[i].bitString[j]++;
				}
				else {
					population[i].bitString[j]--;
				}  
			}
		}
	}
}

void Sort(vector<PopulationMember> &pop)
{
	for ( int i = 0; i < pop.size(); i++)
	{
		for ( int j = i; j < pop.size()-1; j++)
		{
			if (pop[i].fitness < pop[j].fitness)
			{
				PopulationMember temp;// = new PopulationMember();
				temp = pop[i];
				pop[i] = pop[j];
				pop[j] = temp;
			}
		}
	}
}

int main() {
	srand(time(NULL));

	
	// **************First Generation************
	for (int j = 0; j < POPUSIZE; j++) {                    
		char* temp;
		temp = new char[22];
		PopulationMember member;
		for (int i = 0; i < 22; i++) {                       // randomly generate bitstrings representing x
			temp[i] = '0' + rand() % 2;
			//cout << temp[i];
		}
		//cout << endl;
		//cout << fitnessFunc(temp) << endl;
		member.bitString = temp;
		member.fitness = fitnessFunc(temp);
		population.push_back(member);
	}
	cout << "population size " << population.size() << endl; 
	Sort(population);

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
	double maxOutcome = fitnessFunc("0000000000000000000000"); // Not sure if it's a good way to initialize
	for (int i = 0; i < POPUSIZE; i++) {
		if (fitnessFunc(population[i].bitString) > maxOutcome) {
			maxOutcome = fitnessFunc(population[i].bitString);
			index = i;
		}
	}
	cout << "Max output after generation 0: " << setprecision(7) << maxOutcome << " at " << index << endl;
	double lastGenMax = maxOutcome;
	int lastGenIndex = index;
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
		lastGenMax = maxOutcome;
		for (int i = 0; i < (POPUSIZE-1); i+=2) {                 // apply crossovers
			crossOver(population[i], population[i+1]);
		}
		//mutation();                                               // apply mutation
		for (int i = 0; i < POPUSIZE; i++) {
			if (population[i].fitness > maxOutcome) {
				maxOutcome = population[i].fitness;
				index = i;
			}
		}
		cout << "Max output after generation " << genCounter << ": " << setprecision(7) << maxOutcome << " at " << index << endl;
	} while (((maxOutcome - lastGenMax) < 0 || (maxOutcome - lastGenMax) > 0.0000001) && genCounter < 3000); // precision: 6 digits after decimal point
	cout << "final output: " << setprecision(6) << maxOutcome << " at " << index << endl;

	//system("pause");
	return 0;
}
