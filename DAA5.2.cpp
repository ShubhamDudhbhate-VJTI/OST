#include <bits/stdc++.h>
using namespace std;
class node{
    public:
    long val;
    char c;
    node*left;
    node*right;
    node(long val,char c,node* left=nullptr,node* right=nullptr){
        this->val=val;
        this->c=c;
        this->left=left;
        this->right=right;
    }
};


map<char,string>m;
void dfs(node* root,string s){
    if(root->left==NULL&&root->right==NULL){
        m.insert({root->c,s});
        return;}
    
    dfs(root->left , s + "1");
    dfs(root->right, s + "0");
}


int main() {

    string filename = "book.txt";
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    map<char, long> freq;

    char ch;
        while (fin.get(ch)) {
            freq[ch]++;
        }
        fin.close();
        freq.erase('#');

    for (auto &p : freq) {
        if (isprint((unsigned char)p.first))
            cout << "'" << p.first << "' : " << p.second << "\n";
        else
            cout << "0x" << hex << (int)(unsigned char)p.first 
                 << dec << " : " << p.second << "\n";
    }
        priority_queue<
            node*, 
            vector<node*>, 
            function<bool(const node*, const node*)>
        > pq(
            [](const node* a, const node* b) {
                return a->val > b->val;
            }
        );
    for (auto it : freq) {
        node*temp=new node(it.second,it.first);
     pq.push(temp);
}
    while(pq.size()>=2){
        auto p1 = pq.top();pq.pop();
        auto p2 =pq.top(); pq.pop();
        node * node3= new node(p1->val+p2->val,'#',p1,p2);
        pq.push(node3);
    }
    node* root =pq.top();pq.pop();
    dfs(root,"");
    for (auto &p : m) {
        if (isprint((unsigned char)p.first))
            cout << "'" << p.first << "' : " << p.second << "\n";
        else
            cout << "0x" << hex << (int)(unsigned char)p.first 
                 << dec << " : " << p.second << "\n";
    }
        long long totalBits = 0;
        long long compressedBits = 0;
    for (auto &p : freq) {
        totalBits += p.second * 8;  
        string t = m[p.first];
        compressedBits += p.second * t.length();

    }
    cout<<totalBits<<endl;
    cout<<compressedBits<<endl;
    double resultOfCompression = ((double)compressedBits /double(totalBits)) * 100;
    cout << "Percentage of compression : " << 100-resultOfCompression << endl;
    return 0;
}


