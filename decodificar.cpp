#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

 static ofstream decodificado("decodificado.txt",fstream::app);
 template <typename Type> 
 class inteiro{
	public:
	Type *vec;
	int tamanho;
	
	inteiro():vec(NULL),tamanho(0){}	
	inteiro& operator+=(const Type &valor){
	   Type * temp= new Type [tamanho+1];
	   temp[tamanho]=valor;
	   for(int i=0;i<tamanho;i++){
	   	temp[i]=this->vec[i];
	   }
	   this->vec=temp;
	   tamanho++;
	   return *this;

    }
    
    void print(){
    	if(this->vec==NULL)
    	   return;
    	else{
		
    	for(int i=0;i<tamanho;i++)
    	cout<<this->vec[i]<<" ";
	}}
};

static string carac_fim="";
static inteiro <string> codes_fim;
 

class node
{
    public:
    int data;
    char caracter;
    node* left;
    node* right;
    node(int data):data(data),left(NULL),right(NULL){
	if(data>1000)
	caracter='$';
	else 
	caracter = data;
	}
};
 

int search(int arr[], int strt, int end, int value);
node* newNode(int data);
 


node* buildTree(int in[], int pre[], int inStrt, int inEnd)
{
    static int preIndex = 0;
 
    if (inStrt > inEnd)
        return NULL;
 
    
    node* tNode = newNode(pre[preIndex++]);
    
    
    if (inStrt == inEnd)
        return tNode;
 
    
    int inIndex = search(in, inStrt, inEnd, tNode->data);
 
    
    tNode->left = buildTree(in, pre, inStrt, inIndex - 1);
    tNode->right = buildTree(in, pre, inIndex + 1, inEnd);

    return tNode;
}

    void printPreorder(node* node)
{
	
	
    if (node == NULL)
        return;
 
    
     cout<< node->caracter;
 
    
    printPreorder(node->left);
 
   
    printPreorder(node->right);
}

int search(int arr[], int strt, int end, int value)
{
    int i;
    for (i = strt; i <= end; i++)
    {
        if (arr[i] == value)
            return i;
    }
}
 

node* newNode(int data)
{
    node* Node = new node(data);
    Node->data = data;
    Node->left = NULL;
    Node->right = NULL;
    if(Node->data>1000)
    Node->caracter='$';
    else
    Node->caracter=data;
 
    return (Node);
}
void printCodes(node* root, string str)
{   
    if (!root)
        return ;
 
    if (root->caracter != '$')
    cout << root->caracter << ": " << str << "\n";
 
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
    if(root->caracter!='$'){
	carac_fim+= root->caracter;
	codes_fim+=str;
	}
    
    return ;
}

void printInorder(node * node)
{   
    if (node == NULL)
        return;
 
    
    printInorder(node->left);
 
    
    cout<<node->caracter;
 
   
    printInorder(node->right);
} 
int * vetor(string str){
    string temp="";
	inteiro <string> numeros;
	for(int i=0;i<str.length();i++){
    	  if(str[i]==' '){
    	  numeros+=temp;
		  temp="";	
		  }
		  else{
			temp+=str[i];
    	
	}
	}
	
int *in= new int[numeros.tamanho];

for(int i=0;i<numeros.tamanho;i++){
	
	stringstream temp(numeros.vec[i]);
	
	temp>>in[i];
}

	return in;
}

node * busca (node * r, int k) {
    if (r == NULL || r->data == k)
       return r;
       return busca (r->left, k);
       return busca (r->right, k);
}


int main()
{
	//declaro os arquivos que serão lidos
 	ifstream preordem;
 	ifstream simetrico;
	ofstream clear;
	ifstream darquivo("codificado.txt");
	clear.open("decodificado.txt");
    clear.close();
    
    
	static string cpreordem="",csimetrico="";
	char ch;
	preordem.open("preordem.txt");
	 if(preordem.is_open()){
 	while(preordem.get(ch)){
		cpreordem+=ch;
	 }
 }
 else{
 	cout<<"Erro ao abrir o arquivo\n";
 } 
 
 preordem.close();
 char ch1;
 int cont;
 simetrico.open("simetrico.txt");
 if(simetrico.is_open()){
 	while(simetrico.get(ch1)){
 		if(ch1==' ')
 		cont++; 
 		
		csimetrico+=ch1;
	 }
 }
 else{
 	cout<<"Erro ao abrir o arquivo\n";
}
 simetrico.close();


int *intemp,*pretemp;
intemp=vetor(csimetrico);
pretemp=vetor(cpreordem);

int in[cont],pre[cont];

for(int i=0;i<cont;i++){
	in[i]=intemp[i];
	pre[i]=pretemp[i];
}


    



    int len= sizeof(in)/sizeof(in[0]);
    
    node* raiz = buildTree(in, pre, 0,len-1);
    printCodes(raiz,"");
	
    
    //Variaveis temporarias para ler e armazenar o caracter daquele instante
    //temp armazena 0's e 1's até que se torne igual a algum código 
    
	string temp1="";
    char o;
    //Abre o arquivo codificado, e vai montando o código, quando existe uma correspodencia ao código armazenado por temp
    //e por codigo, imprime no arquivo decodificado o caracter associado
    if(darquivo.is_open()){
 	while(darquivo.get(o)){
 		temp1+=o;
 		//cout<<temp<<endl;
 		for(int i=0;i<codes_fim.tamanho;i++){
		  if(temp1==codes_fim.vec[i]){
		  temp1="";
		  decodificado<<carac_fim[i];
	}
	}
		
	 }   
 }       
 else{
 	cout<<"Erro ao abrir o arquivo\n";
}	 
    
    
    return 0;
    
}
