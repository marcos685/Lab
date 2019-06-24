#include <fstream>
#include <map>
#include <string>
#include "minheap.hpp"

using std::fstream;
using std::map;
using std::string;

struct Huffnode
{
    unsigned char elem;
    int peso;
    Huffnode *left;
    Huffnode *right;

    friend ostream& operator<< (ostream& out, Huffnode& huff)
    {
        out<< "(" << huff.elem << "," << huff.peso << ")";
        return (out);
    }

    bool operator< (const Huffnode& rhs)
    {
        return (this->peso < rhs.peso);
    }

    Huffnode () = default;

    Huffnode(char elem, int peso) 
    : elem(elem), peso(peso), left(nullptr), right(nullptr) {}

    Huffnode(Huffnode *l, Huffnode *r)
    : elem('-'), peso(l->peso + r->peso), left(l), right(r) {}
};

/* void make_code(map<unsigned char, string>& results, string padrao = "")
{
    if (this->left == nullptr && this->right == nullptr) 
        results[elem] = padrao;
    else
    {
        if (this->left != nullptr) 
            left->make_code(results, padrao+"0");
        if (this->right != nullptr) 
            right->make_code(results, padrao+"1");
    }
}*/
void traverse(Huffnode huf)
{
    cout << huf;
    if(huf.left != nullptr)  traverse(*(huf.left));
    if(huf.right != nullptr) traverse(*(huf.right));
}

map<unsigned char, int> contar_chars (char* filename)
{
    fstream file(filename);
    map<unsigned char, int> chars;
    MinHeap<Huffnode> ordered_chars;
    

    while(file.peek() != EOF)
    {
        ++chars[file.get()];
    }

    return chars;
}

vector<Huffnode> make_huff_tree(map<unsigned char, int> chars)
{
    vector<Huffnode> huff_tree;
    MinHeap<Huffnode> ordered_chars;

    for (const auto& c : chars)
    {
        huff_tree.push_back(Huffnode(c.first, c.second));
    }
    
    for (int i = 0; i < huff_tree.size(); i++)
    {
        cout << &huff_tree[i];
        ordered_chars.push(&huff_tree[i]);
        
    }

    ordered_chars.print();
    while(ordered_chars.size() > 1)
    {
        Huffnode *x = ordered_chars.pop();
        Huffnode *y = ordered_chars.pop();
        Huffnode z = Huffnode(x, y);
        huff_tree.push_back(z);
        cout << z << x <<y <<'\n';

        ordered_chars.push(&(huff_tree[huff_tree.size()-1]));
    }

    return huff_tree;
}

   // for (int i = 0; i < huff_tree.size(); i++) cout<< huff_tree[i];
    

    // map<unsigned char, string> codigo;
    // w->make_code(codigo);

    // for (const auto& c : codigo)   
    // {
    //     cout << '(' << c.first <<' ' << c.second << ')' << '\n';
    // }



int main(int argc, char** argv)
{
    char* fname = argv[1];
    map<unsigned char, int> ch;
    vector<Huffnode> huf_tr;

    ch = contar_chars(fname);
    /* for (const auto& c : ch)
    {
        cout<<c.first<<c.second<<'\n';
    }*/

    huf_tr = make_huff_tree(ch);
    //cout << *(huf_tr[huf_tr.size()-1].left);
    traverse(huf_tr[huf_tr.size()-1]);

    /*/for (int i = 0; i < huf_tr.size(); i++)
    {
        if(huf_tr[i].left != nullptr ) 
            cout << (huf_tr[i].left) << ' ';
        if (huf_tr[i].right != nullptr) 
            cout << (huf_tr[i].right) << ' ';

        cout << '\n';
    }*/

    //compress(fname);
}
