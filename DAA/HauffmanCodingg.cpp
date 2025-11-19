// #include <bits/stdc++.h>
// using namespace std;

// struct Node{
//     char ch; int freq;
//     Node *left,*right;
//     Node(char c,int f){ ch=c; freq=f; left=right=NULL; }
// };

// struct compare{ bool operator()(Node* a, Node* b){ return a->freq > b->freq; } };

// void printCodes(Node* root, string s){
//     if(!root) return;
//     if(!root->left && !root->right) cout<<root->ch<<": "<<s<<"\n";
//     printCodes(root->left,s+"0");
//     printCodes(root->right,s+"1");
// }

// void huffman(vector<char>& chars, vector<int>& freq){
//     priority_queue<Node*, vector<Node*>, compare> pq;
//     for(int i=0;i<chars.size();i++) pq.push(new Node(chars[i], freq[i]));
//     while(pq.size()>1){
//         Node* l=pq.top(); pq.pop();
//         Node* r=pq.top(); pq.pop();
//         Node* top=new Node('$', l->freq+r->freq);
//         top->left=l; top->right=r;
//         pq.push(top);
//     }
//     printCodes(pq.top(),"");
// }



// int main(){
//     vector<char> chars={'a','b','c','d','e'};
//     vector<int> freq={10,20,100,500,1000};
//     huffman(chars,freq);
// }



#include <bits/stdc++.h>
using namespace std;


struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

struct cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};


void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}


void huffmanEncoding(string text) {

    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;


    priority_queue<Node*, vector<Node*>, cmp> pq;
    for (auto it : freq) {
        pq.push(new Node(it.first, it.second));
    }

   
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);


    cout << "\nHuffman Codes:\n";
    for (auto p : huffmanCode) {
        cout << p.first << " : " << p.second << endl;
    }


    string encoded = "";
    for (char c : text) encoded += huffmanCode[c];
    cout << "\nEncoded String: " << encoded << endl;

 
    int originalSize = text.size() * 8; 
    int compressedSize = encoded.size();
    cout << "Original Size (bits): " << originalSize << endl;
    cout << "Compressed Size (bits): " << compressedSize << endl;
    cout << "Compression Ratio: " << (double)originalSize / compressedSize << endl;
}

int main() {
    string text;
    cout << "Enter text to compress: ";
    getline(cin, text);

    huffmanEncoding(text);
    return 0;
}
