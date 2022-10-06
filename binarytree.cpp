#include<bits/stdc++.h>
using namespace std;
template <typename T>
class binarytree{
    public:
    T data;
    binarytree<T> *left;
    binarytree<T> *right;
    binarytree(T data){
        this->data=data;
        left=NULL;
        right=NULL;
    }
    ~binarytree(){
        delete left;
        delete right;
    }
};
void printtree(binarytree<int> *root){
    if(root==NULL) return;
    queue<binarytree<int>*> q;
    q.push(root);
    while(q.size()!=0){
        binarytree<int> *front=q.front();
        q.pop();
        cout<<front->data<<" : ";
        if(front->left!=NULL) {cout<<"L"<<front->left->data<<",";
        q.push(front->left);}
        if(front->right!=NULL) {cout<<"R"<<front->right->data<<",";
        q.push(front->right);}
        cout<<endl;
    }
}

void mapping(unordered_map<int,int> &m, int in[],int n){
    for(int i=0;i<n;++i){
        m[in[i]]=i;
    }
}
binarytree<int> *inorder_to_preorder(int pr[], int in[], int inst, int inend, int prst,int n, unordered_map<int,int> &m){
    if(prst>=n || inst>inend) return NULL; 
    int rootindex=m[pr[prst]];
    binarytree<int> *root=new binarytree<int>(pr[prst]);
    root->left=inorder_to_preorder(pr,in,inst,rootindex-1,prst+1,n,m);
    root->right=inorder_to_preorder(pr,in,rootindex+1,inend,rootindex+prst+1-inst,n,m);
    return root;  
} 

void preorder(binarytree<int> *root){
    if(root==NULL) return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(binarytree<int> *root){
    if(root==NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
void inorder(binarytree<int> *root){
    if(root==NULL) return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int height(binarytree<int>* root){
    if(root==NULL) return 0;
    return 1+max(height(root->left),height(root->right));
}
int diameter(binarytree<int>* root){
    if(root==NULL) return 0;
    int ans=max(diameter(root->right),max(height(root->right)+height(root->right),diameter(root->left)));
    return ans;
}
/*int diameter_better(binarytree<int>* root){
     
}*/

binarytree<int> *takeinput(){
    int data;
    cout<<"Enter data" <<endl;
    cin>>data;
    if(data==-1) return NULL;
    
    binarytree<int> *root=new binarytree<int>(data);
    binarytree<int> *leftchild=takeinput();
    binarytree<int> *rightchild=takeinput();
    root->left=leftchild;
    root->right=rightchild;   
    return root;
}

binarytree<int> *takeinputlevelwise(){
    int data;
    cout<<"Enter data" <<endl;
    cin>>data;
    if(data==-1) return NULL;
    
    binarytree<int> *root=new binarytree<int>(data);
    queue<binarytree<int>*> q;
    q.push(root);
    while(q.size()!=0){
        binarytree<int>* front=q.front();
        q.pop();
        cout<<"Enter left child of "<<front->data<<":"<<endl;
        int leftchild;
        cin>>leftchild;
        if(leftchild!=-1){
            binarytree<int> *leftc=new binarytree<int>(leftchild);
            front->left=leftc;
            q.push(leftc);
        }
        cout<<"Enter right child of "<<front->data<<":"<<endl;
        int rightchild;
        cin>>rightchild;
        if(rightchild!=-1){
            binarytree<int> *rightc=new binarytree<int>(rightchild);
            front->right=rightc;
            q.push(rightc);
        }
    }
    return root;
}

binarytree<int>* pruneTree(binarytree<int>* root) {
        if(root==NULL) return NULL;
        binarytree<int>* l=pruneTree(root->left);
        binarytree<int>* r=pruneTree(root->right);
        cout<<l->data<<" "<<r->data<<endl;
        if(root->data==0 && l==NULL && r==NULL) root=NULL;
        return root;
}

int main(){
    #ifndef ONLINE_JUDGE
       freopen("input.txt", "r", stdin);
       freopen("output.txt", "w", stdout);
    #endif
    //1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1
    binarytree<int> * root;
     root=takeinputlevelwise();
     //printtree(root);
     //cout<<"-------------------"<<endl;
     root=pruneTree(root);
    // int n,in[20],pr[20],preind=0; cin>>n;
    // for(int i=0;i<n;i++) cin>>pr[i];
    // for(int i=0;i<n;i++) cin>>in[i];
    //unordered_map<int,int> m;
    //mapping(m,in,n);
    //root=inorder_to_preorder(pr,in,0,n-1,preind,n,m);
    printtree(root);
    //cout<<diameter(root);
} 



    // inorder(root);
    // cout<<endl;  
    // preorder(root);
    // cout<<endl;
    // postorder(root);