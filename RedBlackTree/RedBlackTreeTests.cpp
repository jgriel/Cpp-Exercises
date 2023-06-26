
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt->ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30); 
	rbt->Insert(15);
	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Left Right
	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(50); // Right Right
	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B45  R30  R50 ");
	delete rbt;

	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(40); // Right Left
	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B40  R30  R45 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(10);
	rbt->Insert(30);
	rbt->Insert(45);
	cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  B10  B30  R45 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(10);
	rbt->Insert(30);
	rbt->Insert(40);
	rbt->Insert(45);
	cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  B10  B40  R30  R45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(10);
	rbt->Insert(30);
	rbt->Insert(8);
	rbt->Insert(9);
	cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  B9  R8  R10  B30 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	cout << "Pre :" << rbt.ToPrefixString() << endl;
	cout << "In  :" << rbt.ToInfixString() << endl;
	cout << "Post:" << rbt.ToPostfixString() << endl;

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor1(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);
	cout << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);;
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}


void TestContains(){
	cout << "Testing Contains..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(!rbt->Contains(33));
	delete rbt;

	cout << "PASSED!" << endl << endl;
}




void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);

	assert(rbt->GetMin() == 12);
	assert(rbt->GetMax() == 55);
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestEdges(){
	cout << "Testing Edges    " << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(40);
	rbt->Insert(55);
	rbt->Insert(10);
	rbt->Insert(17);
	rbt->Insert(31);
	rbt->Insert(12);
	rbt->Insert(29);
	rbt->Insert(34);
	rbt->Insert(9);
	rbt->Insert(8);

	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B22  B15  R10  B9  R8  B12  B17  B40  B31  R29  R34  B55 ");
	delete rbt;


	cout << endl << "shitty test  " << endl << endl;
	rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(10);
	rbt->Insert(30);
	rbt->Insert(5);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(50);
	rbt->Insert(40);
	rbt->Insert(55);
	cout << "Inserting Last " << endl;
	rbt->Insert(60);

	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  R15  B10  R5  R13  B20  R50  B40  B55  R60 ");
	delete rbt;
}

void TestWrong(){
	cout << "Testing Wrong   " << endl << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(100);
	rbt->Insert(3);
	rbt->Insert(50);
	rbt->Insert(40);
	rbt->Insert(4);
	rbt->Insert(49);
	rbt->Insert(7);
	rbt->Insert(8);

	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B40  R4  B3  B7  R8  R50  B49  B100 ");

	delete rbt;
}

void TestInsertWithRecursiveFixUp(){
	cout << "Testing Recursive FixUp..." << endl;
	// Red uncle, and we "move the blackness up"
	// the makes the grandparent red and that might cause issues
	// at the grand-parent level.
	// This may repeat until the root node (which must be black)
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(400);
	rbt->Insert(800);
	rbt->Insert(200);
	rbt->Insert(600);
	rbt->Insert(150);
	rbt->Insert(900);
	rbt->Insert(300);
	rbt->Insert(100);
	rbt->Insert(175);
	rbt->Insert(160); // does some weird stuff!
	cout << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B200  R150  B100  B175  R160  R400  B300  B800  R600  R900 ");
	rbt->Insert(185);
	rbt->Insert(180); // does a recursive fix-up
	assert(rbt->ToPrefixString() == " B200  B150  B100  R175  B160  B185  R180  B400  B300  B800  R600  R900 ");
	cout << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);
	
	assert(rbt1.Size() == rbt2.Size());
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());


	RedBlackTree rbt3 = RedBlackTree();
	rbt3.Insert(12);
	rbt3.Insert(10);
	rbt3.Insert(0);
	rbt3.Insert(11);
	rbt3.Insert(3);
	rbt3.Insert(9);
	rbt3.Insert(2);
	rbt3.Insert(7);
	rbt3.Insert(1);
	rbt3.Insert(4);
	rbt3.Insert(6);
	rbt3.Insert(8);
	rbt3.Insert(37);
	rbt3.Insert(5);
	rbt3.Insert(72);
	rbt3.Insert(55);
	rbt3.Insert(90);
	rbt3.Insert(92);
	rbt3.Insert(20);
	rbt3.Insert(13);
	rbt3.Insert(57);
	rbt3.Insert(30);
	rbt3.Insert(64);
	rbt3.Insert(69);
	rbt3.Insert(50);
	rbt3.Insert(67);
	rbt3.Insert(99);
	rbt3.Insert(89);
	rbt3.Insert(33);

	assert(rbt3.ToPrefixString() == " B12  R7  B3  B1  R0  R2  B5  R4  R6  B10  B9  R8  B11  R55  B20  B13  R37  B30  R33  B50  B69  R64  B57  B67  R90  B72  R89  B92  R99 ");

	RedBlackTree rbt4 = RedBlackTree(rbt3);

	string s3 = rbt3.ToPrefixString();
	//cout << "s3: " << s3 << endl;
	string s4 = rbt4.ToPrefixString();
	//cout << "s4: " << s4 << endl;
	assert(rbt3.Size() == rbt4.Size());
	assert(s3 == s4);


	rbt3.Insert(200);
	assert(rbt3.ToPrefixString() != rbt4.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}


