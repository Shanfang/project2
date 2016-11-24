#include<iostream>
#include<string>
#include<string.h>//for strcpy()
using namespace std;

//find the occurence of substring(hint) in a string
int occurrence(string* matrix, string hint, int* array, int length) {
	string str;
	int count;
	for(int i = 0; i < length; i++) {	
		count = 0;
		str = matrix[i];		
		size_t start = str.find(hint);
		while(start != string::npos) {
			count++;
			start = str.find(hint, start + 1);
		}
		array[i] = count;
		//cout << "Number of hint is: " << count << endl;
	}
}

//transpose the string array.First, convert to char matrix; Second, transpose matrix; Then, convert to string array;
string* transpose(string* source) {
	int M = source[0].length();
	char** charSource = new char*[M];
	for(int i  = 0; i < M; i++) {
		charSource[i] = new char[M+1];
		strcpy(charSource[i], source[i].c_str());
		for(int j = 0; j < M; j++) {
			//cout << "In the charSource array: i:" << i << "  j:" << j << "  value:" << charSource[i][j] << endl;
		}
	}
	
	//transpose charSource matrix
	char** transDest = new char*[M];
	for(int i = 0; i < M; i++) {
		transDest[i] = new char[M];
		for(int j = 0; j < M; j++) {
			transDest[i][j] = charSource[j][i];
			//cout << "row: " << j << "  column: " << i << " value: "<<transDest[i][j] << endl;
		}
	}
	
	//convert 2D char array into string array
	string* destination = new string[M];
	for(int i = 0; i < M; i++) {
		destination[i] = string(transDest[i]);
	}
	return destination;
}


int main() {
	int N;
	cin >> N;
	string hint;
	cin >> hint;

	string* matrix = new string[N];
	for(int i = 0; i < N; i++) {
		//getline(cin, matrix[i]);
		cin >> matrix[i];
	}
	
	//find the occurence of hint in a each row/column and store value in respective array
	int* row = new int[N];
	int* col = new int[N];
	occurrence(matrix, hint, row, N);	
	string* matrix2 = transpose(matrix);
	occurrence(matrix2, hint, col, N);	
	
	
	
	
	//free allocated memory for arrays
	/*delete matrix[];
	delete matrix2[];
	delete row[];
	delete col[];	
	for(int i = 0; i < N; i++) {
		delete charMatrix[i];
	}
	for(int i = 0; i < N+1; i++) {
		delete transMatrix[i];
	}*/
	return 0;
}