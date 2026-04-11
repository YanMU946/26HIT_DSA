#include "Binary_Tree.h"

int main()
{
    Tree<char> mamba("syHC##Y##au##n##neh##n##b##");
    cout << "*µÝ¹é*Ç°Ðò±éÀú£º" << endl;
    mamba.PreOrder_Print(mamba.Get_Root());
    cout << endl << "*·ÇµÝ¹é*Ç°Ðò±éÀú£º" << endl;
    mamba.PreOrder_Print_N();

    cout << "*µÝ¹é*ÖÐÐò±éÀú£º" << endl;
    mamba.InOrder_Print(mamba.Get_Root());
    cout << endl << "*·ÇµÝ¹é*ÖÐÐò±éÀú£º" << endl;
    mamba.InOrder_Print_N();

    cout << "*µÝ¹é*ºóÐò±éÀú£º" << endl;
    mamba.PostOrder_Print(mamba.Get_Root());
    cout << endl << "*·ÇµÝ¹é*ºóÐò±éÀú£º" << endl;
    mamba.PostOrder_Print_N();

    cout << "²ãÐò±éÀú£º" << endl;
    mamba.BFS();

    mamba.~Tree();
    return 0;
}
