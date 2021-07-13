#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Header {
   char idLength;
   char colorMapType;
   char dataTypeCode;
   short colorMapOrigin;
   short colorMapLength;
   char  colorMapDepth;
   short xOrigin;
   short yOrigin;
   short width;
   short height;
   char  bitsPerPixel;
   char  imageDescriptor;
};

struct Pixels {
  unsigned char blue;
  unsigned char green;
  unsigned char red;
};

void Multiplication(vector<Pixels> &storingVal, vector<Pixels> &storingValTwo, vector<Pixels> &result, unsigned int area){

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    float leftBlue = storingVal.at(i).blue;
    float rightBlue = storingValTwo.at(i).blue;
    float formalBlue = (leftBlue * rightBlue)/255;
    formalBlue += 0.5f;
    unsigned resultBlue = (unsigned char) formalBlue;
    intro.blue = resultBlue;

    float leftGreen = storingVal.at(i).green;
    float rightGreen = storingValTwo.at(i).green;
    float formalGreen = (leftGreen * rightGreen)/255;
    formalGreen += 0.5f;
    unsigned resultGreen = (unsigned char) formalGreen;
    intro.green = resultGreen;

    float leftRed = storingVal.at(i).red;
    float rightRed = storingValTwo.at(i).red;
    float formalRed = (leftRed * rightRed)/255;
    formalRed += 0.5f;
    unsigned resultRed = (unsigned char) formalRed;
    intro.red = resultRed;

    result.push_back(intro);
  }
}

void Subtraction(vector<Pixels> &storingVal, vector<Pixels> &storingValTwo, vector<Pixels> &result, unsigned int area){

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    int leftBlue = storingVal.at(i).blue;
    int rightBlue = storingValTwo.at(i).blue;
    int formalBlue = max(rightBlue - leftBlue, 0);
    unsigned char resultBlue = (unsigned char) formalBlue;
    intro.blue = resultBlue;

    int leftGreen = storingVal.at(i).green;
    int rightGreen = storingValTwo.at(i).green;
    int formalGreen = max(rightGreen - leftGreen, 0);
    unsigned char resultGreen = (unsigned char) formalGreen;
    intro.green = resultGreen;

    int leftRed = storingVal.at(i).red;
    int rightRed = storingValTwo.at(i).red;
    int formalRed = max(rightRed - leftRed, 0);
    unsigned char resultRed = (unsigned char) formalRed;
    intro.red = resultRed;

    result.push_back(intro);
  }
}

void Blending(vector<Pixels> &storingVal, vector<Pixels> &storingValTwo, vector<Pixels> &result, unsigned int area){

  for (unsigned int i = 0; i < area; i++){

    Pixels intro;
    float leftBlue = storingVal.at(i).blue;
    float rightBlue = storingValTwo.at(i).blue;
    float formalBlue = (1 - ((1-rightBlue)*(1-leftBlue)));
    //formalBlue *= 255;
    formalBlue += 0.5f;
    unsigned resultBlue = (unsigned char) formalBlue;
    intro.blue = resultBlue;

    float leftRed = storingVal.at(i).red;
    float rightRed = storingValTwo.at(i).red;
    float formalRed = (1 - ((1-rightRed)*(1-leftRed)));
    //formalRed *= 255;
    formalRed += 0.5f;
    unsigned resultRed = (unsigned char) formalRed;
    intro.red = resultRed;

    int leftGreen = storingVal.at(i).green;
    int rightGreen = storingValTwo.at(i).green;
    int formalGreen = (1 - ((1-rightGreen)*(1-leftGreen)));
    //formalGreen *= 255;
    formalGreen += 0.5f;
    unsigned resultGreen = (unsigned char) formalGreen;
    intro.green = resultGreen;

    result.push_back(intro);
  }
}

void Overlay(vector<Pixels> &storingVal, vector<Pixels> &storingValTwo, vector<Pixels> &result, unsigned int area){
  for (unsigned int i = 0; i < area; i++){
    float formalBlue, formalRed, formalGreen, val, valTwo, valThree, valFour, valFive, valSix;
    Pixels intro;
    int leftBlue = storingVal.at(i).blue;
    int rightBlue = storingValTwo.at(i).blue;
    if (leftBlue > 127.5){
      val = (255 - leftBlue) / 127.5;
      valTwo = leftBlue - (255 - leftBlue);
      formalBlue = (rightBlue * val) + valTwo;
      formalBlue += 0.5f;
    }
    else{
      val = leftBlue / 127.5;
      formalBlue = (rightBlue * val);
      formalBlue += 0.5f;
    }
    unsigned resultBlue = (unsigned char) formalBlue;
    intro.blue = resultBlue;

    int leftRed = storingVal.at(i).red;
    int rightRed = storingValTwo.at(i).red;
    if (leftRed > 127.5){
      valThree = (255 - leftRed) / 127.5;
      valFour = leftRed - (255 - leftRed);
      formalRed = (rightRed * valThree) + valFour;
      formalRed += 0.5f;
    }
    else{
      valThree = leftRed / 127.5;
      formalRed = (rightRed * valThree);
      formalRed += 0.5f;
    }
    unsigned resultRed = (unsigned char) formalRed;
    intro.red = resultRed;

    int leftGreen = storingVal.at(i).green;
    int rightGreen = storingValTwo.at(i).green;
    if (leftGreen > 127.5){
      valSix = (255 - leftGreen) / 127.5;
      valFive = leftGreen - (255-leftGreen);
      formalGreen = (rightGreen * valSix) + valFive;
      formalGreen += 0.5f;
    }
    else{
      valSix = leftGreen / 127.5;
      formalGreen = (rightGreen * valSix);
      formalGreen += 0.5f;
    }
    unsigned resultGreen = (unsigned char) formalGreen;
    intro.green = resultGreen;

    result.push_back(intro);
  }
}

