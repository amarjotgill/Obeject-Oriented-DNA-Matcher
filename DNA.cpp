//Title: DNA.cpp
//Author: Amarjot Gill
//Date: 4/1/2021
//Description: This is part of the DNA_Profiler project in CMSC 202 @ UMBC
#include "DNA.h"
const int ONE = 1;

DNA::DNA(){
    m_name = "Placeholder";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

DNA::DNA(string name){
    m_name = name;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

string DNA::GetName(){
    return m_name;
}

DNA::~DNA(){
    Node *curr = m_head;
    while (curr != nullptr){
        m_head = curr;
        curr = curr -> m_next;
        // deletes all nodes
        delete m_head;
    }
    // resets everything
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

void DNA::InsertEnd(char dna){
    Node *DnaNode = new Node;
   
    DnaNode -> m_next = nullptr;
    DnaNode -> m_data = dna;
    if (m_head == nullptr){
        m_head = DnaNode;
        m_tail = DnaNode;
        m_size++;
    }else{
        Node *temp2 = m_head;
        // will reach the end of the list and then make the end's m_next = the new node
        while (temp2 -> m_next != nullptr){
           temp2 = temp2 -> m_next;
        }
        
        temp2 -> m_next = DnaNode;
        m_tail = DnaNode;
        temp2 = nullptr;
        delete temp2;
        m_size++;
    }
}

  int DNA::GetSize(){
      return m_size;
  }

ostream &operator<< (ostream &output, DNA &myDNA){
    if (myDNA.m_size == 0){
        output << "Linked list is empty" << endl;
        return output;
    }else{
        Node *temp = myDNA.m_head;
        output << myDNA.m_name << endl;
        // iterates through the list and prints it all
        for (int i = 0; i < myDNA.m_size; i++){
            output << temp -> m_data << "->";
            temp = temp -> m_next;
        }
        output << "END" << endl;
        return output;

    }  
}

void DNA::ReverseSequence(){
    Node *curr = m_head;
    Node *prev = nullptr;
    Node *next = nullptr;
    while (curr != nullptr){
        // makes next curr's next
        next = curr -> m_next;
        // currs next is the previous
        curr -> m_next = prev;
        // previous is now curr
        prev = curr;
        // curr is now next so it reversed
        curr = next;
    }
    m_head = prev;
    cout << "Done reversing " << m_name << "'s sequence" << endl;

    curr = nullptr;
    prev = nullptr;
    next = nullptr;

    delete curr;
    delete prev;
    delete next;
}

bool DNA::CompareSequence(DNA &evidence){
    int evidenceSize = evidence.GetSize();
    char evidenceData;
    char dnaData;
    // i is for dna node list size j is for evidence node list size
    int i = 0; 
    int j = 0;
  
    // goes through both linked list
    while (i < m_size && j < evidenceSize){
        dnaData = GetData(i);
        evidenceData = evidence.GetData(j);
        // if they match increment i and j
        if (dnaData == evidenceData){
            i++;
            j++;
           // if evidence if complete traversed then they match
            if (j == evidenceSize){
                return true;
            }    
        }else{
                // resets i and j because linked list at i and j didnt match
                i = i - j + ONE;
                j = 0;
            }
    }
    return false;
}

char DNA::GetData(int nodeNum){
    char dnaData;
    int currentStep = 0;
    Node *temp = m_head;
    while (currentStep != nodeNum){
        temp = temp -> m_next;
        // will go through till the index of node is reached
        currentStep++;
    }

    dnaData = temp->m_data;
    temp = nullptr;
    delete temp;
    return dnaData;
}
