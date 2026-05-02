#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *l, *r;
    Node(char c, int f) : ch(c), freq(f), l(nullptr), r(nullptr) {}
    Node(Node* L, Node* R) : ch('\0'), freq(L->freq + R->freq), l(L), r(R) {}
};

struct PQ {
    Node* data[256];
    int size;
    PQ() : size(0) {}
    void push(Node* n) {
        int i = size++;
        data[i] = n;
        while (i > 0 && data[i]->freq < data[(i-1)/2]->freq) {
            swap(data[i], data[(i-1)/2]);
            i = (i-1)/2;
        }
    }
    Node* top() { return data[0]; }
    void pop() {
        data[0] = data[--size];
        int i = 0;
        while (true) {
            int l = 2*i + 1, r = 2*i + 2, smallest = i;
            if (l < size && data[l]->freq < data[smallest]->freq) smallest = l;
            if (r < size && data[r]->freq < data[smallest]->freq) smallest = r;
            if (smallest == i) break;
            swap(data[i], data[smallest]);
            i = smallest;
        }
    }
    bool empty() { return size == 0; }
};

// Map codes using simple arrays
struct CodeMap {
    char chars[256];
    string codes[256];
    int count;
    CodeMap() : count(0) {}
    void add(char c, string code) { chars[count] = c; codes[count++] = code; }
    string get(char c) {
        for (int i=0;i<count;i++) if (chars[i]==c) return codes[i];
        return "";
    }
    char rev(string code) {
        for (int i=0;i<count;i++) if (codes[i]==code) return chars[i];
        return '\0';
    }
};

void buildCodes(Node* root, string s, CodeMap &cm) {
    if (!root) return;
    if (!root->l && !root->r) { cm.add(root->ch, s); return; }
    buildCodes(root->l, s + "0", cm);
    buildCodes(root->r, s + "1", cm);
}

void compressFile(const string &filename) {
    ifstream in(filename, ios::binary);
    if (!in) { cout<<"Cannot open file.\n"; return; }
    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>()); in.close();
    if (data.empty()) { cout<<"Empty file.\n"; return; }

    int freq[256] = {0};
    for (char c: data) freq[(unsigned char)c]++;

    PQ pq;
    for (int i=0;i<256;i++) if (freq[i]>0) pq.push(new Node((char)i, freq[i]));

    while (pq.size > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        pq.push(new Node(a,b));
    }
    Node* root = pq.top();

    CodeMap cm;
    buildCodes(root, "", cm);

    string encoded;
    for (char c: data) encoded += cm.get(c);

    ofstream out(filename + ".huff", ios::binary);
    out << encoded;
    out.close();

    ofstream mfile(filename + ".map");
    for (int i=0;i<cm.count;i++)
        mfile << (int)(unsigned char)cm.chars[i] << ' ' << cm.codes[i] << '\n';
    mfile.close();

    cout << "Compressed to " << filename << ".huff (map: " << filename << ".map)\n";
}

void decompressFile(const string &filename) {
    string base = filename;
    if (base.size() > 5 && base.substr(base.size()-5)==".huff") base = base.substr(0, base.size()-5);

    CodeMap cm;
    ifstream mfile(base + ".map");
    if (!mfile) { cout<<"Map file not found.\n"; return; }
    int code;
    string bits;
    while (mfile >> code >> bits) cm.add((char)code, bits);
    mfile.close();

    ifstream in(base + ".huff", ios::binary);
    string encoded((istreambuf_iterator<char>(in)), istreambuf_iterator<char>()); in.close();

    string cur;
    string outname = base + ".dehuff";
    ofstream out(outname, ios::binary);
    for (char b: encoded) {
        cur.push_back(b);
        char c = cm.rev(cur);
        if (c!='\0') { out << c; cur.clear(); }
    }
    out.close();
    cout << "Decompressed to " << outname << '\n';
}

void FileCompressor() {
    cout << endl << "FILE COMPRESSOR MODULE LOADED!" << endl;
    cout << "File Compressor: 1) compress 2) decompress 3) back\nChoose: ";
    int c; if (!(cin >> c)) return;
    if (c == 1) {
        cout << "Enter filename to compress: ";
        string f; cin >> f; compressFile(f);
    } else if (c == 2) {
        cout << "Enter .huff filename to decompress: ";
        string f; cin >> f; decompressFile(f);
    }
}