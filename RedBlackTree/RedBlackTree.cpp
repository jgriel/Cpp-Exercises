#include "RedBlackTree.h"
#include <iostream>

using namespace std;

//Regular Constuctor
RedBlackTree::RedBlackTree(){
    root = nullptr;
    numItems = 0;
}

//Copy Constructor
RedBlackTree::RedBlackTree(const RedBlackTree& origObject){
    //instantiate
    root = nullptr;
    numItems = 0;
    //empty tree case
    if(origObject.root == nullptr){
        return;
    }else{
        //take care of root
        RBTNode* newRoot = new RBTNode;
        newRoot->data = origObject.root->data;
        newRoot->color = origObject.root->color;
        root = newRoot;
        numItems++;

        //recurse into children
        if(origObject.root->left != nullptr){
            copyHelper(newRoot, origObject.root->left, 0);
        }
        if(origObject.root->right != nullptr){
            copyHelper(newRoot, origObject.root->right, 1);
        }

    }
}

//Deconstructor
RedBlackTree::~RedBlackTree(){
    if(root == nullptr){
        return;
    }
    deconstructorHelper(root);
}

//Insert
void RedBlackTree::Insert(int num){
    //If tree is empty
    if(root == nullptr){
        RBTNode* node = new RBTNode;
        node->data = num;
        node->color = COLOR_BLACK;
        root = node;
        numItems++;
        return;
    }

    //Check if item is already in tree
    if(this->Contains(num)){
        throw invalid_argument("Number already contained in tree!");
    }

    //Initialize node to be added
    numItems++;
    RBTNode* node = new RBTNode;
    node->data = num;
    node->color = COLOR_RED;
   
   //Get to bottom of tree
    RBTNode* curNode = root;
    while(curNode != nullptr){
        if(num > curNode->data && curNode->right != nullptr){
            curNode = curNode->right;
        
        }else if(num < curNode->data && curNode-> left != nullptr){
            curNode = curNode->left;
        
        }else if(num > curNode->data){
            curNode->right = node;
            node->parent = curNode;
            curNode = nullptr;
            
        }else if(num < curNode->data){
            curNode->left = node;
            node->parent = curNode;
            curNode = nullptr;
        }
    }
    //Step 3
    if(node->parent->color == COLOR_BLACK){
        return;
    }else{
        //PARENT ON LEFT
        if(isNodeLeft(node->parent)){
            //UNCLE BLACK
            if(node->parent->parent->right == nullptr || node->parent->parent->right->color == COLOR_BLACK){
                //NODE LEFT (LL)
                if(isNodeLeft(node)){
                    rotateLL(node->parent);
                }
                //NODE RIGHT (LR)
                else{
                    rotateLR(node);
                    rotateLL(node);
                }
            }
            //UNCLE RED
            else{
                recolor(node);
            }
        }
        //PARENT ON RIGHT
        else{
            //UNCLE BLACK
            if(node->parent->parent->left == nullptr || node->parent->parent->left->color == COLOR_BLACK){
                //NODE RIGHT (RR)
                if(!isNodeLeft(node)){
                    rotateRR(node->parent);
                }
                //NODE LEFT (RL)
                else{
                    rotateRL(node);
                    rotateRR(node);
                }
            }
            //UNCLE RED
            else{
                recolor(node);
            }
        }
    }

}

