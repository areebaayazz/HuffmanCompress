//: This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>
#include <iostream>
using namespace std;
#include <cstring>
#include <string>
#include <fstream>
string globStr;
int COUNTER = 8;

class Node {
private:
	int frequency;
	char data;
	Node* next;
	Node* right;
	Node* left;
public:
	Node() {
		frequency = 0;
		//not really have with this character but the previous choice failed somehow
		data = '~';
		next = NULL;
		left = NULL;
	}
	void setFrequency(int num) {
		frequency = num;
	}
	int getFrequency() {
		return(frequency);
	}
	void setData(char ch) {
		data = ch;
	}
	char getData() {
		return(data);
	}
	void setNext(Node* temp) {
		next = temp;
	}
	Node* getNext() {
		return(next);
	}
	void setRight(Node* temp) {
		right= temp;
	}
	Node* getRight() {
		return(right);
	}
	void setLeft(Node* temp) {
		left = temp;
	}
	Node* getLeft() {
		return(left);
	}
};

class LinkedList {
private:
	Node* root;
public:
	LinkedList() {
		root = NULL;
	}
	Node* getRoot() {
		return(root);
	}
	void insertion(char c) {
		Node* temp = new Node;
		temp->setData(c);
		temp->setFrequency(1);
		if (root == NULL) {
			root = temp;
		}
		else {
			Node* p = root;
			bool match = false;
			while (p->getNext() != NULL || p->getData() == temp->getData()) {
				if (p->getData() == temp->getData()) {
					match = true;
					p->setFrequency(p->getFrequency() + 1);
					break;
				}
				p = p->getNext();
			}
			if (match == false) {
				p->setNext(temp);
			}
		}
	}
	int loadFile(string fileName) {
		char c;
		ifstream file(fileName);
		if (!file.is_open()) {
			cout << "\nError! File does not exist!" << endl;
			return(0);
		}
		else {
			cout << "\nFile loaded successfully!" << endl;
			file >> c;
			while (!file.eof()) {
				insertion(c);
				file >> noskipws >> c;
			}
			file.close();
			return(1);
		}
	}
};

class Queue {
private:
	Node* start;
	Node* end;
public:
	Node* getStart() {
		return(start);
	}
	void enqueue(Node* t) {
		Node* temp = new Node;
		temp->setData (t->getData());
		temp->setFrequency(t->getFrequency());
		temp->setNext(NULL);
		temp->setLeft(t->getLeft());
		temp->setRight(t->getRight());
		if (start == NULL && end == NULL) {
			start = temp;
			end = temp;
		}
		else {
			Node* p = start;
			while (p->getNext() != NULL) {
				p = p->getNext();
			}
		p->setNext(temp);
		end = p->getNext();
		}
	}
	Node* dequeue() {
		Node* temp = start;
		if (start == NULL && end == NULL) {
			return(NULL);
		}
		if (start == end) {
			Node* temp = start;
			start = end = NULL;
			return(temp);
		}
		else if (start != NULL) {
			start = start->getNext();
			return(temp);
		}
	}
	int countQueue() {
		Node* p = start;
		int count=0;
		while (p != NULL) {
			count++;
			p = p->getNext();
		}
		return(count);
	}
	void sortQueueToPriority() {
		Node* p = start;
		Node* c = start;
		Node* n = start;
		/*
		while (p != NULL) {
			cout << p->getData() << "-" << p->getFrequency() << ",";
			p=p->getNext();
		}
		*/
		if (countQueue() == 1) {
			return;
		}
		while (c != NULL) {
			if (c == start)
				p = c;
			n = c->getNext();
			if (n == NULL)
				break;
			if (c->getFrequency() > n->getFrequency()) {
				//only 2 elements
				if (c == start && n == end) {
					start = n;
					end = c;
					end->setNext(NULL);
					start->setNext(end);
					break;
				}
				else if (c != start && n == end) {
					end = c;
					p->setNext(n);
					end->setNext(NULL);
					n->setNext(c);
				}
				else if (c == start && n != end) {
					Node* temp= n->getNext();
					start = n;
					start->setNext(c);
					c->setNext(temp);
				}
				else if (c != start && n != end) {
					Node* temp = n->getNext();
					p->setNext(n);
					n->setNext(c);
					c->setNext(temp);
				}
				c = start;
			}
			else {
				p = c;
				c = c->getNext();
			}
		}
	}
	void printQueue() {
		cout << "\nQUEUE: ";
		Node* p = start;
		while (p != NULL) {
			cout << p->getData() << "-" << p->getFrequency() << ",";
			p = p->getNext();
		}
		cout << endl;
	}
};

