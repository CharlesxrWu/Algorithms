# Graph

图论能解决计算机科学很多问题。

图的分类：无向图和有向图。其中无向图是一种特殊的有向图。

根据边有没有权值，分为无权图和有权图。

## 图的表示

* 邻接矩阵(二维)：适合表示稠密图
* 邻接表：适合表示稀疏图

**[邻接矩阵的数据结构表示](https://github.com/steveLauwh/Data-Structures-And-Algorithms/blob/master/Graph/DenseGraph/DenseGraph.h)**
```cpp
// 稠密图——用邻接矩阵表示
class DenseGraph {
private:
    int n;
    int m;
    bool directed;
    vector< vector<bool> > g; // 邻接矩阵的值用 0 和 1 表示

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
```

**[邻接表的数据结构表示](https://github.com/steveLauwh/Data-Structures-And-Algorithms/blob/master/Graph/SparseGraph/SparseGraph.h)**
```cpp
// 稀疏图——用邻接表表示
class SparseGraph {
private:
    int n;  // 图的顶点
    int m;  // 图的边
    bool directed; // 方向
    vector< vector<int> > g;  // 邻接表的特点，还可以用链表表示

public:
    SparseGraph(int n, bool directed) {
        this->n = n;
        this->m = 0;
        this->directed = directed;

        for (int i = 0; i < n; i++) {
            g.push_back(vector<int>()); // 初始每行都为空
        }
    }

    ~SparseGraph() {

    }

    int V() {
        return n;  // 顶点数
    }

    int E() {
        return m;  // 边数
    }

    void addEdge(int v, int w) {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        g[v].push_back(w);

        if (v != w && !directed) {  // 无向图
            g[w].push_back(v);
        }

        m++;
    }

    bool hasEdge(int v, int w) {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        for (unsigned int i = 0; i < g[v].size(); i++) {
            if (g[v][i] == w)
                return true;
        }

        return false;
    }
};
```

## 遍历邻边——迭代器

迭代器三种操作：begin()，next()，end()。

**稠密图——邻接矩阵的迭代器**

对于邻接矩阵而言，每个顶点(行)，对应的邻边(各列)，用 true 和 false 表示是否有该邻边。begin()，next() 是返回邻边的值，该值其实就是列索引的值。

```cpp
class denseGraphIterator {
private:
    DenseGraph &G;
    int v;
    int index;

public:
    denseGraphIterator(DenseGraph &graph, int v) : G(graph) {
        this->v = v;
        this->index = -1;
    }

    int begin() {
        index = -1;
        return next();
    }

    int next() {
        for (index += 1; index < G.V(); index++) {
            if (G.g[v][index]) {
                return index;    // 返回节点的值
            }
        }

        return -1;
    }

    int end() {
        return index >= G.V();
    }
};
```

**稀疏图——邻接表的迭代器**

对于邻接表而言，每个顶点(行)，对应的邻边(各列)，各列对应的值就是邻边的值。

```cpp
// 遍历邻边——迭代器
class sparseGraphIterator {
private:
    SparseGraph &G;
    int v;
    unsigned int index;

public:
    sparseGraphIterator(SparseGraph &graph, int v) : G(graph) {
        this->v = v;
        this->index = 0;
    }

    int begin() {
        index = 0;
        if (G.g[v].size()) {
            return G.g[v][index];
        }

        return -1;
    }

    int next() {
        index++;
        if (index < G.g[v].size()) {
            return G.g[v][index];
        }

        return -1;
    }

    bool end() {
        return index >= G.g[v].size();
    }
};
```

## [图的读取](https://github.com/steveLauwh/Data-Structures-And-Algorithms/tree/master/Graph/ReadGraph)

图是以文件的方式表示，读取一个图的信息。

```cpp
template <typename Graph>
class ReadGraph {
public:
    ReadGraph(Graph &graph, const string &filename) {
        ifstream file(filename);
	string line;
	int V, E;

	assert(file.is_open());

	assert(getline(file, line));
	stringstream ss(line);
	ss >> V >> E;

	assert(V == graph.V());

	for (int i = 0; i < E; i++) {
	    assert(getline(file, line));
	    stringstream ss(line);
	    
	    int a, b;
	    ss >> a >> b;
	    assert(a >= 0 && a < V);
	    assert(b >= 0 && b < V);

	    graph.addEdge(a, b);
	}
    }
};
```

## 图的遍历 

### 深度优先遍历(DFS)

需要用数组记录每个顶点是否遍历，遍历为 true。

稀疏图(邻接表)的时间复杂度： O( V + E )

稠密图(邻接矩阵)的时间复杂度：O( V^2 )

深度优先遍历算法：使用相邻边迭代器，递归遍历。

```cpp
// 图的深度优先遍历
void dfs(int v) {
    visited[v] = true;

    typename Graph::adjIterator ite(g, v);  // Graph 模板，稠密图和稀疏图

    for (int i = ite.begin(); !ite.end(); i = ite.next()) {
	if (!visited[i]) {
	    dfs(i);
	}
    }
}
```

### 广度优先遍历(BFS)

## 图的应用

### [求图的连通分量](https://github.com/steveLauwh/Data-Structures-And-Algorithms/tree/master/Graph/Component)

通过 DFS 可以计算图的连通分量。

```cpp
// 求无权图的联通分量
template <typename Graph>
class Component {
private:
    Graph &g;
    bool *visited;  // 记录 DFS 过程中顶点是否被遍历
    unsigned int counts;   // 记录联通分量的个数
    int *id;    // 每个顶点所对应的联通分量标记

    // 图的深度优先遍历
    void dfs(int v) {
    	visited[v] = true;
	id[v] = counts;

	typename Graph::adjIterator adj(g, v);

	for (int i = adj.begin(); !adj.end(); i = adj.next()) {
	    if (!visited[i]) {
		dfs(i);
	    }
	}
    }

public:
    // 构造函数，求出无权图的联通分量
    Component(Graph &graph) : g(graph) {
    	visited = new bool[g.V()];
	id = new int[g.V()];
	counts = 0;

	for (int i = 0; i < g.V(); i++) {
	    visited[i] = false;
            id[i] = -1;
	}

	// 图的联通分量
	for (int i = 0; i < g.V(); i++) {
	    if (!visited[i]) {
		dfs(i);
		counts++;
	    }
	}
    }

    ~Component() {
    	delete[] visited;
	delete[] id;
    }
    
    int count() {
	return counts;
    }

    // 查询顶点 v 和顶点 w 是否联通
    bool isConnected(int v, int w) {
	assert(v >= 0 && w < g.V());
	assert(w >= 0 && w < g.V());

	return id[v] == id[w];
    }
};
```

### [求图中任意两点之间的路径](https://github.com/steveLauwh/Data-Structures-And-Algorithms/edit/master/Graph/FindPath/FindPath.h)

通过 DFS 可以求图中任意两点之间的路径。

```cpp
template <typename Graph>
class FindPath {
private:
    Graph &g;
    bool *visited;  // 记录 DFS 过程中的节点是否被访问
    int source;  // 寻路的起始点
    int *from;   //  from[i] 表示查找的路径上 i 的上一个节点
    
    // 图的深度优先遍历
    void dfs(int v) {
        visited[v] = true;
        
        typename Graph::adjIterator adj(g, v);
        for( int i = adj.begin() ; !adj.end() ; i = adj.next() ) {
            if ( !visited[i] ) {
                from[i] = v;  // 记录
                dfs(i);
            }
        }
    }
    
public:
    FindPath(Graph &graph, int s) : g(graph) {
        assert(s >= 0 && s < g.V());
        
        visited = new bool[g.V()];
        from = new int[g.V()];
        
        for (int i = 0; i < g.V(); i++) {
            visited[i] = false;
            from[i] = -1;
        }
        
        this->source = s;
        
        // 寻路
        dfs(s);
    }
    
    ~FindPath() {
        delete[] visited;
        delete[] from;
    }
    
    // 查询从 s 到 t 是否有路径
    bool hasPath(int t) {
        assert(t>= 0 && t < g.V());
        
        return visited[t];
    }
    
    // 查询 s 到 t 的路径，存放在 vector 中
    void path(int t, vector<int> &v) {
        assert(hasPath(t));
        
        stack<int> s;
        
        // 通过 from 数组逆向查找到从 s 到 t 的路径, 存放到栈中
        while (t != -1) { // 源点 s 的 from[s] 是 -1
            s.push(t);
            t = from[t];
        }
        
        // 从栈中取出，顺序的从 s 到 t 的路径，存放到 vector 中
        v.clear();
        
        while (!s.empty()) {
            v.push_back(s.top());   
            s.pop();  
        }
    }
    
    // 打印出从 s 点到 t 点的路径
    void showPath(int t) {
        assert(hasPath(t));
        
        vector<int> vec;
        
        path(t, vec);
        
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i];
            
            if (i == vec.size() - 1) {
                cout << endl;
            }
            else {
                cout << " -> ";
            }
        }
    }
};
```
