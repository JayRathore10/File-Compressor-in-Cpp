#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<fstream>

using namespace std ;

struct Node{
  char ch ;
  int freq ;
  Node* left ;
  Node* right;

  Node(char c , int f){
    ch = c;
    freq = f;
    left = right = NULL;
  }
};

struct Compare {
  bool operator()(Node* a , Node* b){
    return a->freq > b->freq;
  }
};

Node* buildTree(unordered_map<char , int>& freq){
  priority_queue<Node* , vector<Node*> , Compare> pq;

  for(auto& p : freq){
    pq.push(new Node(p.first , p.second));
  }

  while(pq.size() > 1){
    Node* left = pq.top() ; pq.pop();
    Node* right = pq.top() ; pq.pop();

    Node* merged = new Node('\0' , left->freq + right->freq);
    merged->left = left;
    merged->right = right;

    pq.push(merged);

  }
  return pq.top();
}

void generateCodes(Node* root , string code , unordered_map<char , string>& huff){
  if(!root) return ;

  if(root->ch != '\0'){
    huff[root->ch] = code;
  }

  generateCodes(root->left , code + "0" , huff);
  generateCodes(root->right , code + "1" , huff);

}

string encode (string text , unordered_map<char ,string>& huff){
  string res = "";
  for(char c : text){
    res += huff[c];
  }

  return res;
}

int main(int argc , char** argv){
  
  ifstream in("sample.txt");

  if(!in){
    cout<<"Error in opening input file"<<endl;
    return 1;
  }

  string text((istreambuf_iterator<char>(in)) , istreambuf_iterator<char>());

  unordered_map<char , int> freq;
  for(char c : text){
    freq[c]++;
  }


  Node* root = buildTree(freq);

  unordered_map<char, string> huff;
  generateCodes(root ,"" , huff);

  cout<<"Huffman Code: "<<endl;
  for(auto &p : huff){
    cout<<p.first<<" : "<<p.second<<endl;
  }

  string encodeText = encode(text ,huff);

  ofstream out("compressed.txt");
  out << encodeText;

  cout<<"Compressed successfull"<<endl;

  return 0;
}