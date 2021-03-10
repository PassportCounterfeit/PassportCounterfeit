#include <iostream>
#include "JPN.h"
#include "IND.h"
#include "BRA.h"
#include "ESP.h"
#include "MEX.h"
#include "TUR.h"
#include "ARG.h"
using namespace std;

const string imagePath = "ARG//P5//";

int main()
{
    cout << ARG_P5(dataPath + imagePath + "UV.jpg",dataPath + imagePath + "WI.jpg",dataPath + imagePath + "IR.jpg") << endl;
}


