//Można dodawać słowo s do drzewa TRIE BFSem lub DFSem
//trie->addPattBFS(s); trie->addPattDFS(s, 0);
//Wypisanie wzorców leksykograficznie: string s; trie->printLexicographically(s);

#define nd second

struct Node
{
    //Krawędzie w drzewie TRIE
    map<char, Node *> edge;
    //Rodzic w drzewie TRIE
    Node * par;
    //Liczba wzorców kończących się w tym węźle
    int patt;
    //Litera na krawędzi, która prowadzi do tego węzła
    char c;

    Node(char c, Node * N) : c(c), par(N), patt(0) {}

    Node * nex(char c, Node *N)
    {
        //Jeżeli nie istnieje węzeł po krawędzi c to go stwórz
        if (N->edge[c] == nullptr) N->edge[c] = new Node (c, N);
        //Zwróć węzeł po krawędzi c
        return N->edge[c];
    }
    void addPattDFS(string &P, int i)
    {
        if (i == P.size())
        {
            patt++;
            return;
        }
        nex(P[i])->addPattDFS(P, i+1);
    }

    Node * nex(char c)
    {
        //Jeżeli nie istnieje węzeł po krawędzi c to go stwórz
        if (edge[c] == nullptr) edge[c] = new Node(c, this);
        //Zwróć węzeł po krawędzi c
        return edge[c];
    }
    void addPattBFS(string &P)
    {
        Node * N = this;
        for (char c : P)
        {
            N = nex(c, N);
        }
        N->patt++;
    }

    //Wypisuje leksykograficznie wszystkie wzorce podane na wejściu
    void printLexicographically(string &s)
    {
        s += c;
        for (auto i : edge)
        {
            i.nd->printLexicographically(s);
        }
        if (edge.size() == 0)
        {
            for (int i = 0; i < patt; i++)
            {
                cout << s << "\n";
            }
        }
        s.pop_back();
    }
};

//Korzeń drzewa, można napisać lokalnie w mainie
Node * trie = new Node ('*', nullptr);
