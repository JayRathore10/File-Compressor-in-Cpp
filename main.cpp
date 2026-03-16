#include<iostream>
#include<fstream>

#define ll long long 

using namespace std ;

double convertByteToMB(ll);

int main(int argc , char** argv){
  cout<<"File compressor"<<endl;
  ifstream file("sample.txt");

  if(!file){
    cout<<"Error in file opening"<<endl;
    return 0;
  }

  file.seekg(0 , ios::end);
  ll size = file.tellg();

  cout<<"File size : "<<(convertByteToMB(size))<<endl;

  file.close();
  return 0; 
}

double convertByteToMB(ll bytes){
  return ((double)bytes / 1000000);
}
