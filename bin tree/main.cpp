#include <iostream>

struct Node{
    int key;
    Node *lch = nullptr;
    Node *rch = nullptr;
    Node *parent = nullptr;
};

void Insert(Node *node, Node *x){
    while (node != nullptr) {
        if (x->key < node->key) {
            if (node->lch != nullptr)
                node = node->lch;
            else {
                x->parent = node;
                node->lch = x;
                break;
            }
        }
        else {
            if (node->rch != nullptr)
                node = node->rch;
            else {
                x->parent = node;
                node->rch = x;
                break;
            }
        }
    }
}

bool IsInTree(Node *node, int x){
    if (x == node->key)
        return true;
    if (x < node->key && node->lch != nullptr)
        return IsInTree(node->lch, x);
    else if (x > node->key && node->rch != nullptr)
        return IsInTree(node->rch, x);
    return false;
}

Node *Search(Node *node, int x){
    if (x < node->key && node->lch != nullptr)
        return Search(node->lch, x);
    else if (x > node->key && node->rch != nullptr)
        return Search(node->rch, x);
    return node;
}

Node *minimum(Node *node){
    if (node->lch == nullptr)
        return node;
    return minimum(node->lch);
}

Node *maximum(Node *node){
    if (node->rch == nullptr)
        return node;
    return maximum(node->rch);
}

Node *next(Node *node){
    if (node->rch != nullptr)
        return minimum(node->rch);
    if (node->parent != nullptr) {
        Node *isNext = node->parent;
        while (isNext != nullptr && node == isNext->rch) {
            node = isNext;
            isNext = isNext->parent;
        }
        return isNext;
    }
    else
        return node;
}

int next(Node *node, int x){
    node = minimum(node);
    while (node->key <= x)
        node = next(node);
    return node->key;
}

Node *prev(Node *node){
    if (node->lch != nullptr)
        return maximum(node->lch);
    if (node->parent != nullptr) {
        Node *isNext = node->parent;
        while (isNext != nullptr && node == isNext->lch) {
            node = isNext;
            isNext = isNext->parent;
        }
        return isNext;
    }
    else
        return node;
}

int prev(Node *node, int x){
    node = maximum(node);
    while (node->key >= x)
        node = prev(node);
    return node->key;
}

Node *Delete(Node *node, int x){
    Node  *DeleteNode = Search(node, x);
    if (DeleteNode->lch == nullptr && DeleteNode->rch == nullptr && DeleteNode->parent != nullptr){
        if (DeleteNode->parent->lch == DeleteNode)
            DeleteNode->parent->lch = nullptr;
        else
            DeleteNode->parent->rch = nullptr;
        DeleteNode->parent = nullptr;
        delete(DeleteNode);
    }
    else if (DeleteNode->lch == nullptr && DeleteNode->rch != nullptr && DeleteNode->parent != nullptr){
        DeleteNode->rch->parent = DeleteNode->parent;
        if (DeleteNode->parent->lch == DeleteNode)
            DeleteNode->parent->lch = DeleteNode->rch;
        else
            DeleteNode->parent->rch = DeleteNode->rch;
        DeleteNode->parent = nullptr;
        DeleteNode->rch = nullptr;
    }
    else if (DeleteNode->rch == nullptr && DeleteNode->lch != nullptr && DeleteNode->parent != nullptr){
        DeleteNode->lch->parent = DeleteNode->parent;
        if (DeleteNode->parent->lch == DeleteNode)
            DeleteNode->parent->lch = DeleteNode->lch;
        if (DeleteNode->parent->rch == DeleteNode)
            DeleteNode->parent->rch = DeleteNode->lch;
        DeleteNode->parent = nullptr;
        DeleteNode->lch = nullptr;
    }
    else if (DeleteNode->rch != nullptr && DeleteNode->lch != nullptr && DeleteNode->parent != nullptr){
        Node *new_node = next(DeleteNode);
        DeleteNode->key = new_node->key;
        if (new_node->parent->lch == new_node)
            new_node->parent->lch = new_node->rch;
        else
            new_node->parent->rch = new_node->rch;
        new_node->parent = nullptr;
        new_node->rch = nullptr;
    }
    else if (DeleteNode->parent == nullptr && DeleteNode->lch == nullptr && DeleteNode->rch != nullptr){
        Node *old = node;
        node = node->rch;
        node->parent = nullptr;
        old->rch = nullptr;
        delete(old);
    }
    else if (DeleteNode->parent == nullptr && DeleteNode->lch != nullptr && DeleteNode->rch == nullptr){
        Node *old = node;
        node = node->lch;
        node->parent = nullptr;
        old->lch = nullptr;
        delete(old);
    }
    else if (DeleteNode->parent == nullptr && DeleteNode->lch == nullptr && DeleteNode->rch == nullptr){
        node = nullptr;
    }
    else if (DeleteNode->parent == nullptr && DeleteNode->lch != nullptr && DeleteNode->rch != nullptr){
        Node *new_node = next(DeleteNode);
        DeleteNode->key = new_node->key;
        if (new_node->parent->lch == new_node)
            new_node->parent->lch = new_node->rch;
        else
            new_node->parent->rch = new_node->rch;
        new_node->parent = nullptr;
        new_node->rch = nullptr;
    }
    return node;
}

int main() {
    int SizeOfTree = 0;
    std::string option;
    int x;
    Node *root;
    while (std::cin >> option){
        if (option == "insert"){
            std::cin >> x;
            Node *new_node = new Node();
            new_node->key = x;
            if (SizeOfTree == 0) {
                root = new Node();
                root->key = x;
                SizeOfTree++;
            }
            if (SizeOfTree != 0 && !IsInTree(root, x)) {
                Insert(root, new_node);
                SizeOfTree++;
            }
        }
        else if (option == "exists"){
            std::cin >> x;
            if (SizeOfTree != 0 && IsInTree(root, x))
                std::cout << "true" << '\n';
            else
                std::cout << "false" << '\n';
        }
        else if (option == "delete"){
            std::cin >> x;
            if (SizeOfTree != 0 && IsInTree(root, x)) {
                root = Delete(root, x);
                SizeOfTree--;
            }
        }
        else if (option == "next"){
            std::cin >> x;
            if (SizeOfTree == 0 || maximum(root)->key <= x)
                std::cout << "none" << '\n';
            else
                std::cout << next(root, x) << '\n';
        }
        else if (option == "prev"){
            std::cin >> x;
            if (SizeOfTree == 0 || minimum(root)->key >= x)
                std::cout << "none" << '\n';
            else
                std::cout << prev(root, x) << '\n';
        }
    }
    return 0;
}
