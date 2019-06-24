#include <fstream>
#include <map>
#include <string>
#include "parCV.hpp"
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

    void make_code(map<unsigned char, string>& results, string padrao = "")
    {
        cout<<this->elem<<'\n';
        if (this->left == nullptr && this->right == nullptr) 
            results[elem] = padrao;
        else
        {
            if (this->left != nullptr) 
                left->make_code(results, padrao+"0");
            if (this->right != nullptr) 
                right->make_code(results, padrao+"1");
        }
    }

    void traverse()
    {
        cout << this->elem << " " << this->peso << "\n";
        if(this->left != nullptr) this->left->traverse();
        
        if(this->right != nullptr) this->right->traverse();
    }

    bool operator< (const Huffnode& rhs)
    {
        return (this->peso < rhs.peso);
    }

    ostream& operator<< (ostream& out)
    {
        out<< "(" << this->elem << "," << this->peso << ")";
        return (out);
    }

    Huffnode () = default;

    Huffnode(char elem, int peso) 
    : elem(elem), peso(peso), left(nullptr), right(nullptr) {}

    Huffnode(int peso, Huffnode l, Huffnode r)
    : elem('\0'), peso(peso), left(&l), right(&r) {}
};

void compress(char *filename)
{
    fstream file(filename);
    map<unsigned char, int> chars;
    MinHeap<Huffnode> ordered_chars;

    while(file.peek() != EOF)
    {
        ++chars[file.get()];
    }

    for (const auto& c : chars)
    {
        ordered_chars.push(Huffnode(c.first, c.second));
    }

    int n = ordered_chars.size();
    Huffnode x, y, z;
    for (int i = 0; i < n-1; ++i)
    {
        x = ordered_chars.pop();
        y = ordered_chars.pop();
        z = Huffnode(x.peso+y.peso, x, y);
        ordered_chars.push(z);
    } 

    x = ordered_chars.pop();
    cout << x.right->elem ;//<< " " << x.right->elem;
    //x.traverse();


    // map<unsigned char, string> codigo;
    // x.make_code(codigo);   
}

int main(int argc, char** argv)
{
    char* fname = argv[1];

    compress(fname);
}