//Remove
void RedBlackTree::Remove(int num){
    //Contains Check
    if (!Contains(num)){
        throw invalid_argument("Number does not exist in tree!");
    }
    //Find Node toDelete
    RBTNode* curNode = root;
    while(curNode->data != num){
        if(num < curNode->data){
            curNode = curNode->left;
        }
        else if(num > curNode->data){
            curNode = curNode->right;
        }
    }   
    RBTNode* toDelete = curNode;
    RBTNode* Replacement = root;

    //Find Replacement and implement BSTRemove ideas
    //No Children
    if(isLeaf(toDelete)){
        //Root case
        if(toDelete == root){
            root = nullptr;
            numItems--;
            delete toDelete;
            return;
        }
        //Create null node
        Replacement = new RBTNode();
        Replacement->color = COLOR_BLACK;
        Replacement->isNullNode = true;
        Replacement->parent = toDelete->parent;
        if(isNodeLeft(toDelete)){
            toDelete->parent->left = Replacement;
        }else{
            toDelete->parent->right = Replacement;
        }
    }
    //One Child
    else if((toDelete->left != nullptr && toDelete->right == nullptr) || (toDelete->left == nullptr && toDelete->right != nullptr)){
        if(toDelete->left != nullptr){
            Replacement = toDelete->left; 
        }else{
            Replacement = toDelete->right;
        }
        if(toDelete == root){
            root = Replacement;
            Replacement->parent = nullptr;
        }else{
            Replacement->parent = toDelete->parent;
            if(isNodeLeft(toDelete)){
                Replacement->parent->left = Replacement;
            }else{
                Replacement->parent->right = Replacement;
            }    
        }
        
    }
    //Two children
    else if (toDelete->left != nullptr && toDelete->right != nullptr){
        Replacement = findIOS(toDelete);
        int num = Replacement->data;
        Remove(num);
        toDelete->data = num;
        return;
    }

    //Four base cases
    //Root Case
    if(root == Replacement){
        Replacement->color = COLOR_BLACK;
    }
    //D is Red
    else if(toDelete->color == COLOR_RED){
        Replacement->color = COLOR_BLACK;
    }
    //R is Red
    else if(Replacement->color == COLOR_RED){
        Replacement->color = COLOR_BLACK;
    }
    //D and R are Black
    else if(toDelete->color == COLOR_BLACK && Replacement->color == COLOR_BLACK){
        Replacement->color = COLOR_DOUBLEBLACK;
        fixDoubleBlack(Replacement);
    }

    //Delete null node 
    if(Replacement->isNullNode){
        if(isNodeLeft(Replacement)){
            Replacement->parent->left = nullptr;
        }else{
            Replacement->parent->right = nullptr;
        }
        delete Replacement;
    }

    numItems--;
    delete toDelete;
}

//GetMax
int RedBlackTree::GetMax(){
    //Edge case: empty boi
    if(root == nullptr){
        throw logic_error("Tree is empty");
    }
    //Edge case: single boi
    if(isLeaf(root)){
        return root->data;
    }
    //Work way down right of tree
    RBTNode* curNode = root;
    int min;
    while(curNode != nullptr){
        if(curNode->right == nullptr){
            min = curNode->data;
            curNode = nullptr;
        }
        //To the Right! To the Right! To the Right! To the Right!
        else{
            curNode = curNode->right;
        }
    }
    return min;

}

//GetMin
int RedBlackTree::GetMin(){
    //Edge case: empty boi
    if(root == nullptr){
        throw logic_error("Tree is empty");
    }
    //Edge case: single boi
    if(isLeaf(root)){
        return root->data;
    }
    //Work way down left of tree
    RBTNode* curNode = root;
    int max;
    while(curNode != nullptr){
        if(curNode->left == nullptr){
            max = curNode->data;
            curNode = nullptr;
        }
        //To the Left! To the Left! To the Left! To the Left!
        else{
            curNode = curNode->left;
        }
    }
    return max;
}

//Contains
bool RedBlackTree::Contains(int num){
    //Edge case: empty boi
    if(root == nullptr){
        return false;
    }
    //Edge case: OnlyRoot
    if(isLeaf(root)){
        return num == root->data;
    }
    //Otherwise follow path down tree
    RBTNode* curNode = root;
    while(curNode != nullptr){
        //Now Kick! Now Kick! Now Kick! Now Kick!
        if(num == curNode->data){
            return true;
        }else if(num > curNode->data && curNode->right == nullptr){
            curNode = nullptr;
        }else if(num < curNode->data && curNode->left == nullptr){
            curNode = nullptr;
        }else if(num < curNode->data){
            curNode = curNode->left;
        }else if(num > curNode->data){
            curNode = curNode->right;
        }
    }
    //Now walk it by yourself! Now walk it by yourself!!
    return false;
}

//Size
int RedBlackTree::Size(){
    return numItems;
}

//ToInfixString
string RedBlackTree::ToInfixString(RBTNode* root)const{
    //Edge case: you guessed it, empty boi
    if(root == nullptr){
        return "";
    }

    string str = "";
    //Recurse Left
    if(root->left != nullptr){
        str += ToInfixString(root->left);
    }

    //Add the "middle" to the string
    str += " ";
    str += nodeToString(root);

    //Recurse right
    if(root->right != nullptr){
        str += ToInfixString(root->right);
    }

    return str;
}

string RedBlackTree::ToPrefixString(RBTNode* root)const{
    //Edge case: empty boi
    if(root == nullptr){
        return "";
    }

    string str = " ";
    //Add the "pre" to the string
    str += nodeToString(root);

    //Recurse Left
    if(root->left != nullptr){
        str += ToPrefixString(root->left);
    }

    //Recurse Right
    if(root->right != nullptr){
        str += ToPrefixString(root->right);
    }

    return str;
}

