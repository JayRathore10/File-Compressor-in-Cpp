#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<fstream>
#include<algorithm>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c,int f){ch=c;freq=f;left=right=NULL;}
};

struct Compare{
    bool operator()(Node* a,Node* b){
        return a->freq>b->freq;
    }
};

Node* buildTree(unordered_map<char,int>& freq){
    vector<pair<char,int>> arr(freq.begin(), freq.end());
    sort(arr.begin(), arr.end());

    priority_queue<Node*,vector<Node*>,Compare> pq;

    for(auto &p:arr){
        pq.push(new Node(p.first,p.second));
    }

    while(pq.size()>1){
        Node* l=pq.top(); pq.pop();
        Node* r=pq.top(); pq.pop();

        Node* m=new Node('\0',l->freq+r->freq);
        m->left=l;
        m->right=r;

        pq.push(m);
    }

    return pq.top();
}

void generateCodes(Node* root,string code,unordered_map<char,string>& huff){
    if(!root) return;
    if(!root->left && !root->right) huff[root->ch]=code;
    generateCodes(root->left,code+"0",huff);
    generateCodes(root->right,code+"1",huff);
}

string encode(string text,unordered_map<char,string>& huff){
    string res="";
    for(char c:text) res+=huff[c];
    return res;
}

int writeCompressed(string encoded,ofstream& out){
    char byte=0;
    int bitCount=0;
    for(char bit:encoded){
        byte<<=1;
        if(bit=='1') byte|=1;
        bitCount++;
        if(bitCount==8){
            out.put(byte);
            byte=0;
            bitCount=0;
        }
    }
    if(bitCount>0){
        byte<<=(8-bitCount);
        out.put(byte);
    }
    return encoded.size();
}

void writeFreqMap(ofstream& out,unordered_map<char,int>& freq){
    out<<freq.size()<<"\n";
    for(auto &p:freq){
        out<<(int)(unsigned char)p.first<<" "<<p.second<<"\n";
    }
}

unordered_map<char,int> readFreqMap(ifstream& in){
    int n; in>>n;
    unordered_map<char,int> freq;
    for(int i=0;i<n;i++){
        int ascii,f;
        in>>ascii>>f;
        freq[(char)ascii]=f;
    }
    return freq;
}

string decode(string& bits,Node* root){
    string result="";
    Node* curr=root;
    for(char bit:bits){
        if(bit=='0') curr=curr->left;
        else curr=curr->right;
        if(!curr->left && !curr->right){
            result+=curr->ch;
            curr=root;
        }
    }
    return result;
}

double convert_bytes_to_mb(long long bytes){
  return ((double)bytes / 1000000);
}

void find_file_size(ifstream& file){
  file.seekg(0 , ios::end);
  long long size = file.tellg();

  cout<<"File size : "<<(convert_bytes_to_mb(size))<<endl;
}

void find_file_size(ofstream& file){
  file.seekp(0 , ios::end);
  long long size = file.tellp();

  cout<<"File size : "<<(convert_bytes_to_mb(size))<<endl;
}

int main(){
    ifstream in("sample.txt");
    if(!in) return 1;

    string text((istreambuf_iterator<char>(in)),istreambuf_iterator<char>());

    unordered_map<char,int> freq;
    for(char c:text) freq[c]++;

    Node* root=buildTree(freq);

    unordered_map<char,string> huff;
    generateCodes(root,"",huff);

    string encodedText=encode(text,huff);

    ofstream out("compressed.bin",ios::binary);
    writeFreqMap(out,freq);
    out<<encodedText.size()<<"\n";
    writeCompressed(encodedText,out);

    find_file_size(in);
    find_file_size(out);

    in.close();
    out.close();

    ifstream inc("compressed.bin",ios::binary);

    auto freqC=readFreqMap(inc);

    int totalBits;
    inc>>totalBits;
    inc.get();

    Node* rootC=buildTree(freqC);

    string bits="";
    char byte;

    while(inc.get(byte)){
        for(int i=7;i>=0;i--){
            if(bits.size()==totalBits) break;
            bits+=((byte>>i)&1)?'1':'0';
        }
    }

    string decodedText=decode(bits,rootC);

    ofstream outD("decoded.txt");
    outD<<decodedText;

    find_file_size(outD);

    return 0;
}