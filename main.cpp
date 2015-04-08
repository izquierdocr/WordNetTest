#include <iostream>
#include "wn.h"

using namespace std;


void printSynsetDef(SynsetPtr currentSynset){
  if (currentSynset==NULL) return;
  
  cout << "Count: " << currentSynset->wcount << endl;					
  cout << "Type: " << currentSynset->sstype << endl;
  cout << "Definition: " << currentSynset->defn << endl;
  
  for( int k=0; k < currentSynset->wcount; k++ )
    cout << currentSynset->words[k] << endl;
  
  return;
}


int main(int argc, char **argv) {
  
  //string wordInString="apple";
  //string wordInString="cellphone";
  string wordInString="water";
  char* word= (char *)wordInString.c_str();
  
  int isOpen = 0 == wninit();
  if (isOpen) {
    cout << "Wordnet opened!" << endl;
  }
  else {
    cout << "Could not open WordNet dictionary!!" << endl;
    return 1;
  }
  
  
  SynsetPtr synsetWord = findtheinfo_ds( word, NOUN, SYNS, ALLSENSES );
  SynsetPtr currentSense = synsetWord;
  int i=0;
  while( currentSense != NULL )
  {
    cout << endl << "Sense " << i++ << endl;
    printSynsetDef(currentSense);
    
    SynsetPtr listHypernym = traceptrs_ds(currentSense, HYPERPTR, NOUN, 1);
    SynsetPtr currentHypernym = listHypernym;
    int j=0;
    while( currentHypernym != NULL ) {
      cout << endl << "Hypernym " << j++ << endl;
      printSynsetDef(currentHypernym);
      
      SynsetPtr coordinateList = traceptrs_ds(currentHypernym, HYPOPTR, NOUN, 2);
      SynsetPtr currentCoordinate = coordinateList;
      int k=0;
      while( currentCoordinate != NULL ) {
	cout << endl << "Coordinate " << k++ << endl;
	printSynsetDef(currentCoordinate);
	currentCoordinate = currentCoordinate->nextss;
      }
      free_syns(coordinateList);

      currentHypernym = currentHypernym->nextss;
    }
    free_syns(listHypernym);

    currentSense = currentSense->nextss;
  }
  
  free_syns(synsetWord);
 
  
  //Testing user output
  //cout << endl << "----------------------------------------" << endl;
  //cout << findtheinfo( word, NOUN, COORDS, ALLSENSES ) << endl;
  
  
  return 0;
}
