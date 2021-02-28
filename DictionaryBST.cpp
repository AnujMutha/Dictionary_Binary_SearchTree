#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

class DictNode
{
private:
    string key,meaning;
    DictNode *left, *right;
public:
    DictNode(string key,string meaning){
        this->key = key;
        this->meaning = meaning;
        this->left = this->right = nullptr;
    }
    friend class Dictionary;
};
class Dictionary{
public:
    //Function to insert a meaning to its key STARTS
    DictNode* insertDictNode(DictNode *rootWord,string key,string meaning){

        if(rootWord == nullptr){
            cout<<"Dicitonary was empty....Intialised";
            rootWord = new DictNode(key,meaning);
            return rootWord;
        }else{
            if(rootWord->key > key){
                if(rootWord->left != nullptr){
                    insertDictNode(rootWord->left,key,meaning);
                } else{
                    rootWord->left = new DictNode(key,meaning);
                    cout<<"\nNew word inserted Successfully";
                }

            } else if(rootWord->key < key){
                if (rootWord->right!= nullptr){
                    insertDictNode(rootWord->right,key,meaning);
                } else{
                    rootWord->right = new DictNode(key,meaning);
                    cout<<"\nNew word inserted Successfully";
                }
            } else if(rootWord->key == key){
                cout<<"\nKeyword already present..!";
            }
        }
        return rootWord;
    }
//Function to insert a meaning to its key ENDS

//Facility to display dictionary ASCENDING/DESCENDING STARTS
    void showAscendingDictionary(const DictNode *rootWord){
        if(rootWord == nullptr){return;}
        showAscendingDictionary(rootWord->left);
        cout<<endl<<rootWord->key<<" : "<<rootWord->meaning;
        showAscendingDictionary(rootWord->right);
    }
    void showDescendingDictionary(const DictNode *rootWord){
        if(rootWord == nullptr){return;}
        showDescendingDictionary(rootWord->right);
        cout<<endl<<rootWord->key<<" : "<<rootWord->meaning;
        showDescendingDictionary(rootWord->left);
    }
//Facility to display dictionary ASCENDING/DESCENDING ENDS

//Function to update a word in dictionary STARTS
    void updateDictWord(DictNode *rootWord,string updateKey){
        string newMeaning;
        if(rootWord== nullptr)
        {return;}
        if(rootWord->key == updateKey){
            cout<<"\nEnter new meaning for "<<updateKey<<" : ";cin>>newMeaning;
            rootWord->meaning=newMeaning;
            cout<<"\nKey's meaning updated successfully...";
        } else
        if(rootWord->key > updateKey)
        {
            updateDictWord(rootWord->left,updateKey);
            if (rootWord->left== nullptr){
                cout<<"\nNo similar key found";
                return;
            }
        }
        else if (rootWord->key < updateKey)
        {
            updateDictWord(rootWord->right,updateKey);
            if (rootWord->right== nullptr){
                cout<<"\nNo similar key found";
                return;
            }
        }
    }
//Function to update a word in dictionary ENDS

//Functions to delete a keyword STARTS
    DictNode* deleteDictKeyword(DictNode *rootWord, string keyToDelete){
        if(rootWord == nullptr)
        {
            return rootWord;
        }

        else if(keyToDelete < rootWord->key)
        {
            rootWord->left = deleteDictKeyword(rootWord->left, keyToDelete);
            if (rootWord->left== nullptr){
                cout<<"\nNo similar key found";
                return rootWord;
            }
        }
        else if(keyToDelete > rootWord->key)
        {
            rootWord->right = deleteDictKeyword(rootWord->right, keyToDelete);
            if (rootWord->right == nullptr){
                cout<<"\nNo similar key found";
                return rootWord;
            }
        }
        else
        {
            if(rootWord->left == nullptr && rootWord->right == nullptr){//CASE 3 NO CHILD PRESENT ON EITHER OF SIDES
                cout<<"Deleted .........";
                delete rootWord;
                rootWord = nullptr;
            }
            else if(rootWord->left == nullptr){//........................CASE 2 CHILD PRESENT AT LEFT
                DictNode *temp = rootWord;
                rootWord = rootWord->right;
                cout<<"Deleted .........";
                delete temp;
                temp = nullptr;
            }
            else if(rootWord->right == nullptr){//.......................CASE 2 CHILD PRESENT AT RIGHT
                DictNode *temp = rootWord;
                rootWord = rootWord->left;
                cout<<"Deleted .........";
                delete temp;
                temp = nullptr;
            } else{
                DictNode *minN = findMin(rootWord->right);//..............INORDER SUCCESSOR
                rootWord->key = minN->key;
                rootWord->meaning = minN->meaning;
                rootWord->right = deleteDictKeyword(rootWord->right, minN->key);
            }
        }
        return rootWord;
    }

