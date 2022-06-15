#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <tchar.h>

using namespace std;
static string carac_fim="";
static ofstream simetrico("simetrico.txt",fstream::app);
static ofstream preordem("preordem.txt",fstream::app);
static ofstream registro("registro.txt",fstream::app);
static ofstream codificado("codificado.txt",fstream::app);

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

static inteiro <string> codes_fim;
static inteiro<int> freq_fim;
static int n_obj=0;


//Arvore de Huffman
struct MinHeapNode {
    
   
    char data;
 
    
    unsigned freq;
 
    MinHeapNode *left, *right;
    int position;
    MinHeapNode(char data, unsigned freq)
 
    {
    	n_obj++;
        left = right = NULL;
        this->data = data;
        this->freq = freq;
        position=n_obj;
    }
};
 

struct compare {
 
    bool operator()(MinHeapNode* l, MinHeapNode* r)
 
    {
        return (l->freq > r->freq);
    }
};
 

void printCodes(struct MinHeapNode* root, string str)
{   
    if (!root)
        return ;
 
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
 
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
    if(root->data!='$'){
    registro<<root->data<<'-'<<str<<endl;
	carac_fim+= root->data;
	freq_fim+= root->freq;
	codes_fim+=str;
	}
    
    return ;
}
void printPreorder(MinHeapNode* node)
{	
    if (node == NULL)
        return;
 
    
    if(node->data=='$'){
    preordem<< (int)node->data+node->position+1000<<" ";
    }
	else
    preordem<< (int)node->data<<" ";
  
 
    
    printPreorder(node->left);
 
   
    printPreorder(node->right);
}

void printInorder(struct MinHeapNode* node)
{  
    if (node == NULL)
        return;
    
  
    
    
    
   
    printInorder(node->left);
 
    
	if(node->data=='$'){
	
    simetrico<< (int)node->data+node->position+1000<<" ";
	}
	else
	simetrico << (int)node->data<<" ";
 

    printInorder(node->right);
} 

MinHeapNode* HuffmanCodes(char data[], int freq[], int size)
{   
    struct MinHeapNode *left, *right, *top;
 
    
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
 
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));
 
    
    while (minHeap.size() != 1) {
 
    
        left = minHeap.top();
        minHeap.pop();
 
        right = minHeap.top();
        minHeap.pop();
 
    
        top = new MinHeapNode('$', left->freq + right->freq);
 
        top->left = left;
        top->right = right;
 
        minHeap.push(top);
    }
 

   printCodes(minHeap.top(), "");
   return top;
}
 

int main()
{
 
 //limpo o conteúdo dos arquivos
 ofstream clear;
 clear.open("simetrico.txt");
 clear.close();
 clear.open("preordem.txt");
 clear.close();
 clear.open("registro.txt");
 clear.close();
 clear.open("codificado.txt");
 clear.close();
 clear.open("preordem.txt");
 clear.close();
 clear.open("simetrico.txt");
 clear.close();
 
 //declaro os arquivos que serão lidos
 ifstream arquivo("entrada1.txt");



 //caracteres armazenas todos caracteres que aparecem uma vez
 //frequencia armazena a frequencia associada a cada um desse caracteres
 string caracteres="";
 inteiro <int> frequencia;
 //Variável temporária para armazenar o caracter que está sendo lido naquele instante
 char ch;


 //Abre a Entrada e conta a frequencia e armazena quais sao os caracteres
 if(arquivo.is_open()){
 	while(arquivo.get(ch)){
 		bool contido=false;
 		if(caracteres.empty()){
		caracteres+=ch;
		frequencia+=1;
		contido=true;
		 }
 	    else{
 	    	for(int i=0;i<caracteres.length();i++)
 	    	if(ch==caracteres[i]){
			 contido=true;
 	    	frequencia.vec[i]+=1;}
		 }
		 if(!contido){
		 	caracteres+=ch;
		 	frequencia+=1;
		 }
	 }
 }
 else{
 	cout<<"Erro ao abrir o arquivo";
 }
 cout<<'\n';
 arquivo.close();
 
     struct MinHeapNode *raiz;
    //Transformo a string que armazerna os caracteres para um char *, para poder mandar como parametro para Huffmann
    char *p= new char[caracteres.length()];
    strcpy(p, caracteres.c_str());
    
    raiz = HuffmanCodes(p, frequencia.vec, caracteres.length());
    cout<<endl;
    printInorder(raiz);
    printPreorder(raiz);
    
    
    
    //Le o arquivo de entrada, e enquanto lê escreve o codigo associado a aquele caracter no arquivo codificado.
    //Atentar que aqui utilizo variaveis estáticas que estão definidas no topo do código
    arquivo.open("entrada1.txt");
    if(arquivo.is_open()){
 	while(arquivo.get(ch)){
 	for(int i=0;i<carac_fim.length();i++){
	    if(ch==carac_fim[i]){
			codificado<<codes_fim.vec[i];	
		}
	  
	 }
 }
}

 
 else{
 	cout<<"Erro ao abrir o arquivo";
 }
 
	//Fecha os arquivos abertor para que se possa fazer a decodificação
	arquivo.close();
	codificado.close();
	registro.close(); 



	 
    system("PAUSE");
    return 0;
	}
