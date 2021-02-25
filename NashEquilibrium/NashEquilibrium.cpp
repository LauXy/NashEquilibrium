#include<iostream>
#include<string>
#include<set>
#include<istream>
using namespace std;

// Developed by Liu Xueyuan @SJTU, student id: 020033910001

class NashEqu {
private:
	pair<int, int> payoffMat[2][2];
	pair<int, int> curPair, lastpair, initPair;
	void FindSingleNashEqu(int startA, int startB, set<pair<int, int>>& solutions, bool& isloop);
public:
	NashEqu() {}
	NashEqu(pair<int, int>** Mat) {
		payoffMat[0][0] = Mat[0][0], payoffMat[0][1] = Mat[0][1];
		payoffMat[1][0] = Mat[1][0], payoffMat[1][1] = Mat[1][1];
		lastpair.first = lastpair.second = INT_MIN;
	}
	void InputPayOffMat();
	void FindAllNashEqu();
};

void NashEqu::InputPayOffMat() {
	for (int i = 0; i < 4; ++i) {
		bool flag = false; 
		for (int j = 0; j < 2; ++j, flag = !flag) {
			int elem;
			cin >> elem;
			if (!flag) payoffMat[i/2][i%2].first = elem;
			else payoffMat[i/2][i%2].second = elem;
		}
	}
	lastpair.first = lastpair.second = INT_MIN;
}

void NashEqu::FindSingleNashEqu(int startA, int startB, set<pair<int, int>>& solutions, bool& isloop) {
	bool ownlab = true; // Player A: false; Player B: true
	int row = startA, col = 0;
	int loopCnt = 0;
	initPair = curPair = payoffMat[startA][startB];
	//cout << "start with (" << startA << ", " << startB << ")\n";
	while (curPair != lastpair) {
		lastpair = curPair;
		if (!ownlab) {
			if (payoffMat[0][col].first >= payoffMat[1][col].first) {
				curPair = payoffMat[0][col];
				row = 0;
			}
			else {
				curPair = payoffMat[1][col];
				row = 1;
			}
		}
		else {
			if (payoffMat[row][0].second >= payoffMat[row][1].second) {
				curPair = payoffMat[row][0];
				col = 0;
			}
			else {
				curPair = payoffMat[row][1];
				col = 1;
			}
		}
		//cout << "curPair: (" << curPair.first << ", " << curPair.second << ")" << endl;
		ownlab = !ownlab;
		loopCnt += 1;
		if (loopCnt == 4 && curPair == initPair) {
			cout << "None Nash Equilibrium exist!" << endl;
			isloop = true;
			break;
		}
	}
	if (curPair == lastpair) {
		solutions.insert(curPair);
	}
}

void NashEqu::FindAllNashEqu() {
	bool isloop = false;
	set<pair<int, int>> solutions;
	FindSingleNashEqu(0, 0, solutions, isloop);
	if (!isloop) {
		FindSingleNashEqu(1, 0, solutions, isloop);
		for (set<pair<int, int>>::iterator it = solutions.begin(); it != solutions.end(); ++it) {
			cout << "(" << it->first << ", " << it->second << "), ";
		}
		cout << "\b\b is Nash Equilibrium." << endl;
	}
}

int main() {
	NashEqu ne;
	ne.InputPayOffMat();
	ne.FindAllNashEqu();
	return 0;
}