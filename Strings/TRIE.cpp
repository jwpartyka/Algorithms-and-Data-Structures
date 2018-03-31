// You can insert a pattern P into the TRIE using BFS or DFS
// trie -> addPattBFS(P); trie -> addPattDFS(P, 0);
// To print inserted patterns in lexicographical order: string P; trie -> printLexicographically(P)

#define nd second

struct Node
{
    // Edges of the TRIE
    map<char, Node *> edge;
    // Parent in the TRIE
    Node * par;
    // Number of patterns ending in this node
    int patt;
    // Character on the edge leading to this node
    char c;

    Node(char c, Node * N) : c(c), par(N), patt(0) {}

    Node * nex(char c, Node *N)
    {
        // Creates a new edge if there's no edge with character c on it
        if (N -> edge[c] == nullptr) N -> edge[c] = new Node (c, N);
        // Returns the node to which the c - edge leads
        return N -> edge[c];
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
        // Creates a new node if c - edge leads to nothing
        if (edge[c] == nullptr) edge[c] = new Node(c, this);
        // Returns the node to which the c - edge leads
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

    // Prints the inserted patterns in lexicographical order
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
                cout << s.substr(1, s.size()-1) << "\n";
            }
        }
        s.pop_back();
    }
};

// Root of the TRIE
Node * trie = new Node ('*', nullptr);
