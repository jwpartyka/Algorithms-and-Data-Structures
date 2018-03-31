// Aho - Corasick: Matching multiple patterns in linear time
// You can insert a pattern P into the TRIE using BFS or DFS
// trie -> addPattBFS(P); trie -> addPattDFS(P, 0);
// To print inserted patterns in lexicographical order: string P; trie -> printLexicographically(P)
// To count occurrences in string T of every inserted pattern simultaneously: trie -> matchPatterns(T);
// Complexity: O(sum(|P|) + |T|) where sum(|P|) is a sum of lengths of the inserted patterns

#define nd second

struct Node
{
    // Edges of the TRIE
    map<char, Node *> edge;
    // Parent in the TRIE, link to the logest preffix which is my suffix, link to the longest pattern which is my suffix
    Node * par, * suflink, * patlink;
    // Number of patterns which are suffixes of the word ending in this node, number of patterns ending in this node
    int patts, patt;
    // Character on the edge leading to this node
    char c;

    Node(char c, Node * N) : c(c), par(N), suflink(nullptr), patlink(nullptr), patt(0), patts(0) {}

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

    // Creates suflinks and patlinks
    void linkuj()
    {
        queue<Node *> Q;
        for (auto i : edge) Q.push(i.nd);
        while (!Q.empty())
        {
            Node * N = Q.front();
            Q.pop();

            Node * suf = N->par->suflink;
            while (suf->edge.find(N->c) == suf->edge.end())
            {
                suf = suf->suflink;
            }
            N->suflink = suf->edge[N->c];
            N->patlink = (N->suflink->patt ? N->suflink : N->suflink->patlink);
            N->patts = N->patlink->patts + N->patt;

            for (auto i : N->edge)
            {
                Q.push(i.nd);
            }
        }
    }

    // Counts occurrences of the inserted patterns in string T
    int matchPatterns(string &T)
    {
        Node * N = this;
        int res = 0;
        for (char c : T)
        {
            while (N->edge.find(c) == N->edge.end())
            {
                N = N->suflink;
            }
            N = N->edge[c];
            res += N->patts;
        }
        return res;
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

// Creates the super - root (parent of the root) and the root of the TRIE
Node * root, *aho;
void init()
{
    root = new Node('^', nullptr);
    aho = new Node('*', root);
    aho->suflink = aho->patlink = root;
    for (int i = 0; i < 26; i++)
    {
        root->edge[(char)('a'+i)] = aho;
    }
}
