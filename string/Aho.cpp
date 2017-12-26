//Można dodać wzorzec P do drzewa TRIE BFSem lub DFSem
//trie->addPattBFS(P); trie->addPattDFS(P, 0);
//Wypisanie wzorców leksykograficznie: string P; trie->printLexicographically(P);
//Wypisanie liczby wystąpień wszystkich wzorców w tekście T: cout << trie->matchPatterns(T);

#define nd second

struct Node
{
     //Krawędzie w drzewie TRIE
     map<char, Node *> edge;
     //Rodzic w drzewie TRIE, link do najdłuższego prefikso - sufiksu, link do najdłuższego wzorca będącego sufiksem
     Node * par, * suflink, * patlink;
     //Liczba wzorców będących sufiksami słowa kończącego się w tym węźle, liczba wzorców kończących się w tym węźle
     int patts, patt;
     //Litera na krawędzi, która prowadzi do tego węzła
     char c;

     Node(char c, Node * N) : c(c), par(N), suflink(nullptr), patlink(nullptr), patt(0), patts(0) {}

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

     //Tworzy suflinki i patlinki
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

     //Wyszukuje liczbę wystąpień wszystkich wzorców w tekście T
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
                 cout << s.substr(1, s.size()-1) << "\n";
             }
         }
         s.pop_back();
     }
};

//Tworzy super korzeń i korzeń drzewa TRIE
Node * root, *aho;
void init()
{
    root = new Node(' ', nullptr);
    aho = new Node(' ', root);
    aho->suflink = aho->patlink = root;
    for (int i = 0; i < 26; i++)
    {
        root->edge[(char)('a'+i)] = aho;
    }
}
