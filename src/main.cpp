#include <iostream>
#pragma once
using namespace std;
#include <string>

class Node {
public:
    string name;
    string ufid;
    int height;
    string Node_name;
    string Node_ufid;
    Node* left;
    Node* right;
    Node(string name, string ufid) : Node_name(name), Node_ufid(ufid), height (0), left(nullptr), right(nullptr){}
};

class AVLTree{
private:
    Node* MinFIND_Helper(Node* data_node) {
        while (data_node->left) {
            data_node = data_node->left;
        }
        return data_node;
    }

    int BalanceCounter_Helper(Node* tree_node){
        if (tree_node == nullptr){
            return 0;
        }
        return (tree_node->left ? tree_node->left->height : 0) - (tree_node->right ? tree_node->right->height : 0);
    }
    Node* RightRotation_Helper(Node* tree_node){
        Node* Temp = tree_node->left;
        Node* tree_nodeRight = Temp->right;

        // Perform rotation
        Temp->right = tree_node;
        tree_node->left = tree_nodeRight;

        // Update heights
        tree_node->height = 1 + max((tree_node->left ? tree_node->left->height : 0),(tree_node->right ? tree_node->right->height : 0));
        Temp->height = 1 + max((Temp->left ? Temp->left->height : 0),(Temp->right ? Temp->right->height : 0));

        return Temp;
    };
    Node* LeftRotation_Helper(Node* tree_node){
        Node* temp = tree_node->right;
        Node* tree_nodeLeft = temp->left;

        // Perform rotation
        temp->left = tree_node;
        tree_node->right = tree_nodeLeft;

        // Update heights
        tree_node->height = 1 + max((tree_node->left ? tree_node->left->height : 0),(tree_node->right ? tree_node->right->height : 0));
        temp->height = 1 + max((temp->left ? temp->left->height : 0),(temp->right ? temp->right->height : 0));

        return temp;
    };
    Node* InsertHelper(Node* tree_root, string name, string ufid){
        if (tree_root == nullptr){
            cout << "successful" << endl;
            return new Node(name, ufid);
        }
        else{
            int ufid_num = stoi(ufid);
            int tree_node_num = stoi(tree_root->Node_ufid);
            if (ufid_num < tree_node_num){
                tree_root->left = InsertHelper(tree_root->left, name, ufid);
            }
            else if (ufid_num > tree_node_num){
                tree_root->right = InsertHelper(tree_root->right, name, ufid);
            }
        }
        tree_root->height = 1 + max(tree_root->left ? tree_root->left->height : 0, tree_root->right ? tree_root->right->height: 0);
        int balance_counter = 0;
        balance_counter = BalanceCounter_Helper(tree_root);
        if (balance_counter > 1 && stoi(ufid) < stoi(tree_root->left->Node_ufid)) {
            return RightRotation_Helper(tree_root);
        }
        if (balance_counter < -1 && stoi(ufid) > stoi(tree_root->right->Node_ufid)) {
            return LeftRotation_Helper(tree_root);
        }
        if (balance_counter > 1 && stoi(ufid) > stoi(tree_root->left->Node_ufid)) {
            tree_root->left = LeftRotation_Helper(tree_root->left);
            return RightRotation_Helper(tree_root);
        }
        if (balance_counter < -1 && stoi(ufid) < stoi(tree_root->right->Node_ufid)) {
            tree_root->right = RightRotation_Helper(tree_root->right);
            return LeftRotation_Helper(tree_root);
        }

        return tree_root;
    }
    Node* Remove_Helper(Node* tree_root, string ufid_text){
        if (tree_root == nullptr){
            cout << "Unsuccessful" << endl;
            return tree_root;
        }
        if (stoi(ufid_text) < stoi(tree_root->Node_ufid)){
            tree_root->left = Remove_Helper(tree_root->left, ufid_text);
        }
        else if (stoi(ufid_text) > stoi(tree_root->Node_ufid)){
            tree_root->right = Remove_Helper(tree_root->right, ufid_text);
        }
        else{
            if (tree_root->left == nullptr) {
                Node* temp_Node = tree_root->right;
                delete tree_root;
                cout << "successful" << endl;
                return temp_Node;
            }
            else if (tree_root->right == nullptr) {
                Node* temp_Node = tree_root->left;
                delete tree_root;
                cout << "successful" << endl;
                return temp_Node;
            }
            else{
                Node* tempNode = MinFIND_Helper(tree_root->right);
                tree_root->Node_name = tempNode->Node_name;
                tree_root->Node_ufid = tempNode->Node_ufid;
                tree_root->right = Remove_Helper(tree_root->right, tempNode->Node_ufid);
                return tree_root;
            }
        }
        return tree_root;
    }
    Node* SearchID_Helper(Node* tree_root, string ufid_text){
        if (stoi(ufid_text) < stoi(tree_root->Node_ufid)){
            tree_root->left = SearchID_Helper(tree_root->left, ufid_text);
        }
        else if (stoi(ufid_text) > stoi(tree_root->Node_ufid)){
            tree_root->right = SearchID_Helper(tree_root->right, ufid_text);
        }
        else if (stoi(ufid_text) == stoi(tree_root->Node_ufid)){
            cout << tree_root->Node_name << endl;
        }
        else{
            cout << "unsuccessful" << endl;
        }
    }
    void PreorderTraversal_Name_Helper(Node* root_node,string UF_name_string){
        if (root_node == nullptr) {
            return;
        }
        if (UF_name_string == root_node->Node_name){
            cout << root_node->Node_ufid << endl;
        }
        PreorderTraversal_Name_Helper(root_node->left, UF_name_string);
        PreorderTraversal_Name_Helper(root_node->right, UF_name_string);
    }
    void SearchName_Helper(Node* tree_root, string UF_Name){
        PreorderTraversal_Name_Helper(tree_root, UF_Name);
    }
    void printPostOrder_Helper(Node* tree_node){
        if (tree_node == nullptr) {
            return;
        }
        printPostOrder_Helper(tree_node->left);
        printPostOrder_Helper(tree_node->right);
        if (tree_node->right == nullptr) {
            cout << tree_node->Node_name << ", ";
        }
        else if (tree_node->left == nullptr){
            cout << tree_node->Node_name << ", ";
        }
        else if (tree_node->left == nullptr && tree_node->right == nullptr){
            cout << tree_node->Node_name << ", ";
        }
        else{
            cout << tree_node->Node_name << endl;
        }
    }
    void printPreOrder_helper(Node* tree_node){
        if (tree_node == nullptr) {
            return;
        }
        cout << tree_node->Node_name;

        if (tree_node->left != nullptr) {
            cout << ", ";
            printPreOrder_helper(tree_node->left);
        }
        if (tree_node->right != nullptr) {
            cout << ", ";
            printPreOrder_helper(tree_node->right);
        }
    }
    void printInorder_Helper(Node* tree_node){
        if (tree_node == nullptr){
            return;
        }

        printInorder_Helper(tree_node->left);
        if (tree_node->left != nullptr) {
            cout << ", ";
        }
        cout << tree_node->Node_name;
        if (tree_node->right != nullptr){
            cout << ", ";
        }
        printInorder_Helper(tree_node->right);
    }
    int printLevelcount_helper(Node* tree_node){
        if (tree_node == nullptr) {
            return 0;
        }
        int left_levels = printLevelcount_helper(tree_node->left);
        int right_levels = printLevelcount_helper(tree_node->right);
        int levels = max(left_levels, right_levels) + 1;
        if (tree_node == root){
            cout << levels << endl;
        }
        return levels;
    }
    Node* removeInorderN_Helper(Node* tree_node, int Node, int& current){
        if (tree_node == nullptr){
            return nullptr;
        }
        tree_node->left = removeInorderN_Helper(tree_node->left, Node, current);
        if (Node == current) {
            this->root = Remove_Helper(this->root, tree_node->Node_ufid);
            return tree_node->left;
        }
        else{
            current += 1;
        }
        tree_node->right = removeInorderN_Helper(tree_node->right, Node,current);
        return tree_node;
    }
public:
    Node* root;
    void Insert(string name, int ufid) {
        string I_ufid = to_string(ufid);
        this->root = InsertHelper(this->root, name, I_ufid);
    }
    void Remove(int ufid){
        string ufid_string = to_string(ufid);
        Remove_Helper(this->root, ufid_string);
    }
    void SearchID(string ufid){
        this->root = SearchID_Helper(this->root, ufid);
    }
    void Search_Name(string UF_Name){
        SearchName_Helper(this->root, UF_Name);
    }
    void printPostorder(){
        printPostOrder_Helper(this->root);
    }
    void printPreorder(){
        printPreOrder_helper(this->root);
        cout << endl;
    }
    void printInorder(){
        printInorder_Helper(this->root);
        cout << endl;
    }
    void printLevelCount(){
        printLevelcount_helper(this->root);
    }
    void removeInorderN(int N){
        int current = 0;
        this->root = removeInorderN_Helper(this->root, N, current);
        if (current != N){
            cout << "Unsuccessful" << endl;
        }
    }
    AVLTree() : root() {}
};
/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main(){
	return 0;
}

