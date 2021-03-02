#include <iostream>
#include "JPN.h"
#include "IND.h"
#include "BRA.h"
#include "ESP.h"
#include "MEX.h"
using namespace std;

const string dataPath = "F://研究生阶段//实验室//护照鉴伪//pretreatment_data//";
const string imagePath = "MEX//P5//";

int main()
{
    cout << MEX_P5(dataPath + imagePath + "UV.jpg") << endl;
}