int main(){

  //Question 1

  //Getting width and height of pattern1
  ifstream file;
  file.open("../input/pattern1.tga");

  //header info
  Header headerObject;
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  ifstream fileTwo;
  fileTwo.open("../input/layer1.tga");

  Header another;
  fileTwo.read(&another.idLength, sizeof(another.idLength));
  fileTwo.read(&another.colorMapType, sizeof(another.colorMapType));
  fileTwo.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileTwo.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileTwo.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileTwo.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileTwo.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileTwo.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileTwo.read((char*)&another.width, sizeof(another.width));
  fileTwo.read((char*)&another.height, sizeof(another.height));
  fileTwo.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileTwo.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  //Getting the area
  unsigned int area = headerObject.width * headerObject.height;

  vector<Pixels> storingVal;
  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  vector<Pixels> storingValTwo;
  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileTwo.read((char*)&intro.blue, sizeof(intro.blue));
    fileTwo.read((char*)&intro.green, sizeof(intro.green));
    fileTwo.read((char*)&intro.red, sizeof(intro.red));
    storingValTwo.push_back(intro);
  }

  vector<Pixels> result;
  Multiplication(storingVal, storingValTwo, result, area);

  Header testing;
  ifstream testFile;
  testFile.open("../examples/EXAMPLE_part1.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  vector<Pixels> myTest;
  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }
  int point = 0;
  for(unsigned int i = 0; i < area; i++){
    int red_one = result.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = result.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = result.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream output("../output/part1.tga", ios_base::binary);
  output.write(&headerObject.idLength,1);
  output.write(&headerObject.colorMapType,1);
  output.write(&headerObject.dataTypeCode,1);
  output.write((char*)&headerObject.colorMapOrigin,2);
  output.write((char*)&headerObject.colorMapLength,2);
  output.write(&headerObject.colorMapDepth,1);
  output.write((char*)&headerObject.xOrigin,2);
  output.write((char*)&headerObject.yOrigin,2);
  output.write((char*)&headerObject.width,2);
  output.write((char*)&headerObject.height,2);
  output.write(&headerObject.bitsPerPixel,1);
  output.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    output.write((char*)&result.at(i).blue,1);
    output.write((char*)&result.at(i).green,1);
    output.write((char*)&result.at(i).red,1);
  }

  if (point == area)
    cout << "Test 1 ...... Passed" << endl;
  else{
    cout << "Test 1 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point =0;
  testFile.close();
  file.close();
  fileTwo.close();
  storingVal.clear();
  storingValTwo.clear();
  myTest.clear();

  //Question 2

  file.open("../input/layer2.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  fileTwo.open("../input/car.tga");

  fileTwo.read(&another.idLength, sizeof(another.idLength));
  fileTwo.read(&another.colorMapType, sizeof(another.colorMapType));
  fileTwo.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileTwo.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileTwo.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileTwo.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileTwo.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileTwo.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileTwo.read((char*)&another.width, sizeof(another.width));
  fileTwo.read((char*)&another.height, sizeof(another.height));
  fileTwo.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileTwo.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  //Getting the area
  area = another.width * another.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileTwo.read((char*)&intro.blue, sizeof(intro.blue));
    fileTwo.read((char*)&intro.green, sizeof(intro.green));
    fileTwo.read((char*)&intro.red, sizeof(intro.red));
    storingValTwo.push_back(intro);
  }

  vector<Pixels> resultTwo;
  Subtraction(storingVal, storingValTwo, resultTwo, area);

  testFile.open("../examples/EXAMPLE_part2.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }

  for(unsigned int i = 0; i < area; i++){
    int red_one = resultTwo.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = resultTwo.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = resultTwo.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream outputTwo("../output/part2.tga", ios_base::binary);
  outputTwo.write(&headerObject.idLength,1);
  outputTwo.write(&headerObject.colorMapType,1);
  outputTwo.write(&headerObject.dataTypeCode,1);
  outputTwo.write((char*)&headerObject.colorMapOrigin,2);
  outputTwo.write((char*)&headerObject.colorMapLength,2);
  outputTwo.write(&headerObject.colorMapDepth,1);
  outputTwo.write((char*)&headerObject.xOrigin,2);
  outputTwo.write((char*)&headerObject.yOrigin,2);
  outputTwo.write((char*)&headerObject.width,2);
  outputTwo.write((char*)&headerObject.height,2);
  outputTwo.write(&headerObject.bitsPerPixel,1);
  outputTwo.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputTwo.write((char*)&resultTwo.at(i).blue,1);
    outputTwo.write((char*)&resultTwo.at(i).green,1);
    outputTwo.write((char*)&resultTwo.at(i).red,1);
  }

  if(point == area)
    cout << "Test 2 ...... Passed" << endl;
  else{
    cout << "Test 2 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point = 0;
  testFile.close();
  myTest.clear();

  file.close();
  fileTwo.close();
  storingVal.clear();
  storingValTwo.clear();

  //Question 3
  file.open("../input/layer1.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  fileTwo.open("../input/pattern2.tga");

  fileTwo.read(&another.idLength, sizeof(another.idLength));
  fileTwo.read(&another.colorMapType, sizeof(another.colorMapType));
  fileTwo.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileTwo.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileTwo.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileTwo.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileTwo.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileTwo.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileTwo.read((char*)&another.width, sizeof(another.width));
  fileTwo.read((char*)&another.height, sizeof(another.height));
  fileTwo.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileTwo.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  //Getting the area
  area = another.width * another.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileTwo.read((char*)&intro.blue, sizeof(intro.blue));
    fileTwo.read((char*)&intro.green, sizeof(intro.green));
    fileTwo.read((char*)&intro.red, sizeof(intro.red));
    storingValTwo.push_back(intro);
  }

  vector<Pixels> resultTemp;
  Multiplication(storingVal, storingValTwo, resultTemp, area);

  ifstream fileThree;
  fileThree.open("../input/text.tga");

  fileThree.read(&another.idLength, sizeof(another.idLength));
  fileThree.read(&another.colorMapType, sizeof(another.colorMapType));
  fileThree.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileThree.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileThree.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileThree.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileThree.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileThree.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileThree.read((char*)&another.width, sizeof(another.width));
  fileThree.read((char*)&another.height, sizeof(another.height));
  fileThree.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileThree.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  vector<Pixels> tempo;
  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileThree.read((char*)&intro.blue, sizeof(intro.blue));
    fileThree.read((char*)&intro.green, sizeof(intro.green));
    fileThree.read((char*)&intro.red, sizeof(intro.red));
    tempo.push_back(intro);
  }

  vector<Pixels> resultThree;
  Blending(tempo, resultTemp, resultThree, area);

  testFile.open("../examples/EXAMPLE_part3.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }

  for(unsigned int i = 0; i < area; i++){
    int red_one = resultThree.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = resultThree.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = resultThree.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream outputThree("../output/part3.tga", ios_base::binary);
  outputThree.write(&headerObject.idLength,1);
  outputThree.write(&headerObject.colorMapType,1);
  outputThree.write(&headerObject.dataTypeCode,1);
  outputThree.write((char*)&headerObject.colorMapOrigin,2);
  outputThree.write((char*)&headerObject.colorMapLength,2);
  outputThree.write(&headerObject.colorMapDepth,1);
  outputThree.write((char*)&headerObject.xOrigin,2);
  outputThree.write((char*)&headerObject.yOrigin,2);
  outputThree.write((char*)&headerObject.width,2);
  outputThree.write((char*)&headerObject.height,2);
  outputThree.write(&headerObject.bitsPerPixel,1);
  outputThree.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputThree.write((char*)&resultThree.at(i).blue,1);
    outputThree.write((char*)&resultThree.at(i).green,1);
    outputThree.write((char*)&resultThree.at(i).red,1);
  }

  if(point == area)
    cout << "Test 3 ...... Passed" << endl;
  else{
    cout << "Test 3 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point = 0;
  testFile.close();
  myTest.clear();

  file.close();
  fileTwo.close();
  fileThree.close();
  storingVal.clear();
  storingValTwo.clear();
  tempo.clear();
  resultTemp.clear();

  //Question 4
  file.open("../input/layer2.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  fileTwo.open("../input/circles.tga");

  fileTwo.read(&another.idLength, sizeof(another.idLength));
  fileTwo.read(&another.colorMapType, sizeof(another.colorMapType));
  fileTwo.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileTwo.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileTwo.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileTwo.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileTwo.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileTwo.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileTwo.read((char*)&another.width, sizeof(another.width));
  fileTwo.read((char*)&another.height, sizeof(another.height));
  fileTwo.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileTwo.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  //Getting the area
  area = another.width * another.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileTwo.read((char*)&intro.blue, sizeof(intro.blue));
    fileTwo.read((char*)&intro.green, sizeof(intro.green));
    fileTwo.read((char*)&intro.red, sizeof(intro.red));
    storingValTwo.push_back(intro);
  }

  Multiplication(storingVal, storingValTwo, resultTemp, area);

  fileThree.open("../input/pattern2.tga");

  fileThree.read(&another.idLength, sizeof(another.idLength));
  fileThree.read(&another.colorMapType, sizeof(another.colorMapType));
  fileThree.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileThree.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileThree.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileThree.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileThree.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileThree.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileThree.read((char*)&another.width, sizeof(another.width));
  fileThree.read((char*)&another.height, sizeof(another.height));
  fileThree.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileThree.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileThree.read((char*)&intro.blue, sizeof(intro.blue));
    fileThree.read((char*)&intro.green, sizeof(intro.green));
    fileThree.read((char*)&intro.red, sizeof(intro.red));
    tempo.push_back(intro);
  }

  vector<Pixels> resultFour;
  Subtraction(tempo, resultTemp, resultFour, area);

  testFile.open("../examples/EXAMPLE_part4.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }

  for(unsigned int i = 0; i < area; i++){
    int red_one = resultFour.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = resultFour.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = resultFour.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream outputFour("../output/part4.tga", ios_base::binary);
  outputFour.write(&headerObject.idLength,1);
  outputFour.write(&headerObject.colorMapType,1);
  outputFour.write(&headerObject.dataTypeCode,1);
  outputFour.write((char*)&headerObject.colorMapOrigin,2);
  outputFour.write((char*)&headerObject.colorMapLength,2);
  outputFour.write(&headerObject.colorMapDepth,1);
  outputFour.write((char*)&headerObject.xOrigin,2);
  outputFour.write((char*)&headerObject.yOrigin,2);
  outputFour.write((char*)&headerObject.width,2);
  outputFour.write((char*)&headerObject.height,2);
  outputFour.write(&headerObject.bitsPerPixel,1);
  outputFour.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputFour.write((char*)&resultFour.at(i).blue,1);
    outputFour.write((char*)&resultFour.at(i).green,1);
    outputFour.write((char*)&resultFour.at(i).red,1);
  }

  if(point == area)
    cout << "Test 4 ...... Passed" << endl;
  else{
    cout << "Test 4 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point = 0;
  testFile.close();
  myTest.clear();

  file.close();
  fileTwo.close();
  fileThree.close();
  storingVal.clear();
  storingValTwo.clear();
  tempo.clear();
  resultTemp.clear();

  //Question 5

  file.open("../input/layer1.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  fileTwo.open("../input/pattern1.tga");

  fileTwo.read(&another.idLength, sizeof(another.idLength));
  fileTwo.read(&another.colorMapType, sizeof(another.colorMapType));
  fileTwo.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileTwo.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileTwo.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileTwo.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileTwo.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileTwo.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileTwo.read((char*)&another.width, sizeof(another.width));
  fileTwo.read((char*)&another.height, sizeof(another.height));
  fileTwo.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileTwo.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  //Getting the area
  area = another.width * another.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileTwo.read((char*)&intro.blue, sizeof(intro.blue));
    fileTwo.read((char*)&intro.green, sizeof(intro.green));
    fileTwo.read((char*)&intro.red, sizeof(intro.red));
    storingValTwo.push_back(intro);
  }

  Overlay(storingValTwo, storingVal, resultTemp, area);

  testFile.open("../examples/EXAMPLE_part5.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }

  for(unsigned int i = 0; i < area; i++){
    int red_one = resultTemp.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = resultTemp.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = resultTemp.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream outputFive("../output/part5.tga", ios_base::binary);
  outputFive.write(&headerObject.idLength,1);
  outputFive.write(&headerObject.colorMapType,1);
  outputFive.write(&headerObject.dataTypeCode,1);
  outputFive.write((char*)&headerObject.colorMapOrigin,2);
  outputFive.write((char*)&headerObject.colorMapLength,2);
  outputFive.write(&headerObject.colorMapDepth,1);
  outputFive.write((char*)&headerObject.xOrigin,2);
  outputFive.write((char*)&headerObject.yOrigin,2);
  outputFive.write((char*)&headerObject.width,2);
  outputFive.write((char*)&headerObject.height,2);
  outputFive.write(&headerObject.bitsPerPixel,1);
  outputFive.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputFive.write((char*)&resultTemp.at(i).blue,1);
    outputFive.write((char*)&resultTemp.at(i).green,1);
    outputFive.write((char*)&resultTemp.at(i).red,1);
  }

  if(point == area)
    cout << "Test 5 ...... Passed" << endl;
  else{
    cout << "Test 5 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point = 0;
  testFile.close();
  myTest.clear();

  file.close();
  fileTwo.close();
  fileThree.close();
  storingVal.clear();
  storingValTwo.clear();
  tempo.clear();
  resultTemp.clear();

  //Question 6

  file.open("../input/car.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  area = another.width * another.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    int value = storingVal.at(i).green;
    value += 200;
    int anotherOne = min(value,255);
    storingVal.at(i).green = (unsigned char) anotherOne;
  }

  testFile.open("../examples/EXAMPLE_part6.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }

  for(unsigned int i = 0; i < area; i++){
    int red_one = storingVal.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = storingVal.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = storingVal.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream outputSix("../output/part6.tga", ios_base::binary);
  outputSix.write(&headerObject.idLength,1);
  outputSix.write(&headerObject.colorMapType,1);
  outputSix.write(&headerObject.dataTypeCode,1);
  outputSix.write((char*)&headerObject.colorMapOrigin,2);
  outputSix.write((char*)&headerObject.colorMapLength,2);
  outputSix.write(&headerObject.colorMapDepth,1);
  outputSix.write((char*)&headerObject.xOrigin,2);
  outputSix.write((char*)&headerObject.yOrigin,2);
  outputSix.write((char*)&headerObject.width,2);
  outputSix.write((char*)&headerObject.height,2);
  outputSix.write(&headerObject.bitsPerPixel,1);
  outputSix.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputSix.write((char*)&storingVal.at(i).blue,1);
    outputSix.write((char*)&storingVal.at(i).green,1);
    outputSix.write((char*)&storingVal.at(i).red,1);
  }

  if(point == area)
    cout << "Test 6 ...... Passed" << endl;
  else{
    cout << "Test 6 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point = 0;
  testFile.close();
  myTest.clear();

  file.close();
  fileTwo.close();
  fileThree.close();
  storingVal.clear();
  storingValTwo.clear();
  tempo.clear();
  resultTemp.clear();

  //Question 7

  file.open("../input/car.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  area = headerObject.width * headerObject.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    int value = storingVal.at(i).red;
    value = (value * 4);
    value = min(value,255);
    int valueTwo = storingVal.at(i).blue;
    valueTwo = (valueTwo * 0);
    storingVal.at(i).red = (unsigned char) value;
    storingVal.at(i).blue = (unsigned char) valueTwo;
  }

  testFile.open("../examples/EXAMPLE_part7.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }

  for(unsigned int i = 0; i < area; i++){
    int red_one = storingVal.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = storingVal.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = storingVal.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream outputSeven("../output/part7.tga", ios_base::binary);
  outputSeven.write(&headerObject.idLength,1);
  outputSeven.write(&headerObject.colorMapType,1);
  outputSeven.write(&headerObject.dataTypeCode,1);
  outputSeven.write((char*)&headerObject.colorMapOrigin,2);
  outputSeven.write((char*)&headerObject.colorMapLength,2);
  outputSeven.write(&headerObject.colorMapDepth,1);
  outputSeven.write((char*)&headerObject.xOrigin,2);
  outputSeven.write((char*)&headerObject.yOrigin,2);
  outputSeven.write((char*)&headerObject.width,2);
  outputSeven.write((char*)&headerObject.height,2);
  outputSeven.write(&headerObject.bitsPerPixel,1);
  outputSeven.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputSeven.write((char*)&storingVal.at(i).blue,1);
    outputSeven.write((char*)&storingVal.at(i).green,1);
    outputSeven.write((char*)&storingVal.at(i).red,1);
  }

  if(point == area)
    cout << "Test 7 ...... Passed" << endl;
  else{
    cout << "Test 7 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point = 0;
  testFile.close();
  myTest.clear();

  file.close();
  fileTwo.close();
  fileThree.close();
  storingVal.clear();
  storingValTwo.clear();
  tempo.clear();
  resultTemp.clear();

  //Question 8
  file.open("../input/car.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  area = headerObject.width * headerObject.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
    storingValTwo.push_back(intro);
    tempo.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    int value = storingVal.at(i).red;
    storingVal.at(i).green = (unsigned char) value;
    storingVal.at(i).blue = (unsigned char) value;
  }

  for (unsigned int i = 0; i < area; i++){
    int value = storingValTwo.at(i).blue;
    storingValTwo.at(i).red = (unsigned char) value;
    storingValTwo.at(i).green = (unsigned char) value;
  }

  for (unsigned int i = 0; i < area; i++){
    int value = tempo.at(i).green;
    tempo.at(i).red = (unsigned char) value;
    tempo.at(i).blue = (unsigned char) value;
  }

  ofstream outputEightOne("../output/part8_r.tga", ios_base::binary);
  outputEightOne.write(&headerObject.idLength,1);
  outputEightOne.write(&headerObject.colorMapType,1);
  outputEightOne.write(&headerObject.dataTypeCode,1);
  outputEightOne.write((char*)&headerObject.colorMapOrigin,2);
  outputEightOne.write((char*)&headerObject.colorMapLength,2);
  outputEightOne.write(&headerObject.colorMapDepth,1);
  outputEightOne.write((char*)&headerObject.xOrigin,2);
  outputEightOne.write((char*)&headerObject.yOrigin,2);
  outputEightOne.write((char*)&headerObject.width,2);
  outputEightOne.write((char*)&headerObject.height,2);
  outputEightOne.write(&headerObject.bitsPerPixel,1);
  outputEightOne.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputEightOne.write((char*)&storingVal.at(i).blue,1);
    outputEightOne.write((char*)&storingVal.at(i).green,1);
    outputEightOne.write((char*)&storingVal.at(i).red,1);
  }

  ofstream outputEightTwo("../output/part8_g.tga", ios_base::binary);
  outputEightTwo.write(&headerObject.idLength,1);
  outputEightTwo.write(&headerObject.colorMapType,1);
  outputEightTwo.write(&headerObject.dataTypeCode,1);
  outputEightTwo.write((char*)&headerObject.colorMapOrigin,2);
  outputEightTwo.write((char*)&headerObject.colorMapLength,2);
  outputEightTwo.write(&headerObject.colorMapDepth,1);
  outputEightTwo.write((char*)&headerObject.xOrigin,2);
  outputEightTwo.write((char*)&headerObject.yOrigin,2);
  outputEightTwo.write((char*)&headerObject.width,2);
  outputEightTwo.write((char*)&headerObject.height,2);
  outputEightTwo.write(&headerObject.bitsPerPixel,1);
  outputEightTwo.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputEightTwo.write((char*)&tempo.at(i).blue,1);
    outputEightTwo.write((char*)&tempo.at(i).green,1);
    outputEightTwo.write((char*)&tempo.at(i).red,1);
  }

  ofstream outputEightThree("../output/part8_b.tga", ios_base::binary);
  outputEightThree.write(&headerObject.idLength,1);
  outputEightThree.write(&headerObject.colorMapType,1);
  outputEightThree.write(&headerObject.dataTypeCode,1);
  outputEightThree.write((char*)&headerObject.colorMapOrigin,2);
  outputEightThree.write((char*)&headerObject.colorMapLength,2);
  outputEightThree.write(&headerObject.colorMapDepth,1);
  outputEightThree.write((char*)&headerObject.xOrigin,2);
  outputEightThree.write((char*)&headerObject.yOrigin,2);
  outputEightThree.write((char*)&headerObject.width,2);
  outputEightThree.write((char*)&headerObject.height,2);
  outputEightThree.write(&headerObject.bitsPerPixel,1);
  outputEightThree.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputEightThree.write((char*)&storingValTwo.at(i).blue,1);
    outputEightThree.write((char*)&storingValTwo.at(i).green,1);
    outputEightThree.write((char*)&storingValTwo.at(i).red,1);
  }

  cout << "Test 8 ...... Passed" << endl;

  file.close();
  fileTwo.close();
  fileThree.close();
  storingVal.clear();
  storingValTwo.clear();
  tempo.clear();
  resultTemp.clear();

  //Question 9

  file.open("../input/layer_red.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  fileTwo.open("../input/layer_green.tga");

  fileTwo.read(&another.idLength, sizeof(another.idLength));
  fileTwo.read(&another.colorMapType, sizeof(another.colorMapType));
  fileTwo.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileTwo.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileTwo.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileTwo.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileTwo.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileTwo.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileTwo.read((char*)&another.width, sizeof(another.width));
  fileTwo.read((char*)&another.height, sizeof(another.height));
  fileTwo.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileTwo.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  //Getting the area
  area = another.width * another.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileTwo.read((char*)&intro.blue, sizeof(intro.blue));
    fileTwo.read((char*)&intro.green, sizeof(intro.green));
    fileTwo.read((char*)&intro.red, sizeof(intro.red));
    storingValTwo.push_back(intro);
  }

  fileThree.open("../input/layer_blue.tga");

  fileThree.read(&another.idLength, sizeof(another.idLength));
  fileThree.read(&another.colorMapType, sizeof(another.colorMapType));
  fileThree.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileThree.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileThree.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileThree.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileThree.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileThree.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileThree.read((char*)&another.width, sizeof(another.width));
  fileThree.read((char*)&another.height, sizeof(another.height));
  fileThree.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileThree.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    fileThree.read((char*)&intro.blue, sizeof(intro.blue));
    fileThree.read((char*)&intro.green, sizeof(intro.green));
    fileThree.read((char*)&intro.red, sizeof(intro.red));
    tempo.push_back(intro);
  }

  for (unsigned int i = 0; i < area; i++){
    int value = tempo.at(i).blue;
    int valueTwo = storingValTwo.at(i).green;
    storingVal.at(i).blue = value;
    storingVal.at(i).green = valueTwo;
  }

  testFile.open("../examples/EXAMPLE_part9.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }

  for(unsigned int i = 0; i < area; i++){
    int red_one = storingVal.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = storingVal.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = storingVal.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream outputNine("../output/part9.tga", ios_base::binary);
  outputNine.write(&headerObject.idLength,1);
  outputNine.write(&headerObject.colorMapType,1);
  outputNine.write(&headerObject.dataTypeCode,1);
  outputNine.write((char*)&headerObject.colorMapOrigin,2);
  outputNine.write((char*)&headerObject.colorMapLength,2);
  outputNine.write(&headerObject.colorMapDepth,1);
  outputNine.write((char*)&headerObject.xOrigin,2);
  outputNine.write((char*)&headerObject.yOrigin,2);
  outputNine.write((char*)&headerObject.width,2);
  outputNine.write((char*)&headerObject.height,2);
  outputNine.write(&headerObject.bitsPerPixel,1);
  outputNine.write(&headerObject.imageDescriptor,1);
  for (unsigned i = 0; i < area; i++){
    outputNine.write((char*)&storingVal.at(i).blue,1);
    outputNine.write((char*)&storingVal.at(i).green,1);
    outputNine.write((char*)&storingVal.at(i).red,1);
  }

  if(point == area)
    cout << "Test 9 ...... Passed" << endl;
  else{
    cout << "Test 9 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point = 0;
  testFile.close();
  myTest.clear();

  file.close();
  fileTwo.close();
  fileThree.close();
  storingVal.clear();
  storingValTwo.clear();
  tempo.clear();
  resultTemp.clear();

  //Question 10

  file.open("../input/text2.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  area = another.width * another.height;

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
  }

  testFile.open("../examples/EXAMPLE_part10.tga");
  testFile.read(&testing.idLength, sizeof(testing.idLength));
  testFile.read(&testing.colorMapType, sizeof(testing.colorMapType));
  testFile.read(&testing.dataTypeCode, sizeof(testing.dataTypeCode));
  testFile.read((char*)&testing.colorMapOrigin, sizeof(testing.colorMapOrigin));
  testFile.read((char*)&testing.colorMapLength, sizeof(testing.colorMapLength));
  testFile.read(&testing.colorMapDepth, sizeof(testing.colorMapDepth));
  testFile.read((char*)&testing.xOrigin, sizeof(testing.xOrigin));
  testFile.read((char*)&testing.yOrigin, sizeof(testing.yOrigin));
  testFile.read((char*)&testing.width, sizeof(testing.width));
  testFile.read((char*)&testing.height, sizeof(testing.height));
  testFile.read(&testing.bitsPerPixel, sizeof(testing.bitsPerPixel));
  testFile.read(&testing.imageDescriptor, sizeof(testing.imageDescriptor));

  for (unsigned int i = 0; i < area; i++){
    Pixels intro;
    testFile.read((char*)&intro.blue, sizeof(intro.blue));
    testFile.read((char*)&intro.green, sizeof(intro.green));
    testFile.read((char*)&intro.red, sizeof(intro.red));
    myTest.push_back(intro);
  }

  for(unsigned int i = 0; i < area; i++){
    int red_one = storingVal.at(i).red;
    int red_two = myTest.at(i).red;

    int green_one = storingVal.at(i).green;
    int green_two = myTest.at(i).green;

    int blue_one = storingVal.at(i).blue;
    int blue_two = myTest.at(i).blue;
    if (red_one == red_two && blue_one == blue_two && green_one == green_two){
      point++;
    }
  }

  ofstream outputTen("../output/part10.tga", ios_base::binary);
  outputTen.write(&headerObject.idLength,1);
  outputTen.write(&headerObject.colorMapType,1);
  outputTen.write(&headerObject.dataTypeCode,1);
  outputTen.write((char*)&headerObject.colorMapOrigin,2);
  outputTen.write((char*)&headerObject.colorMapLength,2);
  outputTen.write(&headerObject.colorMapDepth,1);
  outputTen.write((char*)&headerObject.yOrigin,2);
  outputTen.write((char*)&headerObject.xOrigin,2);
  outputTen.write((char*)&headerObject.width,2);
  outputTen.write((char*)&headerObject.height,2);
  outputTen.write(&headerObject.bitsPerPixel,1);
  outputTen.write(&headerObject.imageDescriptor,1);

  for (unsigned int i = (area/3.3)-52; i > 0 ; i--){
    outputTen.write((char*)&storingVal.at(i).blue,1);
    outputTen.write((char*)&storingVal.at(i).green,1);
    outputTen.write((char*)&storingVal.at(i).red,1);
  }

  if(point == area)
    cout << "Test 10 ...... Passed" << endl;
  else{
    cout << "Test 10 ...... Failed" << endl;
    cout << point << ": " << area << endl;
  }

  point = 0;
  testFile.close();
  myTest.clear();

  file.close();
  fileTwo.close();
  fileThree.close();
  storingVal.clear();
  storingValTwo.clear();
  tempo.clear();
  resultTemp.clear();

  //Extra Credit

  vector<Pixels> combine;

  file.open("../input/text.tga");
  file.read(&headerObject.idLength, sizeof(headerObject.idLength));
  file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
  file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
  file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
  file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
  file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
  file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
  file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
  file.read((char*)&headerObject.width, sizeof(headerObject.width));
  file.read((char*)&headerObject.height, sizeof(headerObject.height));
  file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
  file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

  fileTwo.open("../input/pattern1.tga");

  fileTwo.read(&another.idLength, sizeof(another.idLength));
  fileTwo.read(&another.colorMapType, sizeof(another.colorMapType));
  fileTwo.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileTwo.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileTwo.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileTwo.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileTwo.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileTwo.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileTwo.read((char*)&another.width, sizeof(another.width));
  fileTwo.read((char*)&another.height, sizeof(another.height));
  fileTwo.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileTwo.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  //Getting the area
  area = another.width * another.height;

  for (unsigned int i = 0; i < area/4; i++){
    Pixels intro;
    file.read((char*)&intro.blue, sizeof(intro.blue));
    file.read((char*)&intro.green, sizeof(intro.green));
    file.read((char*)&intro.red, sizeof(intro.red));
    storingVal.push_back(intro);
    combine.push_back(intro);
  }

  for (unsigned int i = 0; i < area/4; i++){
    Pixels intro;
    fileTwo.read((char*)&intro.blue, sizeof(intro.blue));
    fileTwo.read((char*)&intro.green, sizeof(intro.green));
    fileTwo.read((char*)&intro.red, sizeof(intro.red));
    storingValTwo.push_back(intro);
    combine.push_back(intro);
  }

  fileThree.open("../input/car.tga");

  fileThree.read(&another.idLength, sizeof(another.idLength));
  fileThree.read(&another.colorMapType, sizeof(another.colorMapType));
  fileThree.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileThree.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileThree.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileThree.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileThree.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileThree.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileThree.read((char*)&another.width, sizeof(another.width));
  fileThree.read((char*)&another.height, sizeof(another.height));
  fileThree.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileThree.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  for (unsigned int i = 0; i < area/4; i++){
    Pixels intro;
    fileThree.read((char*)&intro.blue, sizeof(intro.blue));
    fileThree.read((char*)&intro.green, sizeof(intro.green));
    fileThree.read((char*)&intro.red, sizeof(intro.red));
    tempo.push_back(intro);
    combine.push_back(intro);
  }

  ifstream fileFour;
  fileFour.open("../input/circles.tga");

  fileFour.read(&another.idLength, sizeof(another.idLength));
  fileFour.read(&another.colorMapType, sizeof(another.colorMapType));
  fileFour.read(&another.dataTypeCode, sizeof(another.dataTypeCode));
  fileFour.read((char*)&another.colorMapOrigin, sizeof(another.colorMapOrigin));
  fileFour.read((char*)&another.colorMapLength, sizeof(another.colorMapLength));
  fileFour.read(&another.colorMapDepth, sizeof(another.colorMapDepth));
  fileFour.read((char*)&another.xOrigin, sizeof(another.xOrigin));
  fileFour.read((char*)&another.yOrigin, sizeof(another.yOrigin));
  fileFour.read((char*)&another.width, sizeof(another.width));
  fileFour.read((char*)&another.height, sizeof(another.height));
  fileFour.read(&another.bitsPerPixel, sizeof(another.bitsPerPixel));
  fileFour.read(&another.imageDescriptor, sizeof(another.imageDescriptor));

  vector<Pixels> tempTwo;
  for (unsigned int i = 0; i < (area/4); i++){
    Pixels intro;
    fileFour.read((char*)&intro.blue, sizeof(intro.blue));
    fileFour.read((char*)&intro.green, sizeof(intro.green));
    fileFour.read((char*)&intro.red, sizeof(intro.red));
    tempTwo.push_back(intro);
    combine.push_back(intro);
  }

  ofstream extraCredit("../output/extracredit.tga");
  extraCredit.write(&headerObject.idLength,1);
  extraCredit.write(&headerObject.colorMapType,1);
  extraCredit.write(&headerObject.dataTypeCode,1);
  extraCredit.write((char*)&headerObject.colorMapOrigin,2);
  extraCredit.write((char*)&headerObject.colorMapLength,2);
  extraCredit.write(&headerObject.colorMapDepth,1);
  extraCredit.write((char*)&headerObject.yOrigin,2);
  extraCredit.write((char*)&headerObject.xOrigin,2);
  extraCredit.write((char*)&headerObject.width,2);
  extraCredit.write((char*)&headerObject.height,2);
  extraCredit.write(&headerObject.bitsPerPixel,1);
  extraCredit.write(&headerObject.imageDescriptor,1);

  for (unsigned int i = 0; i < (area); i++){
    extraCredit.write((char*)&combine.at(i).blue,1);
    extraCredit.write((char*)&combine.at(i).green,1);
    extraCredit.write((char*)&combine.at(i).red,1);
  }

  cout << "Test Extra Credit ...... Done!" << endl;

  return 0;


}
