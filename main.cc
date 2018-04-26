//Programmed by: Matthew Nevle
//Student Id: Man160530

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <sstream>
#include <cctype>
#include "cdk.h"
using namespace std;

//Define Header class for binary file
class BinaryFileHeader{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

//Define the Record class for Binary file
const int maxRecordStringLength = 25;
class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

//Define Matrix settings
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "HW6 Matrix"

int main(){
  
  //Initialize Matrix variables
  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;

  //Initialize Matrix settings
  const char *columnTitles[MATRIX_HEIGHT+1] = {"0","a","b","c","d","e"};
  const char *rowTitles[MATRIX_WIDTH+1] = {"0","a","b","c"};
  int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  //Initialize Matrix
  window = initscr();
  cdkscreen = initCDKScreen(window);
  initCDKColor();

  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_NAME_STRING, (char **) columnTitles, (char**) rowTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);
  //Initialize objects for holding binary information
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  
  //Read Header information
  ifstream binInFile("cs3377.bin", ios::in | ios::binary);
  binInFile.read((char*) myHeader, sizeof(BinaryFileHeader));
  
  //Convert magicNumber back into Hex
  std::stringstream stream, version, numRecords;
  stream << std::hex << myHeader->magicNumber;
  string head = stream.str();
  string hex;
  for(int i = 0;(unsigned)i < head.size(); i++){
    hex += toupper(head[i]);
  }
  
  //Insert all header veriables into matrix
  hex = "0x" + hex;
  version <<  "Version: "  <<  myHeader->versionNumber;
  numRecords << "NumRecords: " << myHeader->numRecords;
  setCDKMatrixCell(myMatrix, 1, 1, hex.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.str().c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.str().c_str()); 
  
  //Go through records based on number given in header and insert into matrix
  std::stringstream buffer;
  for(int i = 0;(unsigned)i < myHeader->numRecords; i++){  
    binInFile.read((char*) myRecord, sizeof(BinaryFileRecord));
    buffer << "strlen: " << strlen(myRecord->stringBuffer);
    setCDKMatrixCell(myMatrix, i+2, 1, buffer.str().c_str());
    setCDKMatrixCell(myMatrix, i+2, 2, myRecord->stringBuffer);
    buffer.str("");
  }
  
  //Draw matrix and set a pause timer
  drawCDKMatrix(myMatrix,true);
  sleep(10);
  endCDK();
  return 0;
}
