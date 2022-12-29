#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

typedef Node * Tree;

void init(Tree &t) {
    t = NULL;
}

void insertNode(Tree &t, int x) {
    Node *p = new Node;
    if (p == NULL) {
        cout << "Full memory!";
        exit(1);
    }
    else {
        p->data = x;
        p->left = p->right = NULL;
        t = p;
    }
}

void addNodeToTree(Tree &t, int x) {
    if (t == NULL) {
        insertNode(t, x);
    }
    else {
        if (t->data > x) addNodeToTree(t->left, x);
        else if (t->data < x) addNodeToTree(t->right, x);
        else cout << "The data has existed!";
    }
}



void printLNR(Tree t) {
    if (t == NULL) return;
    else {
        printLNR(t->left);
        cout << t->data << " ";
        printLNR(t->right);
    }
}

void deleteNode(Tree &t, int x) {
    Node *p, *q;
    p = t; q = NULL;
    //
    while (p != NULL && p->data != x) {
        q = p;
        if (p->data > x) {
            p = p->left;
        }
        else if (p->data < x) {
            p = p->right;
        }
    }
    if (p != NULL && p != t) {
        //delete node leaf:
        if (p->left == NULL && p->right == NULL) {
            if (q->left == p) q->left = NULL;
            else if (q->right == p) q->right = NULL;
        }


        //delete node with one child
        else if ((p->left != NULL && p->right == NULL) || (p->left == NULL && p->right != NULL)) {
            if (q->left == p) {
                if (p->left != NULL && p->right == NULL) {
                    q->left = p->left;
                }
                else if (p->left == NULL && p->right != NULL) {
                    q->left = p->right;
                }
            }
            else if (q->right == p) {
                if (p->left != NULL && p->right == NULL) {
                    q->right = p->left;
                }
                else if (p->left == NULL && p->right != NULL) {
                    q->right = p->right;
                }
            }
        }

        //delete node with two childrens
        else {
            if (q->right == p) {
               q->right = p->right;
               Node *temp = p->right;
               while (temp->left != NULL) temp = temp->left;
               temp->left = p->left;
            }
            else if (q->left == p) {
                q->left = p->right;
                Node *temp = p->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }
                temp->left = p->left;
            }
        }
        delete p;
    }
    else if (p == t) {
        if (p->left != NULL && p->right == NULL) {
            t = p->left;
        }
        else if (p->left == NULL && p->right != NULL) {
            t = p->right;
        }
        else if (p->left == NULL && p->right == NULL) {
            t = NULL;
        }
        else {
            t = t->right;
            Node *temp = p->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            temp->left = p->left;
        }
        delete p;
    }
    else {
        cout << "\n\t\t The node is unexist!\n";
    }
}


void inputFile(Tree &t) {
    FILE *fp = fopen("input.txt", "r");
    int x;
    if (fp == NULL)
    {
        printf("\nCan not open the file");
        return;
    }
    while (!feof(fp))
    {
        if (fscanf(fp ,"%d", &x) > 0) addNodeToTree(t, x);
    }
    printf("\nCompleted!\n");
    fclose(fp);
}

void menu() {
    cout << "\n===============MENU==============\n";
    cout << "1. Input data from file\n";
    cout << "2. Input data from keyboard\n";
    cout << "3. Print all of nodes\n";
    cout << "4. Delete one node from the tree\n";
    cout << "Please enter a number: ";
}
int main() {
    int choose;
    Tree t;
    init(t);
    do {
        menu();
        cin >> choose;
        if (choose == 1) {
            inputFile(t);
            printLNR(t);
        }
        else if (choose == 2) {
            cout << "\n\t\t- Input data: ";
            int x; cin >> x;
            addNodeToTree(t, x);
        }
        else if (choose == 3) printLNR(t);
        else if (choose == 4) {
            cout << "\n\t\t- Input the data of node which you want to delete: ";
            int n; cin >> n;
            deleteNode(t, n);
            printLNR(t);
        }
    } while (choose != 0);
}