string RedBlackTree::ToPostfixString(RBTNode* root)const{
    //Edge case: empty boi
    if(root == nullptr){
        return "";
    }

    string str = "";
    //Recurse Left
    if(root->left != nullptr){
        str += ToPostfixString(root->left);
    }

    //Recurse Right
    if(root->right != nullptr){
        str += ToPostfixString(root->right);
    }

    //Add the "Post" to the string
    str += " ";
    str += nodeToString(root);

    return str;
}

//isLeaf
bool RedBlackTree::isLeaf(RBTNode* node)const{
    return node->right == nullptr && node->left == nullptr;
}

//isNodeLeft
//Because if it ain't left, it's right!
bool RedBlackTree::isNodeLeft(RBTNode* node){
    return node->parent->left == node;
}

//rotateRR
void RedBlackTree::rotateRR(RBTNode* node){
    RBTNode* parent = node->parent;
    
    if(node->left != nullptr){
        parent->right = node->left;
        node->left->parent = parent;
    }else{
        parent->right = nullptr;
    }
    node->left = parent;
    if(parent->parent != nullptr){
        RBTNode* grandP = parent->parent;
        node->parent = grandP;
        if(!isNodeLeft(parent)){
            grandP->right = node;  
        }else{
            grandP->left = node; 
        }
    }
    else{
        node->parent = nullptr;
        root = node;
    }
    parent->parent = node;
    parent->color = COLOR_RED;
    node->color = COLOR_BLACK;
}

//rotateRL
void RedBlackTree::rotateRL(RBTNode* node){
    RBTNode* parent = node->parent;
    RBTNode* grandP = parent->parent;
    node->parent = grandP;
    grandP->right = node;
    if(node->right !=nullptr){
        parent->left = node->right;
        node->right->parent = parent;
    }else{
        parent->left = nullptr;
    }
    node->right = parent;
    parent->parent = node;
}

//rotateLL
void RedBlackTree::rotateLL(RBTNode* node){
    RBTNode* parent = node->parent;

    if(node->right != nullptr){
        parent->left = node->right;
        node->right->parent = parent;
    }else{
        parent->left = nullptr;
    }
    node->right = parent;
    if(parent->parent != nullptr){
        RBTNode* grandP = parent->parent;
        node->parent = grandP;
        if(!isNodeLeft(parent)){
            grandP->right = node;  
        }else{
            grandP->left = node; 
        }
    }
    else{
        node->parent = nullptr;
        root = node;
    }
    parent->parent = node;
    parent->color = COLOR_RED;
    node->color = COLOR_BLACK;

}

//rotateLR
void RedBlackTree::rotateLR(RBTNode* node){
    RBTNode* parent = node->parent;
    RBTNode* grandP = parent->parent;
    node->parent = grandP;
    grandP->left = node;
    if(node->left !=nullptr){
        parent->right = node->left;
        node->left->parent = parent;
    }else{
        parent->right = nullptr;
    }
    node->left = parent;
    parent->parent = node;
}

//recolor
void RedBlackTree::recolor(RBTNode* node){ 
    RBTNode* parent = node->parent;
    RBTNode* grandP = node->parent->parent;
    if(node->parent->color == COLOR_BLACK){
        return;
    }
    else if (isUncleBlack(node)){
        //Parent Left
        if(isNodeLeft(parent)){
            //Node Left (LL)
            if(isNodeLeft(node)){
                rotateLL(parent);
            }
            //Node Right (LR)
            else{
                rotateLR(node);
                rotateLL(node);
            }
        }
        //Parent Right 
        else{
            //Node Left (RL)
            if(isNodeLeft(node)){
                rotateRL(node);
                rotateRR(node);
            }
            //Node Right (RR)
            else{
                rotateRR(parent);
            }
        }
    }else{      
        parent->color = COLOR_BLACK;
        grandP->color = COLOR_RED;
        //Say uncle! Say uncle!
        if(isNodeLeft(parent)){
            grandP->right->color = COLOR_BLACK;
        }else{
            grandP->left->color = COLOR_BLACK;
        }
        //Stop if grandaddy the root
        if(grandP == root){
            root->color = COLOR_BLACK;
        }
        //Otherwise recurse
        else if (grandP->parent->parent != nullptr){
            recolor(grandP);
        }
    }
}

//isUncleBlack
bool RedBlackTree::isUncleBlack(RBTNode* node){
    RBTNode* parent = node->parent;
    RBTNode* grandP = node->parent->parent;

    if(isNodeLeft(parent)){
        return grandP->right->color == COLOR_BLACK;
    }else{
        return grandP->left->color == COLOR_BLACK;
    }
}

