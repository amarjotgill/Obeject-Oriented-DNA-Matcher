//Title: Sequencer.cpp
//Author: Amarjot Gill
//Date: 4/1/2021
//Description: This is part of the DNA_Profiler project in CMSC 202 @ UMBC
#include "Sequencer.h"
const int ONE = 1;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;
const char S = 'S';
const char E = 'E';
const char COMMA = ',';


Sequencer::Sequencer(string fileName){
     m_fileName = fileName;
     ReadFile();
     MainMenu();
}

Sequencer::~Sequencer(){
     cout << "Deleting suspects" << endl;
     // deletes all pointers in m_suspects
     for (int i = 0; i < int(m_suspects.size()); i++){
          delete m_suspects[i];
          m_suspects.at(i) = nullptr;
          
     }
     cout << "Deleting evidence" << endl;
     // deletes all pointers in m_evidence
     for (int i = 0; i < int(m_evidence.size()); i++){
          delete m_evidence[i];
          m_evidence.at(i) = nullptr;
     }
}

void Sequencer::MainMenu(){
     int userChoice;
     bool continueUser = true;
     do{
          cout << "What would you like to do? " << endl;
          cout << "1. Display Strand " << endl;
          cout << "2. Reverse Sequence " << endl;
          cout << "3. Check Suspects" << endl;
          cout << "4. Exit" << endl;
          cin >> userChoice;

          if (userChoice == ONE){
               DisplayStrands();
          }else if (userChoice == TWO){
               ReverseSequence();
          }else if(userChoice == THREE){
               CheckSuspects();

          }else if(userChoice == FOUR){
               cout << "Deleting DNA strands" << endl;
               // calls DNA destructor for each suspect and evidence.
               for (int i = 0; i < int(m_suspects.size()); i++){
                    m_suspects[i] -> ~DNA();
                    
               }
               for (int i = 0; i < int(m_evidence.size()); i++){
                    m_evidence[i] -> ~DNA();   
               }
               continueUser = false;

          }else{
               // runs if 1,2,3,4 isnt selected
               cout << " Please enter a number 1 - 4 " << endl;
          }  
     } while (continueUser);   
}


void Sequencer::ReadFile(){
     string name;
     DNA *newSuspect = nullptr;
     DNA *newEvidence = nullptr;
    
    // keep tracks of position
    int currentPosition = 0;
    ifstream theFile(m_fileName);
    if(theFile.is_open()){
        while(getline(theFile,name)){
             if(name[0] == S){
                    // creates new DNA
                    newSuspect =  new DNA(name);
                    m_suspects.push_back(newSuspect);
                    currentPosition++;

                    getline(theFile,name);
                    for (int i = 0; i < int(name.length()); i++){
                         // goes the length and if the char isnt a , its a DNA strand so it adds it to the node list.
                         if (name[i] != COMMA){
                             newSuspect -> InsertEnd(name[i]); 
                         }    
                    }
                    newSuspect = nullptr;

             }if (name[0] == E){
                    newEvidence = new DNA(name);
                    m_evidence.push_back(newEvidence); 
                    currentPosition++;
                    getline(theFile,name);
                    for (int i = 0; i < int(name.length()); i++){
                         if (name[i] != COMMA){
                            newEvidence -> InsertEnd(name[i]); 
                         }
                    } 
             }
        }
    }
    cout << currentPosition << " Strands loaded" << endl;
    theFile.close();
}

void Sequencer::DisplayStrands(){
     // calls the ostream for each suspect and evidence outputting it
     for (int i = 0; i < int(m_suspects.size()); i++){
          cout << *m_suspects[i];  
     }

     for (int i = 0; i < int(m_evidence.size()); i++){
          cout << *m_evidence[i];
     }
}

void Sequencer::ReverseSequence(){
     int userChoice;
     int whichStrand;
     do{
          cout << "Which Sequence to reverse?" << endl;
          cout << "1. Suspect" << endl;
          cout << "2. Evidence" << endl;
          cin >> userChoice;
     } while (userChoice <= 0 || userChoice > 2);

     if (userChoice == ONE){
               do{
                    cout << "Which suspect # do you want to reverse?" << endl;
                    cin >> whichStrand;
               } while (whichStrand > int(m_suspects.size())); 
               // calls reverse sequence for the suspect user seleted to reverse
               m_suspects.at(whichStrand - ONE) -> ReverseSequence();
     }else if(userChoice == TWO){
          do{
               cout << "Which evidence # do you want to reverse?" << endl;
               cin >> whichStrand;
               } while (whichStrand > int(m_evidence.size())); 
               m_evidence.at(whichStrand - ONE) -> ReverseSequence();
     }
}

void Sequencer::CheckSuspects(){
     bool matches = true;
     int matchesEvi = 0;
     cout << "Checking all suspects vs evidence" << endl;
     for (int i = 0; i < int(m_suspects.size()); i++){
          // resets the matches for each new suspect
          matchesEvi = 0;
          for (int j = 0; j < int(m_evidence.size()); j++){
               // compares each suspect with each evidence
               matches = m_suspects[i] -> CompareSequence(*m_evidence[j]);
               if (matches){
                    cout << m_suspects[i] -> GetName() << " matches " << m_evidence[j] -> GetName() << endl;
                    matchesEvi++;
               // if matchesEvi is incremented and = the amount of evidence them suspect matches all evidence
               }if(matchesEvi == int(m_evidence.size())){
                    cout << m_suspects[i] -> GetName() << " matches ALL evidence! " << endl;
               }else if(matches == false){
                    cout << m_suspects[i] -> GetName() << " does NOT match " << m_evidence[j] -> GetName() << endl;
               }
          }
     }
}