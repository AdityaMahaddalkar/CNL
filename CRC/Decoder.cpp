#include<bits/stdc++.h>
using namespace std;

class Decoder{

	vector<int> dataword, redundant, codeword;
	vector<int> generator;

public:
	Decoder(){
		// Initialize generator

		generator.push_back(1);
		generator.push_back(1);
		generator.push_back(0);
		generator.push_back(1);
	}

	void printVector(vector<int> v){
		for(int i = 0;i < v.size();i ++){
			cout << v[i] << " ";
		}
	}

	void getCodeword(){
		// Logic to get codeword through network
	}

	void testing(){
		cout << "Enter codeword: ";
		string code_string;
		cin >> code_string;

		int n = code_string.length();
		for(int i = 0;i < n;i ++){
			codeword.push_back(code_string[i] - 48);
		}		
		printVector(codeword);
	}

	void polynomialTesting(){
		cout << "\nEnter the size of the codeword: ";
		int n;
		cin >> n;
		for(int i = 0;i < n;i ++){
			codeword.push_back(0);
		}
		
		//Input all the non-zero coefficients' exponents

		cout << "\nEnter the number of non-zero coefficients: ";
		int no_coeff, temp;
		cin >> no_coeff;
		for(int i = 0;i < no_coeff;i ++){
			cout << "\nEnter exponent " << i << " : ";
			cin >> temp;
			codeword[n-temp-1] = 1;
		}
		printVector(codeword);		

	}

	void checkSignificand(){

		cout << "Received codeword is" << endl;
		printVector(codeword);
		cout << endl; 
		int pointer = 3;
		vector<int> answer, temp_answer;
		//Compute significand

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

		answer.erase(answer.end()-1);

		//Check if significand is zero
		bool flag = true;

		for(int i = 0;i < answer.size();i ++){
			if(answer[i] != 0){
				flag = false;
				break;
			}
		}

		if(flag){
			cout << "Successful transmission" << endl;
			for(int i = 0;i < codeword.size()-3;i ++){
				dataword.push_back(codeword[i]);
			}
			cout << "The received dataword is: ";
			printVector(dataword);
		}
		else{
			cout << "Failure in transmission, dataword rejected" << endl;
		}

	}

};

int main(){
	Decoder dc;
	dc.testing();
	dc.checkSignificand();
}