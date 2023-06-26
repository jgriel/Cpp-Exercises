#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLEBLACK 2

#include <string>
#include <vector>

using namespace std;

struct RBTNode{
    int data;
    unsigned short int color;
    RBTNode *left = nullptr;
    RBTNode *right = nullptr;
    RBTNode *parent = nullptr;
    bool isNullNode = false;
};

class RedBlackTree {
    public:
        RedBlackTree();                                 
        RedBlackTree(const RedBlackTree& origObject);
        ~RedBlackTree();                                

        void Insert(int num);
        void Remove(int num);                           
        bool Contains(int num);                         
        int GetMin();                                   
        int GetMax();                                   
        int Size();                                     

        string ToInfixString() const {return ToInfixString(root);};
        string ToPrefixString() const {return ToPrefixString(root);};
        string ToPostfixString() const {return ToPostfixString(root);};

    private:
        string ToInfixString(RBTNode* root) const;      
        string ToPrefixString(RBTNode* root) const;     
        string ToPostfixString(RBTNode* root) const;    
        bool isLeaf(RBTNode* node) const;               
        bool isNodeLeft(RBTNode* node);                 
        void rotateRR(RBTNode* node);                   
        void rotateRL(RBTNode* node);                   
        void rotateLL(RBTNode* node);                   
        void rotateLR(RBTNode* node);                          
        void recolor(RBTNode* node);  
        bool isUncleBlack(RBTNode* node);
        string nodeToString(RBTNode* node)const;
        void copyHelper(RBTNode* parent, RBTNode* copyThis, short pos); 
        RBTNode* findIOS(RBTNode* start);
        void fixDoubleBlack(RBTNode* node);
        void deconstructorHelper(RBTNode* node);                           
        unsigned long long int numItems;
        RBTNode *root;
};
#endif