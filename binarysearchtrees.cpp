#include<bits/stdc++.h>
using namespace std;
template<typename T>
class bst{
    public:
    T data;
    bst<T>* left;
    bst<T>* right;
    bst<T>* root=NULL;
    bst(T data){
        this->data=data;
        left=NULL;
        right=NULL;
    }
    bst(bst<T>* root){
        this->root=root;
    }
    ~bst(){
        delete left;
        delete right;
    }

    private:
        bst<T> *deletedata(T n, bst<T> *root){
            if(root==NULL) return NULL;
            if(n>root->data){
                root->right=deletedata(n,root->right);
                return root;
            }
            else if(n<root->data){
                root->left=deletedata(n,root->left); 
                return root;
            }
            else{
                if(root->left==NULL && root->right==NULL){
                    delete root;
                    return NULL;
                }
                else if(root->right==NULL){
                    bst<int> *temp=root->left;
                    root->left=NULL;
                    delete root;
                    return temp;
                }
                else if(root->left==NULL){
                    bst<int> *temp=root->right;
                    root->right=NULL;
                    delete root;
                    return temp;
                }
                else{
                    bst<int> *minnode=root->right;
                    while(minnode->left!=NULL){
                        minnode=minnode->left;
                    }
                    T rightmin=minnode->data;
                    root->data=rightmin;
                    root->right=deletedata(rightmin,root->right);
                    return root;
                } 
            }
        }
    public:
        void deletedata(int n){
            root=deletedata(n,root);
        }
    private:
        bst<T>* insert(int n,bst<T>* root){
            if(root==NULL){
                bst<T> *newroot= new bst<T>(n);
                return newroot; 
            }
            if(n<root->data){
                root->left=insert(n,root->left);
            }
            else{
                root->right=insert(n,root->right);
            }
            return root;
        }
    public:
        void insert(int n){
            this->root=insert(n,this->root); 
        }

    private:
        bool hasData(T n, bst<T>* root){
            if(root==NULL) return false;
            if(root->data==n) return true;
            else if(n<root->data) return hasData(n,root->left);
            else return hasData(n,root->right);
        }
    public:
        bool hasData(T n){
            return hasData(n,root);
        }
        bst<int> *updated(){
            return root;
        }
};

template<typename T>
class Node{
    public:
        T data;
        Node<T> *next;
        Node(T n){
            data=n;
            this->next=NULL;
        }
};
void printll(Node<int> *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
    cout<<endl;
}
Node<int> *bst_to_ll(bst<int> *root){
    if(root==NULL) return NULL;
    Node<int> *leftll=bst_to_ll(root->left);
    Node<int> *head=new Node<int>(root->data);
    Node<int> *temp=leftll;
    if(temp==NULL){
        temp=head;
    }
    else{
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=head;
    }
    Node<int> *rightll=bst_to_ll(root->right);
    head->next=rightll;
    if(leftll!=NULL) head=leftll;
    return head;
}

bool binarysearcht(bst<int>* root, int n){
    if(root==NULL) return 0;
    if(root->data==n) return 1;
    if(root->data>n) return binarysearcht(root->left,n);
    if(root->data<n) return binarysearcht(root->right,n);
    return 0;
}

void printtree(bst<int> *root){
    if(root==NULL) return;
    queue<bst<int>*> q;
    q.push(root);
    while(q.size()!=0){
        bst<int> *front=q.front();
        q.pop();
        cout<<front->data<<" : ";
        if(front->left!=NULL) {cout<<"L"<<front->left->data<<",";
        q.push(front->left);}
        if(front->right!=NULL) {cout<<"R"<<front->right->data<<",";
        q.push(front->right);}
        cout<<endl;
    }
}

bst<int> *constructbst(vector<int> a, int start, int end){
    if(start>end) return NULL;
    int mid=end-(end-start)/2;
    bst<int> *root=new bst<int>(a[mid]);
    root->left=constructbst(a,start,mid-1);
    root->right=constructbst(a,mid+1,end);
    return root;
}

vector<int> root_to_node(bst<int> *root, int n){
    vector<int> v;
    if(root == NULL) return v;
    if(root->data==n){
        v.push_back(n);
        return v;
    }
    //we check for left first, if the vector returned is of size zero, then we check on
    //the right side
    v=root_to_node(root->left,n);  
    if(v.size()!=0){
        v.push_back(root->data); 
    }
    else{
        v=root_to_node(root->right,n);
        if(v.size()!=0){
            v.push_back(root->data);
        }
    }
    return v;
}

