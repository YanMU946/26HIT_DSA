#ifndef __MST_H__
#define __MST_H__ 
#include <iostream>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;

const int INF = 0x7FFFFFFF;

struct node {
    int val;
    int near;
    int min_dis;
    int weight;
    bool isVisited;
    node* pnext;
};

struct edge {
    int u, v, weight;
};

class graph {
public:
    graph(int _n)
    {
        vnum = _n;
        base = new node[_n];
        for (int i = 0; i < _n; i++)
        {
            base[i].val = 0;
            base[i].near = -1;
            base[i].min_dis = INF;
            base[i].weight = 0;
            base[i].isVisited = false;
            base[i].pnext = nullptr;
        }
    }

    node* createNode(int _val, int _weight)
    {
        auto new_p = new node;
        new_p->val = _val;
        new_p->near = -1;
        new_p->weight = _weight;
        new_p->isVisited = false;
        new_p->pnext = nullptr;
        return new_p;
    }

    void insert(int _a, int _b, int _weight)
    {
        auto new_pf = createNode(_b, _weight);
        if (base[_a].pnext == nullptr)
            base[_a].pnext = new_pf;
        else
        {
            node* cur = base[_a].pnext;
            while (cur->pnext != nullptr)
                cur = cur->pnext;
            cur->pnext = new_pf;
        }
        auto new_pb = createNode(_a, _weight);
        if (base[_b].pnext == nullptr)
            base[_b].pnext = new_pb;
        else
        {
            node* cur = base[_b].pnext;
            while (cur->pnext != nullptr)
                cur = cur->pnext;
            cur->pnext = new_pb;
        }
    }

    void Prim(int _start)
    {
        base[_start].min_dis = 0;
        // <weight,val>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push(make_pair(0, _start));
        while (!q.empty())
        {
            int top_val = q.top().second;
            q.pop();
            node* cur = base[top_val].pnext;
            if (base[top_val].isVisited) continue;
            while (cur != nullptr)
            {
                if (cur->weight < base[cur->val].min_dis && !base[cur->val].isVisited)
                {
                    base[cur->val].min_dis = cur->weight;
                    base[cur->val].near = top_val;
                    q.push(make_pair(cur->weight, cur->val));
                }
                cur = cur->pnext;
            }
            base[top_val].isVisited = true;
        }

        int sum_weight = 0;
        cout << "MST tree (Prim): " << endl;
        for (int i = 0;i < vnum;i++)
        {
            if (base[i].near != -1)
            {
                cout << setw(4) << i << setw(4) << base[i].near << setw(4) << base[i].min_dis << endl;
                sum_weight += base[i].min_dis;
            }
        }
        cout << "Sum weight: " << sum_weight << endl;
    }

    int find(int _node, int _linked[])
    {
        int cur = _node;
        while (_linked[cur] > -1)
            cur = _linked[cur];
        return cur;
    }

    void Kruskal(int _start)
    {
        vector<edge> q;
        int linked[vnum];
        int sum_weight = 0;
        memset(linked, -1, sizeof(int) * vnum);
        for (int i = 0;i < vnum;i++)
        {
            node* cur = base[i].pnext;
            while (cur != nullptr)
            {
                q.push_back(edge{ i,cur->val,cur->weight });
                cur = cur->pnext;
            }
        }
        sort(q.begin(), q.end(), [](edge a, edge b) {return a.weight < b.weight;});
        cout << "MST tree (Kruskal): " << endl;
        for (int i = 0, n = 0;n < vnum - 1;i++)
        {
            int source1 = find(q[i].u, linked);
            int source2 = find(q[i].v, linked);
            if (source1 != source2)
            {
                cout << setw(4) << q[i].u << setw(4) << q[i].v << setw(4) << q[i].weight << endl;
                sum_weight += q[i].weight;
                linked[source2] = source1;
                n++;
            }
        }
        cout << "Sum weight: " << sum_weight << endl;
    }

private:
    node* base;
    int vnum;
};

#endif /* end mst */
