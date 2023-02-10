#include<iostream>
using namespace std;
class myStack{
    int top=-1,SIZE=5;
    string s[5];
    public:
    myStack(){
    }
    bool isFull(){
        if(top==SIZE-1) return true;
        else return false;
    }
    bool isEmpty(){
        if(top==-1) return true;
        else return false;
    }
    void push(string x){
        if(!isFull())
        s[++top] = x;
    }
    string pop(){
        if(!isEmpty()){
            return s[top--];
        }
        else return "EOF";
    }
};

int main(){

}