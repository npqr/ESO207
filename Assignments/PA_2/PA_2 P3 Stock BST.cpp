/* PA_2 P3 Stock BST */
/* Name : Nevish Pathe */
/* Roll No. 220757*/
/* Handle : npqrrr */

#include <iostream>
#include <cstdlib>

using namespace std;
typedef long long int ll;

/* BST Implementation with Auxiliary Functions*/
struct BST {
    struct node {
        ll data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(ll x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(ll x, node* t) {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    node* find(node* t, ll x) {
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
            return find(t->right, x);
        else
            return t;
    }

    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(ll x) {
        root = insert(x, root);
    }

    void remove(ll x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    void search(ll x) {
        node* k = find(root, x);
        if(k == nullptr) cout << "NO\n";
        else if (k->data == x)
        cout << "YES\n";
    }
};

void StockStuff() {
    int D;
    cin >> D;

    BST portfolio;
    while(D--)
    {
        char c;
        ll x;
        cin >> c >> x;
        // cout << " char : " << c << " num : " << x << " \n";
        if(c == 'B')
            {
            // cout << "BB!\n";
            portfolio.insert(x);}
        else if(c == 'S'){
            // cout << "sus!\n";
            portfolio.remove(x);
           }
        else if (c == 'R'){
            // cout << "rooor!\n";
            portfolio.search(x);}
        // b.display();
    }
    return;
}

int main(){
    StockStuff();

    return 0;
}