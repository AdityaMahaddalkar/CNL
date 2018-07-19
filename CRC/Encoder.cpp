#include <bits/stdc++.h>
using namespace std;
#define PORT 8080


class Encoder{
	vector<int> dataword, redundant, codeword;
	vector<int> generator;
	int n, k, r;

public:
	Encoder(){
		// Assume encoder = 1101
		generator.push_back(1);
		generator.push_back(1);
		generator.push_back(0);
		generator.push_back(1);

		//Size of redundant = | generator | - 1
		r = 3;
	}

	void printVector(vector<int> v){
		for(int i = 0;i < v.size();i ++){
			cout << v[i] << " ";
		}
	}

	void alterBit(){
		cout << "Enter a bit to be altered: " << endl;
		int alter_bit;
		cin >> alter_bit;

		try{
			codeword[alter_bit] = codeword[alter_bit] == 1? 0:1;
			cout << "After altering:" << endl;
			printVector(codeword);
		}
		catch(...){
			cout << "Error" << endl;
		}
	}

	void getData(){
		cout << "\nEnter the size of dataword: ";
		cin >> k;
		int temp;
		cout << "\nEnter the bits of dataword: ";
		for(int _ = 0;_ < k;_++){
			cin >> temp;
			dataword.push_back(temp);
		}

		// Size of codeword = dataword + redundant
		n = k + r;

		//Inititalize codeword by appending zeros to the end
		for(int _ = 0; _ < this->k; _ ++){
			codeword.push_back(dataword[_]);
		}
		for(int _ = 0;_ < this->r; _ ++){
			codeword.push_back(0);
		}

	}

	void polynomialInput(){
		cout << "Enter size of dataword: ";
		cin >> k;

		// Initialize all bits by zero
		for(int _ = 0;_ < k;_ ++){
			dataword.push_back(0);
		}

		// Enter exponents of polynomial whose bits are 1
		cout << "\nEnter number of non-zero terms: ";
		int non_zero;
		int exponent;
		cin >> non_zero;
		try{
			for(int i = 0;i < non_zero;i ++){
				cout << "\nEnter term " << i << " : ";
				cin >> exponent;
				dataword[exponent] = 1;
			}
		}
		catch(...){
			cout << "\nError";
			exit(1);
		}

		//Inititalize codeword by appending zeros to the end
		for(int _ = 0; _ < this->k; _ ++){
			codeword.push_back(dataword[_]);
		}
		for(int _ = 0;_ < this->r; _ ++){
			codeword.push_back(0);
		}
	}


	void computeCodeword(){
		vector<int> answer, temp_answer;
		int pointer = 3;
		
		cout << "Initital codeword is" << endl;
		printVector(codeword);
		cout << endl; 

		while(pointer < codeword.size()){
			//Check the first bit of answer
			// if it is 1, then xor with generator
			// else xor with 0000

			int first_bit;
			if(answer.size() == 0){
				first_bit = 1;
				for(int _ = 0;_ < 4;_ ++){
					answer.push_back(codeword[_]);
				}
			}
			else{
				first_bit = answer[0];
			}

			//Compute the temporary answer

			if(first_bit == 1){
				for(int i = 0;i <= 3;i ++){
					temp_answer.push_back(answer[i] ^ generator[i]);
				}
			}
			else{
				for(int i = 0;i <= 3;i ++){
					temp_answer.push_back(answer[i] ^ 0);
				}
			}

			//Remove first bit from temp answer and assign answer to temp answer
			answer.clear();
			temp_answer.erase(temp_answer.begin());
			answer = temp_answer;
			
			//Assign pointer + 1 bit to end of answer

			answer.push_back(codeword[pointer+1]);

			pointer += 1;

			// Clear the temp answer
			temp_answer.clear();
			cout << "At iter " << pointer << " answer is";
			printVector(answer);
			cout << endl;
		}

		//Assign the redundant bit
		answer.erase(answer.end()-1);
		redundant = answer;

		//Create a new codeword
		codeword.clear();

		for(int _ =0;_ < k;_ ++){
			codeword.push_back(dataword[_]);
		}

		for(int _ = 0;_ < r; _ ++){
			codeword.push_back(redundant[_]);
		}

		cout << "Final codeword is" << endl;
		printVector(codeword);
		cout << endl;

	}

	void sendCodeWord(){
		//Logic to send codeword over the network

		//Create socket

		int sockfd = socket(AF_NET, SOCK_STREAM, 0);
	}
};

int main(){
	Encoder ec;
	ec.getData();
	ec.computeCodeword();
}
