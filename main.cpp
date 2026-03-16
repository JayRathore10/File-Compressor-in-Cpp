#include<iostream>
#include<vector>
#include<utility>
#include<fstream>

#define ll long long 

using namespace std ;
/**
 *  [character , freq] + (left  , right)
 * 
 */
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
MinHeap* build_MinHeap(char[] , int[] , int);
void Heapify(MinHeap* ,int ,  int);

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

MinHeap* build_MinHeap(char arr[] , int freq[] , int unique_size){
  int i;
  MinHeap* minHeap = new MinHeap(unique_size);

  for(int i  = 0 ;  i < unique_size ; i++){
    minHeap->array[i] = new Node(arr[i] , freq[i]);
  }

  int n = minHeap->size - 1;
  for(int i = (n - 1) / 2 ; i >= 0 ; i--){
    Heapify(minHeap , i);
  }

  return minHeap;

}

void Heapify(MinHeap* minHeap  ,int n, int i){
  int smallest = i ;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if(l < n && minHeap->array[l] < minHeap->array[smallest]){
    smallest = l;
  }

  if(r < n && minHeap->array[r] < minHeap->array[smallest]){
    smallest = r;
  }

  if(i != smallest){
    swap(minHeap->array[i] , minHeap->array[smallest]);
    Heapify(minHeap , n , smallest);
  }

}
