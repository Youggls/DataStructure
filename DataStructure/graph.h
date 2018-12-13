#pragma once
#ifndef VECTOR
#define VECTOR
#include <vector>
using std::vector;
#endif // !vector

namespace dataStructure {
	class edge {
	private:
		int u;
		int v;
		int len;
	public:
		edge(int n1, int n2, int l) { u = n1; v = n2; len = l; };
		edge(const edge& e) { u = e.u; v = e.v; len = e.len; };
		edge() { u = -1; v = -1; len = INT_MAX; };
		int& getU() { return u; };
		int& getV() { return v; };
		int& getlen() { return len; };
	};
}