    DictNode* findMin(DictNode *rootWord) {
        if(rootWord->left == nullptr){
            return rootWord->left;
        } else{
            return findMin(rootWord->left);
        }
    }

//Functions to delete a keyword ENDS

//Functions to count number of comparisons STARTS
    void countComp(DictNode *rootWord,string keyToSearch,int counter){

        if(rootWord== nullptr){
            cout<<"Empty Dictionary";
            return;}
        if(rootWord->key == keyToSearch){
            cout<<"\nNumber of comparison : "<<counter;
            cout<<"\nKey's found successfully...";
            return;
        } else
        if(rootWord->key > keyToSearch)
        {
            counter+=1;
            countComp(rootWord->left,keyToSearch,counter);
            if (rootWord->left== nullptr){
                cout<<"\nNo similar key found";
                return;
            }
        }
        else if (rootWord->key < keyToSearch)
        {
            counter+=1;
            countComp(rootWord->right,keyToSearch,counter);
            if (rootWord->right== nullptr){
                cout<<"\nNo similar key found";
                return;
            }
        }

    }
//Functions to count number of comparisons ENDS
};
DictNode *findMin(DictNode *pNode);


int main(){
    int counter=0;
    int choice;
    string key,meaning;
    Dictionary dictionary;
    DictNode *dictNode = nullptr;

    while (choice!=7){
        key = "";
        cout<<"\n|===============OPERATIONS=================|"
            <<"\n| 1) : Insert a word                       |"
            <<"\n|******************************************|"
            <<"\n| 2) : Show Dictionary in ascending order  |"
            <<"\n|******************************************|"
            <<"\n| 3) : Show dictionary in descending order |"
            <<"\n|******************************************|"
            <<"\n| 4) : Update a word                       |"
            <<"\n|******************************************|"
            <<"\n| 5) : Delete a word                       |"
            <<"\n|******************************************|"
            <<"\n| 6) : Find a word  (With Max Comparisons) |"
            <<"\n|******************************************|"
            <<"\n| 7) : EXIT                                |"
            <<"\n|==========================================|";
        cout<<"\n|Enter Your Choice : ";cin>>choice;
        switch (choice) {
            case 1:
                cout<<"\nEnter Key : ";cin>>key;
                cout<<"Enter Meaning : ";cin>>meaning;
                dictNode = dictionary.insertDictNode(dictNode,key,meaning);
                cout<<"\nPress any key to continue...!";
                getch();
                break;
            case 2:
                cout<<"\n===========DICTIONARY==============";
                dictionary.showAscendingDictionary(dictNode);
                cout<<"\n===================================\n";
                cout<<"\nPress any key to continue...!";
                getch();
                break;
            case 3:
                cout<<"\n===========DICTIONARY==============";
                dictionary.showDescendingDictionary(dictNode);
                cout<<"\n===================================\n";
                cout<<"\nPress any key to continue...!";
                getch();
                break;
            case 4:
                cout<<"\nEnter the keyword whose meaning you want to change : ";cin>>key;
                dictionary.updateDictWord(dictNode,key);
                cout<<"\nPress any key to continue...!";
                getch();
                break;
            case 5:
                cout<<"\nEnter the keyword you wish to delete : ";cin>>key;
                dictNode = dictionary.deleteDictKeyword(dictNode,key);
                cout<<"\nPress any key to continue...!";
                getch();
                break;
            case 6:
                cout<<"\nEnter the keyword you wish to find : ";cin>>key;
                dictionary.countComp(dictNode,key,counter);
                cout<<"\nPress any key to continue...!";
                getch();
                break;
            case 7:
                cout<<"Terminating from console.....\n";
                _sleep(1500);
                cout<<"Signing off......\n";
                _sleep(1500);
                cout<<"Terminated successfully !";
                exit(0);
        }
    }
    return 1;
}