void TestRemove(){
	cout << "Testing Remove..." << endl;


	RedBlackTree* rbt = new RedBlackTree();
	rbt->Insert(1);
	rbt->Insert(0);
	rbt->Insert(2);
	rbt->Remove(1);

	cout << rbt->ToPrefixString() << endl << endl;
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(50);
	rbt->Insert(100);
	rbt->Insert(10);
	rbt->Insert(75);
	rbt->Remove(50);
	rbt->Insert(0);
	rbt->Remove(10);
	rbt->Insert(850);
	rbt->Insert(900);
	rbt->Remove(0);

	assert(rbt->ToPrefixString() == " B850  B75  R100  B900 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(75);
	rbt->Insert(0);
	rbt->Insert(850);
	rbt->Insert(100);
	rbt->Remove(0);
	rbt->Insert(85);
	rbt->Remove(850);

	assert(rbt->ToPrefixString() == " B85  B75  B100 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(100);
	rbt->Insert(12);
	rbt->Insert(780);
	rbt->Insert(1);
	rbt->Insert(400);
	rbt->Insert(54);
	rbt->Insert(800);
	rbt->Insert(543);
	rbt->Remove(543);
	rbt->Remove(400);

	assert(rbt->ToPrefixString() == " B100  B12  R1  R54  B780  R800 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(100);
	rbt->Insert(12);
	rbt->Insert(780);
	rbt->Insert(1);
	rbt->Insert(400);
	rbt->Insert(54);
	rbt->Insert(800);
	rbt->Insert(543);
	rbt->Remove(1);
	rbt->Remove(54);
	rbt->Remove(12);
	rbt->Remove(800);

	assert(rbt->ToPrefixString() == " B400  B100  B780  R543 ");
	delete rbt;
	
	
	rbt = new RedBlackTree();
	rbt->Insert(100);
	rbt->Insert(12);
	rbt->Insert(780);
	rbt->Insert(1);
	rbt->Insert(400);
	rbt->Remove(100);
	rbt->Insert(54);
	rbt->Remove(12);
	rbt->Insert(800);
	rbt->Remove(780);
	rbt->Insert(543);
	rbt->Insert(48);
	rbt->Remove(1);
	rbt->Insert(430);
	rbt->Remove(400);
	rbt->Remove(54);
	rbt->Remove(800);
	rbt->Remove(543);
	rbt->Remove(48);
	rbt->Remove(430);

	assert(rbt->ToPrefixString() == "");
	assert(rbt->Size() == 0);
	delete rbt;


}


int main(){

	TestSimpleConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();
	TestToStrings();
	TestInsertRandomTests();
	TestCopyConstructor1();
	TestContains();
	TestGetMinimumMaximum();
	TestEdges();
	TestWrong();
	TestInsertWithRecursiveFixUp();
	TestCopyConstructor();

	TestRemove();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
