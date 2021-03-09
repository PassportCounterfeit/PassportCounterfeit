#include <iostream>
#include "JPN.h"
#include "IND.h"
#include "BRA.h"
#include "ESP.h"
#include "MEX.h"
#include "TUR.h"
using namespace std;

const string dataPath = "F://研究生阶段//实验室//护照鉴伪//pretreatment_data//";
const string imagePath = "TUR//P2//";

int main()
{
    cout << TUR_P2(dataPath + imagePath + "UV.jpg",dataPath + imagePath + "WI.jpg",dataPath + imagePath + "IR.jpg") << endl;
}