int maximum(bst<int>* root){
    if(root==NULL) return INT_MIN;
    int ans=root->data;
    ans=max(ans,max(maximum(root->left),maximum(root->right)));
    return ans;
}
int minimum(bst<int>* root){
    if(root==NULL) return INT_MAX;
    int ans=root->data;
    ans=min(ans,min(minimum(root->left),minimum(root->right)));
    return ans;
}
bool isBST(bst<int> *root){
    if(root==NULL) return 1;
    if((root->data>maximum(root->left)) && (root->data<=minimum(root->right)) && isBST(root->left) && isBST(root->right)) return 1;
    else return 0;
}

class is_BST{
    public:
    bool isbst;
    int maxm;
    int minm;
};
is_BST isBST2(bst<int> *root){
    if(root==NULL){
        is_BST opt;
        opt.isbst=true;
        opt.maxm=INT_MIN;
        opt.minm=INT_MAX;
        return opt;
    }
    is_BST leftopt=isBST2(root->left);
    is_BST rightopt=isBST2(root->right);
    int minm=min(root->data,min(leftopt.minm,rightopt.minm));
    int maxm=max(root->data,max(leftopt.maxm,rightopt.maxm));
    bool isbstfinal=(root->data>leftopt.maxm) && (root->data<=rightopt.minm) && leftopt.isbst && rightopt.isbst;
    is_BST opt;
    opt.isbst=isbstfinal;
    opt.maxm=maxm;
    opt.minm=minm;
    return opt;
}

void printelementsinrange(bst<int> *root,int n1,int n2){
    if(root==NULL) return;
    if(n1>root->data) printelementsinrange(root->right,n1,n2);
    else if(n2<root->data) printelementsinrange(root->left,n1,n2);
    else{
        printelementsinrange(root->left,n1,n2);
        cout<<root->data<<" ";
        printelementsinrange(root->right,n1,n2);
    }
}

bst<int>* takeinput(){
    int n;
    cout<<"Enter data" <<endl;
    cin>>n;
    if(n==-1) return NULL;
    bst<int> *root=new bst<int>(n);
    queue<bst<int>*> q;
    q.push(root);
    while(q.size()){
        bst<int> *front=q.front();
        q.pop();
        cout<<"Enter left child of "<<front->data<<":"<<endl;
        int k;
        cin>>k;
        if(k!=-1){
            bst<int> *leftc=new bst<int>(k);
            front->left=leftc;
            q.push(leftc);
        }
        cout<<"Enter right child of "<<front->data<<":"<<endl;
        cin>>k;
        if(k!=-1){
            bst<int> *rightc=new bst<int>(k);
            front->right=rightc;
            q.push(rightc);
        }
    }
    return root; 
}

int main(){
    //4 2 6 1 3 5 7 -1 -1 -1 -1 -1 -1 -1 -1 bst
    //1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1 binary tree
    #ifndef ONLINE_JUDGE
       freopen("input.txt", "r", stdin);
       freopen("output.txt", "w", stdout);
    #endif
    bst<int> *root=NULL;
    //root=takeinput();
    bst<int> b(root);
    b.insert(10);
    b.insert(20);
    b.insert(5);
    b.insert(3);
    b.insert(7);
    b.insert(0);
    b.insert(8);
    root=b.updated();
    printtree(root);
    cout<<"Updated"<<endl;
    b.deletedata(10);
    root=b.updated();
    printtree(root);
    b.deletedata(5);
    root=b.updated();
    printtree(root);
    //cout<<b.hasData(7);
    //cout<<endl;
    // vector<int> v;
    // v=root_to_node(root,9);
    // for(auto i:v) cout<<i<<" ";
    // cout<<endl;
    //vector<int> a={0,1,2,3,4,5,6,7,8};
    //root=constructbst(a,0,a.size()-1);
    //Node<int> *head=bst_to_ll(root);
    //printll(head);
    //cout<<isBST(root);
    //int k1,k2; cin>>k1>>k2;
    //printelementsinrange(root,k1,k2);
    /*if(binarysearcht(root,k)) cout<<"true"<<endl;
    else cout<<"false"<<endl;*/
}