//nodeToString
string RedBlackTree::nodeToString(RBTNode* node)const{
    string str = "";
    if(node->color == COLOR_BLACK){
            str.push_back('B');
        }else{
            str.push_back('R');
        }
        str.append(to_string(node->data));
        str.append(" ");
        return str;
}

//copyHelper
void RedBlackTree::copyHelper(RBTNode* parent, RBTNode* copyThis, short pos){
    //copy data
    RBTNode* tmp = new RBTNode;
    tmp->color = copyThis->color;
    tmp->data = copyThis->data;
    tmp->parent = parent;
    if(pos == 0){
        parent->left = tmp;
    }else{
        parent->right = tmp;
    }
    numItems++;

    //recurse into children
    if(copyThis->left != nullptr){
        copyHelper(tmp, copyThis->left, 0);
    }

    if(copyThis->right != nullptr){
        copyHelper(tmp, copyThis->right, 1);
    }
}

//findIOS
RBTNode* RedBlackTree::findIOS(RBTNode* start){
    RBTNode* ios = start->right;
    while(ios->left != nullptr){
        ios = ios->left;
    }
    return ios;
}

//fixDoubleBlack
void RedBlackTree::fixDoubleBlack(RBTNode* node){
    //root case
    if(root == node){
        root->color = COLOR_BLACK;
        return;
    }
    
    RBTNode* sibling = node;
    if(isNodeLeft(node)){
        sibling = node->parent->right;
    }else{
        sibling = node->parent->left;
    }
    //SIBLING BLACK
    if(sibling->color == COLOR_BLACK){
        //Sibling all black children
        if((sibling->left == nullptr || sibling->left->color == COLOR_BLACK) && (sibling->right == nullptr || sibling->right->color == COLOR_BLACK)){
            sibling->color = COLOR_RED;
            node->color = COLOR_BLACK;
            if(node->parent->color == COLOR_RED){
                node->parent->color = COLOR_BLACK;
            }else{
                node->parent->color = COLOR_DOUBLEBLACK;
                fixDoubleBlack(node->parent);
            }
        }
        //Sibling has a red child
        else if((sibling->left != nullptr && sibling->left->color == COLOR_RED) || (sibling->right != nullptr && sibling->right->color == COLOR_RED)){
            //Sibling left, left red child or two red children
            if(isNodeLeft(sibling) && (sibling->left != nullptr && sibling->left->color == COLOR_RED)){
                RBTNode* sibParent = sibling->parent;
                unsigned short int parentColor = sibParent->color;
                rotateLL(sibling);
                sibling->left->color = COLOR_BLACK;
                sibling->color = parentColor;
                sibParent->color = COLOR_BLACK;
                node->color = COLOR_BLACK; 
            }
            //Sibling left, single red right child
            else if(isNodeLeft(sibling) && (sibling->left == nullptr && sibling->right->color == COLOR_RED)){
                RBTNode* sibParent = sibling->parent;
                RBTNode* sibChild = sibling->right;
                rotateLR(sibChild);
                rotateLL(sibChild);
                sibChild->color = COLOR_BLACK;
                sibParent->color = COLOR_BLACK;
                node->color = COLOR_BLACK;
            }
            //Sibling right, right red child or two red children
            else if(!isNodeLeft(sibling) && (sibling->right != nullptr && sibling->right->color == COLOR_RED)){
                RBTNode* sibParent = sibling->parent;
                unsigned short int parentColor = sibParent->color;
                rotateRR(sibling);
                sibling->right->color = COLOR_BLACK;
                sibling->color = parentColor;
                sibParent->color = COLOR_BLACK;
                node->color = COLOR_BLACK;
            }
            //Sibling right, single red left child
            else if(!isNodeLeft(sibling) && (sibling->right == nullptr && sibling->left->color == COLOR_RED)){
                RBTNode* sibParent = sibling->parent;
                RBTNode* sibChild = sibling->left;
                rotateRL(sibChild);
                rotateRR(sibChild);
                sibChild->color = COLOR_BLACK;
                sibParent->color = COLOR_BLACK;
                node->color = COLOR_BLACK;
            }  
        }
    }
    //SIBLING RED
    else if(sibling->color == COLOR_RED){
        //Sibling left
        if(isNodeLeft(sibling)){
            rotateLL(sibling);
        }
        //Sibling right
        else{
            rotateRR(sibling);
        }
        fixDoubleBlack(node);
    }
}

//deconstructorHelper
void RedBlackTree::deconstructorHelper(RBTNode* node){
    //recurse into children if applicable
    if(node->left != nullptr){
        deconstructorHelper(node->left);
    }
    if(node->right != nullptr){
        deconstructorHelper(node->right);
    }
    //postfix delete
    delete node;
}
