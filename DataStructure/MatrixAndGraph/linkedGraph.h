#pragma once

#include "AdjMatrixGraph.h"

namespace dataStructure {
	class linkedGraph {
	private:
		class linkedGraphChain {
		public:
			int w;
			int v;
			linkedGraphChain* nxt;
			linkedGraphChain() { v = -1; w = INT_MAX; nxt = NULL; }
			linkedGraphChain(int vv, int ww) { v = vv; w = ww; nxt = NULL; }
			int indexOf(int j) {
				linkedGraphChain* t = nxt;
				int k = 0;
				while (t) {
					if (t->v == j) return k;
					t = t->nxt;
					k++;
				}
				return -1;
			}

			linkedGraphChain* find(int j) {
				linkedGraphChain* t = nxt;
				while (t) {
					if (t->v == j) return t;
					t = t->nxt;
				}

				return NULL;
			}

			void insert(linkedGraphChain* newEdge, int pos = 0) {
				if (pos == 0) {
					newEdge->nxt = nxt;
					nxt = newEdge;
				}

				linkedGraphChain* t = this;
				int k = 0;
				while (k < pos) {
					t = t->nxt;
					k++;
				}
				newEdge->nxt = t->nxt->nxt;
				t->nxt = newEdge;
			}

			void erase(int pos) {

			}
		};

		linkedGraphChain* aList;
		int v;
		int e;

	public:
		linkedGraph(int v = 0);
		bool existEdge(int i, int j);
		bool existEdge(const dataStructure::edge& ed);
		void insertEdge(int i, int j, int w = 1);
		void insertEdge(const dataStructure::edge& ed);

		void eraseEdge(int i, int j);
		void eraseEdge(const dataStructure::edge& ed);

		dataStructure::edge* getAllEdge();
	};

	linkedGraph::linkedGraph(int vv) {
		aList = new linkedGraphChain[vv + 1];
		v = vv;
		e = 0;
	}

	bool linkedGraph::existEdge(int i, int j) {
		if (i < 1 || j < 1 || i > v || j > v || aList[i].indexOf(j) == -1) return false;
		else return true;
	}

	bool linkedGraph::existEdge(const dataStructure::edge& ed) {
		return existEdge(ed.i, ed.j);
	}

	void linkedGraph::insertEdge(int i, int j, int w = 1) {
		linkedGraphChain* t = aList[i].find(j);
		if (t == NULL) {
			linkedGraphChain* newEdge = new linkedGraphChain(j, w);
			aList[i].insert(newEdge);
			return;
		}
		else return;
	}

	void linkedGraph::insertEdge(const dataStructure::edge& ed) {
		insertEdge(ed.i, ed.j, ed.w);
	}

	void linkedGraph::eraseEdge(int i, int j) {
		linkedGraphChain* t = aList[i].find(j);
		if (t != NULL) {

		}
	}
}