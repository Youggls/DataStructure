#pragma once
#include <istream>
#include <ostream>

namespace dataStructure {
	template <class T>
	class sparseMatrix {
	private:
		template <class T>
		class term {
		public:
			term() { col = -1; row = -1; };
			int col;
			int row;
			T dat;
		};
		int colNum;
		int rowNum;
		int terms;
		int maxTerms;
		term<T>* data;
	public:
		sparseMatrix(int c, int r, int max);
		//		sparseMatrix();
		int size() { return terms; }
		int capacity() { return maxTerms; }
		void transpose(sparseMatrix<T>& s);
		//		void add(const sparseMatrix<T>& another);

		friend istream& operator>>(istream& in, sparseMatrix<T>& s) {
			in >> s.rowNum >> s.colNum >> s.maxTerms;
			for (int i = 0; i < s.maxTerms; i++) {
				in >> s.data[i].row >> s.data[i].col >> s.data[i].dat;
			}
			s.terms = s.maxTerms;
			return in;
		}
		friend ostream& operator<<(ostream& out, const sparseMatrix<T>& s) {
			for (int i = 0; i < s.terms; i++) {
				out << s.data[i].col << ' ' << s.data[i].row << ' ' << s.data[i].dat;
				if (i != s.terms - 1) out << endl;
			}

			return out;
		}
	};

	template <class T>
	sparseMatrix<T>::sparseMatrix(int c, int r, int max) {
		colNum = c;
		rowNum = r;
		maxTerms = max;
		terms = 0;
		data = new term<T>[max];
	}


	template <class T>
	void sparseMatrix<T>::transpose(sparseMatrix<T>& s) {
		s.colNum = rowNum;
		s.rowNum = colNum;
		s.terms = terms;
		s.maxTerms = terms;

		int* colSize;
		int* rowNext;
		colSize = new int[colNum + 1];
		rowNext = new int[colNum + 1];

		for (int i = 1; i <= colNum; i++) {
			colSize[i] = 0;
		}
		for (int i = 0; i < terms; i++) {
			colSize[data[i].col]++;
		}

		rowNext[1] = 0;
		for (int i = 2; i <= colNum; i++) {
			rowNext[i] = rowNext[i - 1] + colSize[i - 1];
		}

		for (int i = 0; i < terms; i++) {
			int j = rowNext[data[i].col]++;
			s.data[j].row = data[i].col;
			s.data[j].col = data[i].row;
			s.data[j].dat = data[i].dat;
		}
	}
}