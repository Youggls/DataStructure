#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::stack;

stack<int>* track;
int numberOfCarts;
int numberOfTracks;
int smallestCar;
int itsTrack;

void outputFromHoldingTrack() {
	track[itsTrack].pop();
	cout << "Move car" << smallestCar << " from holding "
		<< "track " << itsTrack << " to  output track" << endl;

	smallestCar = numberOfCarts + 2;
	for (int i = 1; i <= numberOfTracks; i++) {
		if (!track[i].empty() && (track[i].top() < smallestCar)) {
			smallestCar = track[i].top();
			itsTrack = i;
		}
	}
}

bool putInHoldingTrack(int c) {
	int bestTrack = 0;
	int bestTop = numberOfCarts + 1;

	for (int i = 1; i <= numberOfTracks; i++) {
		if (!track[i].empty()) {
			int topCar = track[i].top();
			if (c < topCar && topCar < bestTop) {
				bestTop = topCar;
				bestTrack = i;
			}
		}
		else if (bestTrack == 0) {
			bestTrack = 1;
		}
	}

	if (bestTrack == 0) return false;

	track[bestTrack].push(c);
	cout << "Move car" << c << " from input track "
		<< "to holding track" << bestTrack << endl;

	if (c < smallestCar) {
		smallestCar = c;
		itsTrack = bestTrack;
	}

	return true;
}

bool railRoad(int inputOrder[], int theNumberOfCarts, int theNumberOfTracks) {
	numberOfCarts = theNumberOfCarts;
	numberOfTracks = theNumberOfTracks;

	track = new stack<int>[numberOfTracks + 1];

	int nextCarToOutPut = 1;
	smallestCar = numberOfCarts + 1;
	for (int i = 1; i <= numberOfCarts; i++) {
		if (inputOrder[i] == nextCarToOutPut) {
			cout << "Move car" << inputOrder[i]
				<< " from input track to output track" << endl;
			nextCarToOutPut++;

			while (smallestCar == nextCarToOutPut) {
				outputFromHoldingTrack();
				nextCarToOutPut++;
			}
		}
		else {
			if (!putInHoldingTrack(inputOrder[i])) {
				return false;
			}
		}
	}

	return true;
}

//int main() {
//	int* arr = new int[10];
//	for (int i = 0; i < 9; i++) {
//		cin >> arr[i + 1];
//	}
//	railRoad(arr, 9, 3);
//	system("pause");
//	return 0;
//}