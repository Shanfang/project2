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

int max(int a, int b) {
	return (a > b)? a:b;
}
//iterative version of finding the longest common sequence of two arrays
void LCS( int* row, int* col, int m, int n) {
   int L[m+1][n+1];
 
   //building L[m+1][n+1] in bottom up fashion; L[i][j] contains length of LCS of row[0..i-1] and col[0..j-1]
   for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
		   if (i == 0 || j == 0){
				L[i][j] = 0;  
		   }
		   else if (row[i-1] == col[j-1]) {
				L[i][j] = L[i-1][j-1] + 1;   
		   }
		   else {
			 L[i][j] = max(L[i-1][j], L[i][j-1]);
			}
		}
	}
	
	//do the backtracking and print out the longest common sequence in row and col array
	int length = L[m][n];
	int lcs[length];
	int i = m;
	int j = n;
	while(i > 0 && j >0) {
		if(row[i-1] == col[j-1]) {
			lcs[length-1] = row[i-1];
			i--;
			j--;
			length--;
		}
		else if(L[i][j-1] > L[i-1][j]) {
			j--;
		}
		else {
			i--;
		}
	}
	
	//print out lcs
	for(int k = 0; k < L[m][n]; k++) {
		cout << lcs[k];
	}
	cout << endl;
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
	
	//the combination with max length is the longest common sequence of the row and col arrays
	LCS(row, col, N, N);
	
	
	//free allocated memory for arrays
	delete[] matrix;
	delete[] matrix2;
	delete[] row;
	delete[] col;	
	return 0;
}