#include <iostream>
#include <vector>

using namespace std;

// template <typename T>
// struct ParCV
// {
//     T chave;
//     int valor;

//     bool operator< (const ParCV<T>& rhs)
//     {
//         return (this->valor < rhs.valor);
//     }

//     ostream& operator<< (ostream& out)
//     {
//         out<< "(" << this->chave << "," << this->valor << ")";
//         return (out);
//     }

//     ParCV(T c, int v): chave(c), valor(v) {} 
// };

// template <typename T>
// ostream& operator<< (ostream& out, const ParCV<T>& p)
// {
//     out<< "(" << p.chave << "," << p.valor << ")";
//     return (out);
// }


template <typename T> 
class MinHeap
{
    private:       
        vector<T> heap;

        void heapify(int i)
        {
            int l = 2*i;
            int r = 2*i + 1;
            int smallest = i;
            if (l < heap.size() && heap[l] < heap[smallest]) smallest = l;
            if (r < heap.size() && heap[r] < heap[smallest]) smallest = r;

            if (smallest != i)
            {
                swap(heap[smallest], heap[i]);
                heapify(smallest);
            }
        }

        void build_min_heap()
        {
            for (int i = heap.size()/2; i >=0; i--)
            {
                heapify(i);
            }
        }

    public:

        void push(T e)
        {
            heap.push_back(e);
            build_min_heap();
        }

        T pop()
        {
            T min_elem = heap[0];
            heap.erase(heap.begin());
            build_min_heap();
            return min_elem;
        }

        void print()
        {
            for(int i = 0; i <heap.size(); i++)
            {
               cout<<heap[i]<<endl;
            }
        }

        int size()
        {
            return heap.size();
        }
 };

// int main()
// {
//     MinHeap<ParCV<char> > heap;

//     ParCV<char> a = ParCV<char>('a', 13);
//     ParCV<char> b = ParCV<char>('b', 15);
//     ParCV<char> c = ParCV<char>('f', 69);
    
//     heap.push(ParCV<char>('f', 69));
//     heap.push(a);
//     heap.push(b);

//     ParCV<char> d = heap.pop();
//     ParCV<char> e = heap.pop();
//     ParCV<char> f = heap.pop();
//     cout<< a << endl << b << endl << c <<endl;
// }