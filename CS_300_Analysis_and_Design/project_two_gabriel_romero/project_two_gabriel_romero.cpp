// project_two_gabriel_romero.cpp : This file contains the 'main' function. Program execution begins and ends there.
// CS300
// Project two
// Module 7
// Author:  Gabriel Luis Romero
// Date:    06/15/2022

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Implementing Course Struct
struct Course {
    string number;
    string description;
    vector<string> prerequesites;

    // Implemented for removal of struct from vector
    friend bool operator==(const Course& lhs, const Course& rhs) {
        return lhs.number == rhs.number && lhs.description == rhs.description && lhs.prerequesites == rhs.prerequesites;
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    void destructTree(Node* node);
    Node* removeNode(Node* node, string courseNumber);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course);
    void Remove(string courseNumber);
    Course Search(string courseNumber);
    void InOrder();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    this->destructTree(root);
}

void BinarySearchTree::destructTree(Node* node) {
    if (node) {
        destructTree(node->left);
        destructTree(node->right);
        delete node;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root '
    this->inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    else {
        // else
            // add Node root and course
        this->addNode(root, course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseNumber) {
    // remove node root courseNumber
    this->removeNode(root, courseNumber);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNumber) {
    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching courseNumber found
    while (current != nullptr) {
        // if match found, return current course
        if (current->course.number.compare(courseNumber) == 0) {
            return current->course;
        }
        // if course is smaller than current node then traverse left
        if (courseNumber.compare(current->course.number) < 0) {
            current = current->left;
        }
        else {
            // else larger so traverse right
            current = current->right;
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.number.compare(course.number) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        else {
            // else recurse down the left node
            this->addNode(node->left, course);
        }
    }
    else {
        // else
            // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
            //else
        }
        else {
            // recurse down the left node
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //inorder not left
        inOrder(node->left);
        // course output 
        cout << "*****************************************" << endl;
        cout << "Course Number: " << node->course.number << endl;
        cout << "Course Description: " << node->course.description << endl;
        cout << "Course Prerequisites: " << endl;
        for (string i : node->course.prerequesites) {
            cout << "\t\t\t" << i << endl;
        }
        cout << "*****************************************" << endl;
        //inoder right
        inOrder(node->right);
    }
}

Node* BinarySearchTree::removeNode(Node* node, string courseNumber) {
    // if this node is null then return
    if (node == nullptr) {
        return node;
    }

    // recurse down left subtree
    if (courseNumber.compare(node->course.number) < 0) {
        node->left = removeNode(node->left, courseNumber);
    }
    else if (courseNumber.compare(node->course.number)) {
        node->right = removeNode(node->right, courseNumber);
    }
    else {
        // no children so this is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr) {
            // one child in left node
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else if (node->right != nullptr && node->left == nullptr) {
            // one child in right node
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // dealing with two children
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->course = temp->course;
            node->right = removeNode(node->right, temp->course.number);
        }
    }
    return node;
}

// Prototyping for method calls
void prerequisitesValidation();
//void loadCourses(BinarySearchTree* bst);

// Vector of course stucts
vector<Course> coursesList;

// Vector for valid course names
vector<string> validCourseNumber;


void loadCSVData() {
    string csvFilename;
    cout << endl << "Please provide the file name: ";
    cin >> csvFilename;

    // Variable to break down file lines
    string line, entry, temp;

    // Open and read file
    ifstream courseFile(csvFilename);

    if (courseFile.is_open()) {
        while (courseFile.good()) {
            Course tempRow;

            // grab each line in file
            getline(courseFile, line);

            // Set stringstream object using the line that was just grabbed
            stringstream s(line);

            // data count to keep track of the entries we get with getline
            int dataCount = 0;

            // Breakdown data into pieces for data structures
            if (line != "") {
                while (getline(s, entry, ',')) {
                    // Using a switch along with three param getline to determine the seperate data points
                    switch (dataCount) {
                    case 0:
                        tempRow.number = entry;
                        dataCount++;
                        break;
                    case 1:
                        tempRow.description = entry;
                        dataCount++;
                        break;
                    case 2:
                        tempRow.prerequesites.push_back(entry);
                        break;
                    default:
                        break;
                    }
                }
                // If not number or description found, dont pass into vector
                if (!tempRow.number.empty() && !tempRow.description.empty()) {
                    validCourseNumber.push_back(tempRow.number);
                    coursesList.push_back(tempRow);
                }
            }
        }
        courseFile.close();
    }
    else {
       cout << "File could not open. Check file name." << endl;
    }
    prerequisitesValidation();
}

// For testing purposes
void listCourses() {
    for (Course i : coursesList) {
        cout << "Course number: " << i.number << endl;
        cout << "Course description: " << i.description << endl;
        cout << "Course Prerequisites: " << endl;
        for (string y : i.prerequesites) {
            cout << "\t\t\t" << y << endl;
        }
    }
}

// Prerequisite Validation
void prerequisitesValidation() {
    for (Course i : coursesList) {
        if (!i.prerequesites.empty()) {
            for (string y : i.prerequesites) {
                // setup iterator for find method
                vector<string>::iterator iterate;
                iterate = find(validCourseNumber.begin(), validCourseNumber.end(), y);
                // if found in vector continue
                if (iterate != validCourseNumber.end()) {
                    continue;
                }
                else {
                    cout << endl << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                    cout << "Prerequisite not found in valid course list for : " << i.number << ", REMOVING from valid courses." << endl;
                    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;
                    coursesList.erase(remove(coursesList.begin(), coursesList.end(), i), coursesList.end());
                }
            }
        }
    }
}

void displayCourse(Course course) {
    cout << "*****************************************" << endl;
    cout << "Course Number: " << course.number << endl;
    cout << "Course Description: " << course.description << endl;
    cout << "Course Prerequisites: " << endl;
    for (string i : course.prerequesites) {
        cout << "\t\t\t" << i << endl;
    }
    cout << "*****************************************" << endl;
}

void loadCourses(BinarySearchTree* bst) {
    for (Course course : coursesList) {
        bst->Insert(course);
    }
}

void displayMenu() {
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "*****************************************" << endl;
        cout << "Main Menu: " << endl;
        cout << " 1. Load Courses From CSV" << endl;
        cout << " 2. Print Course List" << endl;
        cout << " 3. Print Specific Course Information" << endl;
        cout << " 9. Exit Application" << endl;
        cout << "*****************************************" << endl << endl;
        
        cout << "Choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            loadCSVData();
            loadCourses(bst);
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            string courseKey;
            cout << "Please type the course number you are searching for: " << endl;
            cin >> courseKey;

            // Ensure its always capitalized
            transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);
            course = bst->Search(courseKey);

            if (!course.number.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course Number" << courseKey << " not found." << endl;
            }
            break;
        }
    }
}

int main()
{
    displayMenu();
}
