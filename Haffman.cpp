#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <limits>
using namespace std;

//create Uzel
class Node{
	public:
		int a;
		char c;
		Node *left, *right;
	 
		Node(){
			left=right=NULL;
		}

		Node(Node *L, Node *R) {  left =  L;
		right = R;
	    a = L->a + R->a;  
	    }
};

//create peregruzka op
struct peregruzka{
    bool operator()(const Node* l, const Node* r) const {
    	return l->a < r->a; 
    	}
};

void get_tree(string &user_input, Node *&tree){
	
//get count liter
    cin.sync();
    cin.clear();
	cout<<"enter string - ";
	getline(cin, user_input);
	cout<<endl;
	map<char,int> m;
	
	for(int i = 0; i < user_input.size();i++){ 
	
		char c = user_input[i]; 
	    m[c]++;
	}

// create all uzel list
	     	     
   list<Node*> all_uzel = {};
   for( map<char,int>::iterator itr=m.begin(); itr!=m.end(); ++itr){  
   
      Node *p = new Node;
      p->c = itr->first;
      p->a = itr->second;  
      all_uzel.push_back(p);      
      }	
	

//  create tree		

  while (all_uzel.size()!=1){  
  
     all_uzel.sort(peregruzka());
    
     Node *left = all_uzel.front();
     all_uzel.pop_front();
     Node *right= all_uzel.front(); 
     all_uzel.pop_front();
     
     tree = new Node(left,right); 
     all_uzel.push_back(tree);

  }
	tree = all_uzel.front();  
}

//get path
void get_path(Node *tree, 
vector<bool> &path, 
map<char,vector<bool> > &path_liter){
	
	if (tree->left!=NULL) {
		path.push_back(0);
		get_path(tree->left,path, path_liter);
	}
     
    if (tree->right!=NULL){
		path.push_back(1);
		get_path(tree->right,path, path_liter);
	}
   
    if (tree->left==NULL && tree->right==NULL) path_liter[tree->c]=path;     
    
    path.pop_back();
}

//check liter - value
void check_path(map<char,vector<bool> > path_liter){
		map<char,vector<bool> >::iterator it;
		for(it = path_liter.begin();it != path_liter.end();it++){
			cout<<it->first<<" - ";
			for(bool i :it->second){
				cout<<i;
			}
			cout<<endl;
		}
}

//create message code
void get_ms_code(string user_input,
map<char,vector<bool> > path_liter
,vector <vector<bool> > &ms_code){
	for(int i = 0; i < user_input.size();i++){
		char liter = user_input[i];
		ms_code.push_back(path_liter[liter]);
	}
}

//get message
void get_ms(Node *tree,vector <vector<bool> > ms_code){
	for(vector<bool>  i : ms_code){
		Node *three = tree;
		
		for(bool j: i){
			if(j){
				three = three->right;
			} else if(!(j)){
				three = three->left;
			}
		}
		cout<<three->c;
	}
	cout<<endl;
}

//get code
void get_code(vector <vector<bool> > ms_code){
	
	for(vector<bool>  i : ms_code){
		for(bool j: i){
			cout<<j;
		}
		cout<<" ";
	}
	cout<<endl;
}

int start(Node *tree,vector <vector<bool> > ms_code, map<char,vector<bool> > path_liter){
		
		do{
		    
		int user_choice;
		cout<<"check liter code[1]\ncheck message code[2]\ncheck message[3]\ncreate new tree[4]\nexit[5]\n- ";
		cin>>user_choice;
		cin.ignore (7777, '\n');
		cout<<endl;
		
		if(user_choice == 1){
			check_path(path_liter);
			cout<<endl;
			
		}else if(user_choice == 2){	
			get_code(ms_code);
			cout<<endl;
			
		}else if(user_choice == 3){
			get_ms(tree,ms_code);
			cout<<endl;
			
		}else if(user_choice == 4){
			return 0;
			
		}else if(user_choice == 5){
			return 1;
			
		}else{
			    cin.clear();
			    cin.ignore(numeric_limits<streamsize>::max(), '\n');
			    cin.sync();
			}
			
			
	}while(true);
}

int main (){
	do{
		vector <vector<bool> > ms_code;
		vector<bool> path;                
		map<char,vector<bool> > path_liter;  
		Node *tree = NULL;
		string user_input;
		int x;
	
		get_tree(user_input,tree);
		get_path(tree,path,path_liter);   
		get_ms_code(user_input,path_liter,ms_code);
		x = start(tree,ms_code,path_liter);
		if(x == 1){
			break;}
	}while(true);

	return 0;
