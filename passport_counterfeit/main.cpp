#include <iostream>
#include "JPN.h"
#include "IND.h"
#include "BRA.h"
#include "ESP.h"
#include "MEX.h"
using namespace std;

const string dataPath = "F://研究生阶段//实验室//护照鉴伪//pretreatment_data//";
const string imagePath = "JPN//P3//";

int main()
{
    cout << JPN_P3(dataPath + imagePath + "UV.jpg",dataPath + imagePath + "WI.jpg",dataPath + imagePath + "IR.jpg") << endl;
}


