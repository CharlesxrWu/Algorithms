#ifndef DENSEGRAPH_H
#define DENSEGRAPH_H

#include <vector>
#include <iostream>
#inclue <cassert>

using namespace std;

// 稠密图——用邻接矩阵表示
class DenseGraph {
private:
    int n;
    int m;
    bool directed;
    vector<vector<bool>> g; // 邻接矩阵的值用 0 和 1 表示

public:
    DenseGraph(int n, bool directed) {
        this->n = n;
        this->m = 0;
        this->directed = directed;
        
        for (int i = 0; i < n; i++) {
            g.push_back(vector<bool>(n, false));  // 矩阵初始都为 false
        }
    }
    
    ~DenseGraph() {
    
    }
    
    int V() {
        return n;
    }
    
    int E() {
        return m;
    }
    
    void addEdge(int v, int w) {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        
        if (hasEdge(v, w)) {
            return;
        }
        
        g[v][w] = true;
        
        if (!directed) {
            g[w][v] = true;  // 无向图
        }
        
        m++;
    }
    
    bool hasEdge(int v, int w) {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        
        return g[v][w];
    }
    
};

#endif