class Tree {
private:
	Node* root;
public:
	Node* getRoot() {
		return(root);
	}
	void insert(Queue q, int type) {
		//check for 1 character in queue needed
		Node* temp = new Node;
		Node* a = q.dequeue();
		Node* b = q.dequeue();
		temp->setFrequency(a->getFrequency() + b->getFrequency());
		if (a->getData() != '~') {
			a->setRight(NULL);
			a->setLeft(NULL);
		}
		if (b->getData() != '~') {
			b->setRight(NULL);
			b->setLeft(NULL);
		}
		if (a->getData() > b->getData()) {
			temp->setRight(a);
			temp->setLeft(b);
		}
		else {
			temp->setRight(b);
			temp->setLeft(a);
		}
		q.enqueue(temp);
		q.sortQueueToPriority();
		while (q.countQueue() >1) {
			temp = new Node;
			a = q.dequeue();
			if (a->getData() != '~') {
				a->setRight(NULL);
				a->setLeft(NULL);
			}
			b = q.dequeue();
			if (b->getData() != '~') {
				b->setRight(NULL);
				b->setLeft(NULL);
			}
			temp->setFrequency(a->getFrequency() + b->getFrequency());
			temp->setRight(b);
			temp->setLeft(a);
			q.enqueue(temp);
			q.sortQueueToPriority();
		}
		root = q.dequeue();
	}
	void printValues(Node * tempNode, int space, int type){
			if (tempNode == NULL)
				return;
			space += COUNTER;
			printValues(tempNode->getRight(), space, type);
			cout << endl;
			for (int i = COUNTER; i < space; i++)
				cout << " ";
			if (type==1) {
				if (tempNode->getData() == '~') {
					cout << "NULL" << "\n";
				}
				else
					cout << tempNode->getData() << "\n";
			}
			else {
				if (tempNode->getData() == '~') {
					cout << tempNode->getFrequency() << "\n";
				}
				else
					cout << tempNode->getData() << "\n";
			}
			printValues(tempNode->getLeft(), space, type);
		}
	void encode(Node* t, string str,char ch) {
		if (t->getLeft() == NULL && t->getRight() == NULL&&t->getData()==ch) {
			cout << str;
			return;
		}
		else {
			if (t->getLeft() != NULL) {
				encode(t->getLeft(), str + "0", ch);
			}
			if (t->getRight() != NULL) {
				encode(t->getRight(), str + "1",ch);
			}
		}
	}
	void decode(string sentence) {
		int counter = 0;
		Node* p = root;
		cout << "\nWarning: All wrong codes will be discarded in decoding process! :)\nThe Decoded Message is: ";
		while (counter != sentence.length()) {
			if (sentence[counter] == '1' && p->getData() == '~' && p->getRight() != NULL) {
				p = p->getRight();
				if (p->getData() != '~' && p->getLeft() == NULL && p->getRight() == NULL) {
					cout << p->getData();
					p = root;
				}
			}
			else if (sentence[counter] == '0' && p->getData() == '~' && p->getLeft() != NULL){
				p = p->getLeft();
				if (p->getData() != '~' && p->getLeft() == NULL && p->getRight() == NULL) {
					cout << p->getData();
					p = root;
				}
			}
			else if (p->getData() != '~' && p->getLeft() == NULL && p->getRight() == NULL) {
				cout << p->getData();
				p = root;
			}
			counter++;
		}
	}
	void printTable(Node* t, string str) {
		if (t->getLeft() == NULL && t->getRight() == NULL) {
			cout << "\n" << t->getData() << "   " << str;
			return;
		}
		else {
			if (t->getLeft() != NULL) {
				printTable(t->getLeft(),str+"0");
			}
			if (t->getRight() != NULL) {
				printTable(t->getRight(), str + "1");
			}
		}
	}
	void encodeForCompression(Node* t, string str, char ch) {
		if (t->getLeft() == NULL && t->getRight() == NULL && t->getData() == ch) {
			globStr = str;
			return;
		}
		else {
			if (t->getLeft() != NULL) {
				encodeForCompression(t->getLeft(), str + "0", ch);
			}
			if (t->getRight() != NULL) {
				encodeForCompression(t->getRight(), str + "1", ch);
			}
		}
	}
	void compressionRatio(string text, int N) {
		float ABR=0;
		int count = 0;
		string str = "";
		LinkedList templl;
		while (count != text.length()) {
			templl.insertion(text[count]);
			count++;
		}
		Node* p = templl.getRoot();
		while (p != NULL) {
			encodeForCompression(root, str, p->getData());
			ABR=ABR+p->getFrequency()*globStr.length();
			globStr = "";
			str = "";
			p = p->getNext();
		}
		ABR = ABR / N;
		cout << 8 / ABR << endl;
	}
};
class HuffmanCode {
private:
	string text;
	LinkedList ll;
	Queue q;
	Tree tS, tO; //Tree Simple, Tree Optimized
	float textFile8BitCR;
public:
	string readFile(string fileName) {
			string c;
			ifstream file(fileName);
			if (!file.is_open()) {
				cout << "\nError! File does not exist!" << endl;
			}
			else {
				getline(file, c);
				file.close();
				return(c);
			}
	}
	int  saveFileToLinkedList(string filename) {
		if (ll.loadFile(filename) == 1) {
			text = readFile(filename);
			textFile8BitCR = 0;
			Node* x = ll.getRoot();
			while (x != NULL) {
				textFile8BitCR = textFile8BitCR + x->getFrequency() * 8;
				x =x->getNext();
			}
			textFile8BitCR = textFile8BitCR / text.length();
			textFile8BitCR = 8 / textFile8BitCR;
			saveFileToQueue();
			return(1);
		}
		else 
			return(0);
	}
	void saveFileToQueue() {
		Node* temp = ll.getRoot();
		while (q.countQueue() != 0) {
			q.dequeue();
		}
		while (temp != NULL) {
			q.enqueue(temp);
			temp = temp->getNext();
		}
		q.sortQueueToPriority();
		temp = ll.getRoot();
		//reset linked list frequencies to 1
		while (temp != NULL) {
			temp->setFrequency(1);
			temp = temp->getNext();
		}
	}
	void huffmanCodeSimple() {
		saveFileToQueue();
		tS.insert(q, 1);
	}
	void optimizedHuffmanCodeSimple() {
		tO.insert(q, 2);
	}
	void PrintTrees(int num) {
		if (num == 1) {
			cout << "\nThe SIMPLE Huffman Tree for this data Looks like: ";
			tS.printValues(tS.getRoot(), 0, 1);
		}
		else {
			cout << "\nThe OPTIMIZED Huffman Tree for this data Looks like: ";
			tO.printValues(tO.getRoot(), 0, 2);
		}
		}
	void decodeMessage(string sentence, int num) {
		if (num == 1)
			tS.decode(sentence);
		else
			tO.decode(sentence);
	}
	void encodeMessage(string sentence, int num) {
		string temp = "";
		bool error = false;
		int counter = 0;
		//validation checks
		while (counter != sentence.length()) {
			if (text.find(sentence[counter]) == string::npos) {	
				error = true;
				break;
			}
			counter++;
		}
		counter = 0;
		if (error == false) {
		if (num == 1) {
			cout << "\nYour Encoded Message is: ";
			while (counter != sentence.length()) {
				tS.encode(tS.getRoot(), temp, sentence[counter]);
				counter++;
			}
		}
		else {
			cout << "\nYour Encoded Message is: ";
			while (counter != sentence.length()) {
				tO.encode(tO.getRoot(), temp, sentence[counter]);
				counter++;
			}
		}
		}
		if (error == true) {
			cout << "\nYou've entered a character that is not saved in the Database. Try changing the text file!" << endl;
		}
	}
	void printAllValues(int num) {
		string temp = "";
		if (num == 1) {
			cout << "\nCodes for Simple Huffman Tree: \n";
			tS.printTable(tS.getRoot(), temp);
		}
		else {
			cout << "\nCodes for Optimized Huffman Tree: \n";
			tO.printTable(tO.getRoot(), temp);
		}
	}
	void calculateCompression(int num) {
		if (num == 1) {
			cout << "\nThe compression Ratio is: ";
			cout << textFile8BitCR;
			cout << "\nThis is because the file is not compressed and uses all 8 bits! So, the ratio is 1 to 1." << endl;
		}
		else if (num == 2) {
			cout << "\nThe compression Ratio is: ";
			tS.compressionRatio(text,text.length());
		}
		else if (num == 3) {
			cout << "\nThe compression Ratio is: ";
			tO.compressionRatio(text,text.length());
		}
	}
	void printASCII() {
		string word;
		int count = 0;
		ifstream file("ASCII.txt");
		if (!file.is_open()) {
			cout << "\nError! File does not exist!" << endl;
		}
		else {
			cout << "\n";
			cout << "     ";
			file >> word;
			cout << word;
			file >> word;
			cout << "  ";
			cout << word;
			cout << "    ";
			file >> word;
			cout << word;
			file >> word;
			cout << "  ";
			cout << word;
			cout << "    ";
			count++;
			count++;
			while (file >> word) {
				cout << word;
				file >> word;
				cout << "  ";
				cout << word;
				count++;
				if (count == 4) {
					cout << endl;
					count = 0;
				}
				cout << "     ";
			}
			file.close();
		}
	}
	void encodeASCII(string sentence) {
		cout << "\nYour Encoded Message is: ";
		string word[100];
		char ch[100];
		int count = 0;
		ifstream file("ASCII.txt");
		if (!file.is_open()) {
			cout << "\nError! File does not exist!" << endl;
		}
		else {
			file >> word[count];
			file >> ch[count];
			count++;

			file >> word[count];
			file >> ch[count];
			count++;

			while (file >> word[count]) {
				file >> ch[count];
				count++;
			}
			file.close();
		}
		cout << "\n";
		int counter1 = 0;
		int counter2 = 0;
		while (counter1 != sentence.length()) {
			counter2 = 0;
			while (counter2!=count) {
				if (ch[counter2] == sentence[counter1])
					cout << word[counter2];
				counter2++;
			}
			counter1++;
		}
		cout << endl;
	}
};
int main()
{
	cout << "\nWELCOME TO DS PROJECT - HUFFMAN ENCODING!\n";
    HuffmanCode hc;
	LinkedList ll1;
	string fName, sWord, sentence;
	cout << "\nEnter file name: ";
	cin >> fName;
	int opt=11, tempID;
	string tempURL;
	if (hc.saveFileToLinkedList(fName) == 0) {
		do {
			cout << "\nRe-enter: ";
			cin >> fName;
		} while (hc.saveFileToLinkedList(fName) == 0);
	}
	hc.optimizedHuffmanCodeSimple();
	hc.huffmanCodeSimple();
	cout << "\n" << endl;
	cout << "          ___________" << endl;
	cout << "	 |.---------.|" << endl;
	cout << "	 ||         ||" << endl;
	cout << "	 ||  10101  ||" << endl;
	cout << "	 ||         ||" << endl;
	cout << "         |'---------'|" << endl;
	cout << "	  `)_______('" << endl;
	cout << "	  [== = ---o]--." << endl;
	cout << "        __'---------'__ \\" << endl;
	cout << "       [::::::::::: :::] )" << endl;
	cout << "	 `'''''''''''''`/T\\" << endl;
	cout << "	                \\_/" << endl;
	cout << "\n Press: \n0. Print ASCII table \n1. To convert data to ASCII\n2. Print Simple Huffman Tree for the File\n3. Print Optimized Huffman Tree for the File\n4. Print all codes for Simple Huffman Tree\n5. Print all codes for Optimized Huffman Tree\n6. Calculate Compression Ratios\n7. Encode Messaging using Simple Huffman Tree\n8. Encode Messaging using Optimized Huffman Tree\n9. Decode Messaging using Simple Huffman Tree\n10. Decode Messaging using Optimized Huffman Tree\n-1. To EXIT!\nEnter: ";
	cin >> opt;
	system("CLS");
	while (opt != -1) {
		
		if (opt == 0) {
			hc.printASCII();
		}
		else if (opt == 1) {
			cout << "\nEnter a line to Encode: ";
			cin >> sentence;
			hc.encodeASCII(sentence);
		}
		else if (opt == 2) {
			hc.PrintTrees(1);
		}
		else if (opt == 3) {
			hc.PrintTrees(2);
		}
		else if (opt == 4) {
			hc.printAllValues(1);
		}
		else if (opt == 5) {
			hc.printAllValues(2);
		}
		else if (opt == 6) {
			int choice;
			cout << "\n Press:\n1. for 8 Bit\n2. for Simple Huffman Code\n3. for Optimized Huffman Code\n4. Any other key to EXIT..\nEnter: ";
			cin >> choice;
			hc.calculateCompression(choice);
		}
		else if (opt == 7) {
			cout << "\nEnter a line to Encode: ";
			cin >> sentence;
			hc.encodeMessage(sentence, 1);
		}
		else if (opt == 8) {
			cout << "\nEnter a line to Encode: ";
			cin >> sentence;
			hc.encodeMessage(sentence, 2);
		}
		else if (opt == 9) {
			cout << "\nEnter a line to Decode: ";
			cin >> sentence;
			hc.decodeMessage(sentence, 1);
		}
		else if (opt == 10) {
			cout << "\nEnter a line to Decode: ";
			cin >> sentence;
			hc.decodeMessage(sentence, 2);
		}
		else if (opt == -1) {
			break;
		}
		else 
			cout << "\nWELCOME TO DS PROJECT - HUFFMAN ENCODING!\n\nFile has already been loaded successfully!" << endl;
		cout << "\n" << endl;
		cout << "          ___________" << endl;
		cout << "	 |.---------.|" << endl;
		cout << "	 ||         ||" << endl;
		cout << "	 ||  10101  ||" << endl;
		cout << "	 ||         ||" << endl;
		cout << "         |'---------'|" << endl;
		cout << "	  `)_______('" << endl;
		cout << "	  [== = ---o]--." << endl;
		cout << "        __'---------'__ \\" << endl;
		cout << "       [::::::::::: :::] )" << endl;
		cout << "	 `'''''''''''''`/T\\" << endl;
		cout << "	                \\_/" << endl;
		cout << "\n Press: \n0. Print ASCII table \n1. To convert data to ASCII\n2. Print Simple Huffman Tree for the File\n3. Print Optimized Huffman Tree for the File\n4. Print all codes for Simple Huffman Tree\n5. Print all codes for Optimized Huffman Tree\n6. Calculate Compression Ratios\n7. Encode Messaging using Simple Huffman Tree\n8. Encode Messaging using Optimized Huffman Tree\n9. Decode Messaging using Simple Huffman Tree\n10. Decode Messaging using Optimized Huffman Tree\n-1. To EXIT!\nEnter: ";
		cin >> opt;
		system("CLS");
		if (opt!=-1)
			cout << "\nWELCOME TO DS PROJECT - HUFFMAN ENCODING!\n\nFile has already been loaded successfully!" << endl;
	}
	cout << "\n\n\n\n             Thank you!\n\n\n\n" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    