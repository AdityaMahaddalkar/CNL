#include <bits/stdc++.h>
using namespace std;

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

	void getData(){
		cout << "\nEnter the size of dataword: ";
		cin >> k;
		int temp;
		cout << "\nEnter the bits of dataword: ";
		for(int _ = 0;_ < k;_++){
			cin >> temp;
			try{
				if(temp != 0 || temp != 1){
					throw "Error";
				}
				dataword.push_back(temp);
			}
			catch(...){
				cout << "\nDataword invalid";
				exit(1);
			}
		}

		// Size of codeword = dataword + redundant
		n = k + r;

		//Inititalize codeword by appending zeros to the end
		for(int _ = 0; _ < this.k; _ ++){
			codeword.push_back(dataword[_]);
		}
		for(int _ = 0;_ < this.r; _ ++){
			codeword.push_back(0);
		}

	}

	void computeCodeword(){
		vector<int> answer, temp_answer;
		int pointer = 3;
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
				for(int i = pointer-3;i <= pointer;i ++){
					temp_answer.push_back(answer[i] ^ codeword[i])
				}
			}
			else{
				for(int i = pointer-3;i <= pointer;i ++){
					temp_answer.push_back(answer[i] ^ 0)
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
		}

		//Assign the redundant bit
		answer.erase(answer.begin());
		redundant = answer;

		//Create a new codeword
		codeword.clear();

		for(int _ =0;_ < k;_ ++){
			codeword.push_back(dataword[_]);
		}

		for(int _ = 0;_ < r; _ ++){
			codeword.push_back(redundant[_]);
		}
	}

	void sendCodeWord(){
		
	}
};

int main(){
	
}