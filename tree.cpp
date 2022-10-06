#include<bits/stdc++.h>
using namespace std;
template <typename T>
class treenode{
    public:
        T data;
        vector<treenode<T>*> children;
        treenode(T n){
            data=n;
        }
        /*~treenode(){
            for(int i=0;i<children.size();i++){
                delete children[i];
            }
        }*/
};

treenode<int> *input_queue(){   //levelwise input
    int data;
    cout<<"Enter data"<<endl;
    cin>>data;
    treenode<int>* root=new treenode<int>(data);
    queue<treenode<int>*> q;

    q.push(root);
    while(q.size()!=0){
        treenode<int>* front=q.front();
        q.pop();
        cout<<"Enter number of children of "<<front->data<<endl;
        int numchild;
        cin>>numchild;
        for(int i=0;i<numchild;i++){
            int childdata;
            cout<<"Enter "<<i<<"th child of "<<front->data<<endl;
            cin>>childdata;
            treenode<int> *child=new treenode<int>(childdata);
            front->children.push_back(child);
            q.push(child);
        }
    }
    return root;

}

treenode<int> *takeinput(){
    int data;
    cout<<"Enter data"<<endl;
    cin>>data;
    treenode<int>* root=new treenode<int>(data);

    int n;
    cout<<"Enter number of children of "<<data<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        treenode<int> *child=takeinput();
        root->children.push_back(child);
    }
    return root;
}

void printtree(treenode<int> *root){

    if(root==NULL) return;

    queue<treenode<int>*> q;
    q.push(root);
    while(q.size()!=0){
        treenode<int> *front=q.front();
        q.pop();
        cout<<front->data<<":";
        for(int i=0;i<front->children.size();i++){
            cout<<front->children[i]->data<<",";
            q.push(front->children[i]);
        }
        cout<<endl;
    }
}

int numofnodes(treenode<int>* root){
    int ans=1;
    for(int i=0;i<root->children.size();i++){
        ans+=numofnodes(root->children[i]);
    }
    return ans;
} 

int height(treenode<int> *root){
    int maxans=1,ans=1;
    for (int i = 0; i < root->children.size(); i++){
        ans=ans+height(root->children[i]);
        maxans=max(maxans,ans);
        ans=1;
    }
    return maxans;
}

void printlevel(treenode<int> *root,int k){
    if(root == NULL) return;
    if(k==0) {
        cout<<root->data<<", ";
    }
    for(int i=0;i<root->children.size();i++){
        printlevel(root->children[i],k-1);
    }
}

int leafnodes(treenode<int> *root){
    if(root->children.size()==0) return 1;
    int ans=0;
    for(int i=0;i<root->children.size();i++){
        ans=ans+leafnodes(root->children[i]);
    }
    return ans;
}

void postordertraversal(treenode<int>* root){
    for(int i=0;i<root->children.size();i++){
        postordertraversal(root->children[i]);
    }
    cout<<root->data<<" ";
}

int nodesgreaterthanx(treenode<int> *root, int k){
    int ans=0;
    for(int i=0;i<root->children.size();i++){
        /*if(root->children[i]->data > k) ans=ans+1+nodesgreaterthanx(root->children[i],k);
        else*/ 
        ans=ans+nodesgreaterthanx(root->children[i],k);

    }
    if(root->data>k) return ans=ans+1;;
    return ans;

}

treenode<int>* maxsum(treenode<int>* root){
    queue<treenode<int>*> q;
    q.push(root);
    treenode<int>* maxnode;
    int maxm=0;
        //cout<<"Sum "<<sum<<endl;
    while(q.size()!=0){
        int sum=0;
        treenode<int>* front;
        front=q.front();
        q.pop();
        for(int i=0;i<front->children.size();i++){
            sum+=front->children[i]->data;
            q.push(front->children[i]);
        }
        sum+=front->data;
        //cout<<"Sum "<<sum<<endl;
        if(sum>maxm){
            maxm=sum;
            maxnode=front;
        }
    }
    return maxnode;
}

treenode<int> *nextmax(treenode<int>* root, int n){
    treenode<int>* ans=NULL, *temp=NULL;
    if(root->data>n) ans=root;
    for(int i=0; i<root->children.size();i++){
        temp=nextmax(root->children[i],n);
        if(ans!=NULL){
            if(temp!=NULL &&  temp->data>n && temp->data < ans->data ){
                ans=temp;
            }
        }
        else{
            if(temp!=NULL && temp->data>n) ans=temp;
        }
    }
    //if(temp!=NULL && ans==NULL ) ans=temp;
    return ans;
}

/*treenode<int> *secmax(treenode<int>* root){
    treenode<int> *maxm=NULL, *secmaxm=NULL;
    if(maxm==NULL) maxm=root; 
    for(int i=0; i<root->children.size();i++){
        t
        if()
    }
    return secmaxm;
}*/


int main(){
   /* treenode<int> *root=new treenode<int>(1);
    treenode<int> root2(1); 
    treenode<int> *node1=new treenode<int>(2);
    treenode<int> *node2=new treenode<int>(3);
    root->children.push_back(node1);
    root->children.push_back(node2);*/
    #ifndef ONLINE_JUDGE
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
    #endif
    treenode<int> *root;
    int n;
    cin>>n;
    root=input_queue();
    //1 3 2 3 4 2 5 6 1 7 2 8 9 0 0 0 2 11 10 0 0 0
    //cout<<numofnodes(root)<<endl;
    //cout<<height(root);
    //printlevel(root,2);
    //cout<<leafnodes(root);
    //postordertraversal(root);
    //cout<<nodesgreaterthanx(root,2)<<endl;
    printtree(root);
   //delete root;
    //printtree(root);
    cout<<nextmax(root,n)->data;
}