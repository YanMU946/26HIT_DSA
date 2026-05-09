#include "mst.h"

int main()
{
    ifstream infile("graph.in");
    if (!infile)
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    int num, edges;
    infile >> num >> edges;
    graph mst_t(num);

    int a, b, weight;
    for (int i = 0; i < edges; i++)
    {
        infile >> a >> b >> weight;
        mst_t.insert(a, b, weight);
    }

    infile.close();

    mst_t.Prim(2);
    cout << "------------------------------------------------------------" << endl;
    mst_t.Kruskal(10);
    return 0;
}
