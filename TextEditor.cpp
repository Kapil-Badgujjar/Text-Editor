#include<bits/stdc++.h>
#include<conio.h>
//#include<fstream>
using namespace std;
//Remember class to store last actions and data
class remember{
    private:
    string data[5];
    int number[5];
    int front=-1,back=-1;
    public:
    bool isEmpty(){
        if(front==-1) return true;
        else return false;
    }
    void push(string stringData){ 
        //if remeber is empty( front = -1 ) increase front and back to zero index means first element
        if(front==-1){ 
            front=back=0;
            //name[back]=stringName; 
            data[back]=stringData;
        }
        else if((5+front-1)%5==back){ //if remeber is full  [we have to delete front and store new element]
        //used modulas operator to getback to 0th index
            front=(front+1)%5;    //increase front [ but max upto 4th index ]
            back=(back+1)%5;    //incrase back [ but max upto 4th index ] and store element to this position
            data[back] = stringData;
        }
        else{   //if remember is not full as well as not empty 
            back=(back+1)%5;    //incerase back [ but max upto 4th index ]
            data[back] = stringData;    //store new element
        }     
    }
    string pop(){
        string temp;    //create a temp string
        if(front!=-1&&back!=-1) //if remeber is not empty 
        {
            if(front==back){    //if front and back are same means only one element if poped make front and bake -1 to show remeber is empty
                temp=data[back]; front=back=-1;
            }
            else{   //if store more than one elements
                temp = data[back];
                back = (5+back-1)%5;
            }
        }
        else temp=">>>  ! !  Error in Returning File  ! !  <<<  || check for isEmpty() befor calling pop! ";
        return temp;        
    }
};
//editor class to provide functionality
class editorClass{
    private:
    //Function to insert and append new data
    string insertData(){
        string temp="";
        char c ;
        while((c=getchar())!='`'){
            temp += c;
        }
        return temp;
    }
    //Insert function end.
    //Function to find pattern in pattern itself
    void processPattern(string ptrn,int m, int *lps){   //Taking arguments (Pattern,size of pattern,a pointer to store pattern details)
        int len=0;  //variable to count the repeated occurance
        lps[0] = 0; //Initial character of the patter always occure once, it is not repeated before itself
        int i=1;    //Varialbe to iterate
        while(i<m){
            if(ptrn[i]==ptrn[len]){ //If character match to its next character increament len and store in pointer on ith index
                len++;
                lps[i] = len;
                i++;
            }
            else if(len!=0){    //If it is end of string
                len = lps[len-1];   //len equals to last stored value
            }
            else{   //If it is not end of string and characters are also not matching
                lps[i]=0;       //than store 0 to point oth index of pattern at ith index in pointer
                i++;    
            }
        }
    }
    int search(string s){
        int index=-1;   //if index does not updated we return -1 to indicate pattern is not found
        string ptrn;   
        cout<<"Enter a word: ";
        cin>>ptrn;
        int n=s.length(),m=ptrn.length(),i=0,j=0;   //n is length of our string and m is length of pattern
        int lps[m]; //an array of size m to store pattern repeatation details
        processPattern(ptrn,m,lps);     // preprocessing pattern to find patterns in pattern itself
        while((n-i)>=(m-j)){    
            if(s[i]==ptrn[j]){  
                i++; j++;   //Increamenting both i and j if characters of string and pattern are same
            }
            if(j==m){   //if we reach the end of pattern means we found the pattern in given string
                index=i-j;
                j=lps[j-1]; 
            }
            else if(i<n&&ptrn[j]!=s[i]){  if(j!=0) j=lps[j-1]; else i++;     }      //if a mismatch found than check for last repeatation of character in pattern and jump back j to that index in pattern
        }
        return index;  
    }
    //Update function to update given string
    string update(string str){
        string s,data;
        int l=str.length();
        cout<<"Enter a string before you want to enter new text: ";
        cin>>s;
        cout<<"Enter new data to insert & press '`' before pressing enter : ";
        data=insertData();
        int pos=str.find(s);
        if(pos-1<0) return data+str;
        else if(pos==l-1) return str+data;
        else if(pos-1>0&pos<l-1) return str.substr(0,pos-1)+" "+data+" "+str.substr(pos,l-pos);
        else return str;
    }
    //End of Update function
    //Delete Function
    string deleteData(string str){
        string s,data;
        int l=str.length(); 
        cout<<"Enter data [word] that you want to delete : ";
        cin>>data;
        cout<<endl<<"you entered : "<<data<<endl;
        int pos=str.find(data), m=data.length();
        if(pos==0&&m>0) s= str.substr(m,l-m);
        else if(pos==l-1) s= str.substr(0,l-1);
        else if(pos>0&&pos<l)
        {
            s=str.substr(0,pos-1)+str.substr(pos+m,l-pos-m+1);
        }
        else s= str;
        return s;
      }
      //End of delete function
      //Function to save string in files
      void save(string s){
        string filename;
        cout<<"Enter filename (with extension): ";
        cin>>filename;
        ofstream save(filename);
        save<<s;
        cout<<"File saved successfully..."<<endl;
      }
      //End of save function
      public:
     //Operations Function
    void operation(char choice, string &s,remember *obj){
        int a=-1;
         switch(choice){ 
            case 'i':  obj->push(s); cout<<">>> In Insert Mode Press '`' before pressing enter. <<<"<<endl<<endl; s=insertData();  cout<<endl<<endl<<"Data inserted successfully."<<endl; break; 
            case 'u': obj->push(s); cout<<">>> In Update Mode <<<"<<endl; s = update(s); cout<<endl<<endl<<"Data updated successfully"<<endl; break;
            case 'a': obj->push(s); cout<<endl<<">>> In Append Mode <<<"<<endl; getch(); if(s!="") {s+=" "+insertData().substr(1);} else { s=insertData();} cout<<"Data Appended successfully."<<endl; break;
            case 'f':  cout<<">>> In Search Mode <<<"<<endl; a = search(s); if(a>=0) cout<<"Found at index: "<<a<<endl; else cout<<"Not found!"<<endl; break;
            case 'd': obj->push(s); cout<<">>> In Delete Mode <<<"<<endl; s=deleteData(s); break;
            case 'p':cout<<">>> In Print Mode <<<"<<endl;  cout<<endl<<s<<endl<<endl; break;
            case 'y': if(!obj->isEmpty()) {s = obj->pop(); cout<<endl<<"Undo Successfully."<<endl; } else cout<<endl<<"Can't undo"<<endl; break;
            case 's': save(s); break;
            case 'x': cout<<">>> Exited successfully <<<"; exit(0);
            default: cout<<endl<<"Please enter a valid choice!"<<endl<<endl;
            }
    }
};
int main()
{
    char choice='b';
    bool flag=false;
    while(!flag){
        cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
        cout<<"|                                                          Text Editor                                                    |"<<endl; 
        cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
        cout<<endl<<"Press -> [ n ] : To creat new string, [ x ] To exit  :  "  ; choice=getch();
        if(choice=='x') break; //exit(0);
        else if(choice=='n') flag=true;
        else cout<<"You dont have space to enter text!"<<endl<<"Please create a new string or exit."; 
        }
    remember *R =new remember;
    string s;
    editorClass e;
    while(flag){
         cout<<endl<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
        cout<<"|       Options : Press->      [ i ] To insert.  [ u ] To update. [ a ] To append. [ s ] To save.    [ d ] To delete.     |"<<endl;
        cout<<"|                              [ p ] To display. [ f ] To search. [ y ] To undo.   [ b ] To go back. [ x ] To exit.       |"<<endl;  
        cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
        cout<<endl<<"    :     ";
        choice=getch();
        e.operation(choice,s,R);
    }
    cout<<endl<<"Program Closed Successfully..."<<endl;
    return 0;
}