#include<iostream>
#include<vector>
#include<utility>
#include<fstream>

#define ll long long 

using namespace std ;

class Node{
  public:
    char character ;
    int freq ;
    Node* l;
    Node* r;

    Node(char c ,int f){
      character = c;
      freq = f;
      l = r = nullptr;
    }
};

class MinHeap{
  public:
    int size ;
    vector<Node*> array ;

    MinHeap(int s){
      size = s ;
      array.resize(s);
    }

};

double convert_bytes_to_mb(ll);
void find_file_size(ifstream&);

int main(int argc , char** argv){
  cout<<"File compressor"<<endl;
  ifstream file("sample.txt");

  if(!file){
    cout<<"Error in file opening"<<endl;
    return 0;
  }

  find_file_size(file);

  file.close();
  return 0; 
}

double convert_bytes_to_mb(ll bytes){
  return ((double)bytes / 1000000);
}

void find_file_size(ifstream& file){
  file.seekg(0 , ios::end);
  ll size = file.tellg();

  cout<<"File size : "<<(convert_bytes_to_mb(size))<<endl;
}