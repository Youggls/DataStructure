#pragma once

namespace dataStructure {
	class sparseMatrix {
	private:
		class term {
		public:
			term(int d, int r, int c) :dat(d), rowIndex(r), colIndex(c) {};
			term() :dat(0), rowIndex(-1), colIndex(-1) {};
			bool operator>(const term& another) {
				if (this->rowIndex > another.rowIndex) return true;
				else if (this->rowIndex == another.rowIndex) {
					return (this->colIndex > another.colIndex);
				}
				else return false;
			}

			bool operator<(const term& another) {
				if (this->rowIndex < another.rowIndex) return true;
				else if (this->rowIndex == another.rowIndex) {
					return (this->colIndex < another.colIndex);
				}
				else return false;
			}
			
			bool operator==(const term& another) {
				return ((another.colIndex == this->colIndex) && (another.rowIndex == this->rowIndex));
			}
			int dat;
			int rowIndex;
			int colIndex;
		};
		vector<term> data;
		int rowNum;
		int colNum;
		int capacitySize;
		int currentTerms;

	public:
		sparseMatrix(int capacity, int rowNum, int colNum);
		sparseMatrix(const sparseMatrix& another) {
			data = another.data;
			rowNum = another.rowNum;
			colNum = another.colNum;
			capacitySize = another.capacitySize;
			currentTerms = another.currentTerms;
		}
		int& at(int i, int j);
		void transpose();
		sparseMatrix multiple(sparseMatrix& another);
		sparseMatrix add(sparseMatrix& another);

		void insert(int d, int r, int c);
		void insert(term& t);
		int size() { return currentTerms; }
		int capacity() { return data.size(); }
	};

	sparseMatrix::sparseMatrix(int capacity, int r, int c) {
		if (capacity == -1) capacity = 1000;

		capacitySize = capacity;
		rowNum = r;
		colNum = c;
		currentTerms = 0;

		data.resize(capacitySize);
	}

	int& sparseMatrix::at(int i, int j) {
		if (i > colNum || j > rowNum) throw "Out of range";
		term tempTerm(0, i, j);
		for (int k = 0; k < currentTerms; k++) {
			if (data[k] == tempTerm) return data[k].dat;
		}
		
		throw "Not found";
	}

	void sparseMatrix::transpose() {
		vector<term> newData(capacitySize);
		vector<int> colSize(colNum + 1, 0);
		vector<int> rowNext(colNum + 1, 0);

		//Caculate every column term size
		for (int i = 0; i < currentTerms; i++) {
			colSize[data[i].colIndex]++;
		}
		//Where the row start at the vector<term> data, at the transpos matrix
		rowNext[1] = 0;
		for (int i = 2; i <= colNum; i++) {
			rowNext[i] = rowNext[i - 1] + colSize[i - 1];
		}

		for (int i = 0; i < currentTerms; i++) {
			int j = rowNext[data[i].colIndex]++;
			newData[j].rowIndex = data[i].colIndex;
			newData[j].colIndex = data[i].rowIndex;
			newData[j].dat = data[i].dat;
		}

		data.clear();
		data = newData;
		int t = colNum;
		colNum = rowNum;
		rowNum = t;
	}

	sparseMatrix sparseMatrix::multiple(sparseMatrix& another) {
		sparseMatrix rev(this->capacity(), this->rowNum, another.colNum);

		//Every row size
		vector<int> rowSize(another.rowNum, 0);
		//The start of the rows int the data
		vector<int> rowPosition(another.rowNum, 0);

		for (int i = 0; i < another.currentTerms; i++) rowSize[data[i].rowIndex]++;
		for (int i = 2; i < another.rowNum + 1; i++) rowPosition[i] = rowPosition[i - 1] + rowSize[i - 1];

		int k = 0;
		for (int i = 1; i <= this->rowNum; i++) {
			vector<int> tempAns(another.colNum + 1, 0);

			int pos = 0;

			while (i == data[k].rowIndex) {
				int tempColIndex = data[k].colIndex;

				if (tempColIndex < another.rowNum) pos = rowPosition[tempColIndex + 1];
				else pos = another.currentTerms;

				for (int j = rowPosition[tempColIndex]; j < pos; j++) {
					tempAns[another.data[j].colIndex] += data[k].dat * another.data[j].dat;
				}
				k++;
			}

			for (int j = 1; j < another.colNum + 1; j++) {
				if (tempAns[j]) {
					rev.insert(tempAns[j], i, j);
				}
			}
		}

		return rev;
	}

	sparseMatrix sparseMatrix::add(sparseMatrix& another) {
		if (rowNum != another.rowNum || colNum != another.colNum) throw "Input wrong";
		sparseMatrix rev(this->size() + another.size(), rowNum, colNum);

		int currentThisIndex = 0;
		int currentAnotherIndex = 0;
		int revCurrentIndex = 0;

		while (currentThisIndex < currentTerms && currentAnotherIndex < another.currentTerms) {
			if (data[currentThisIndex] < another.data[currentAnotherIndex]) {
				rev.insert(data[currentThisIndex++]);
			}
			else if (data[currentThisIndex] > another.data[currentAnotherIndex]) {
				rev.insert(another.data[currentAnotherIndex++]);
			}
			else {
				int d = data[currentThisIndex].dat + another.data[currentAnotherIndex].dat;
				int r = data[currentThisIndex++].rowIndex;
				int c = another.data[currentAnotherIndex++].colIndex;
				if (d == 0) continue;
				term newTerm(d, r, c);
				rev.insert(newTerm);
			}
		}

		while (currentThisIndex < currentTerms) {
			rev.insert(data[currentThisIndex++]);
		}
		while (currentAnotherIndex < another.currentTerms) {
			rev.insert(another.data[currentAnotherIndex++]);
		}

		return rev;
	}

	void sparseMatrix::insert(int d, int r, int c) {
		vector<term>::iterator insertPosition = data.begin();
		term newTerm(d, r, c);

		if (currentTerms == 1) {
			if (newTerm < data[0]) 
				data.insert(insertPosition, newTerm);
			else if (newTerm > data[0]) 
				data.insert(insertPosition + 1, newTerm);
			currentTerms++;
			return;
		}

		for (int i = 0; i < currentTerms - 1; i++) {
			if (data[i] < newTerm && data[i + 1] > newTerm) {
				insertPosition += i + 1;
				break;
			}
			if (i == 0 && newTerm < data[0]) 
				break;
			else if (i == currentTerms - 2 && data[i + 1] < newTerm) {
				insertPosition += currentTerms;
			}
		}

		data.insert(insertPosition, newTerm);
		currentTerms++;
	}

	void sparseMatrix::insert(term& t) {
		vector<term>::iterator insertPosition = data.begin();

		if (currentTerms == 1) {
			if (t < data[0])
				data.insert(insertPosition, t);
			else if (t > data[0])
				data.insert(insertPosition + 1, t);
			currentTerms++;
			return;
		}

		for (int i = 0; i < currentTerms - 1; i++) {
			if (data[i] < t && data[i + 1] > t) {
				insertPosition += i + 1;
				break;
			}
			if (i == 0 && t < data[0])
				break;
			else if (i == currentTerms - 2 && data[i + 1] < t) {
				insertPosition += currentTerms;
			}
		}

		data.insert(insertPosition, t);
		currentTerms++;
	}
}