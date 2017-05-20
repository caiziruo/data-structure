//
//  main.cpp
//  stack
//
//  Created by caiziruo on 02/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
using namespace std;

#include "mediumtolatter.h"
#include "lattertoresult.h"
#include "check_pascal.h"
int main(int argc, const char * argv[])
{
    z2h exp1("1024/ 2 /2 / 2");
    exp1.result();
    
    // h2result exp2("1 2 + 3 + 4 +");
    // cout << exp2.result() << endl;
    
    // char filename[80];
    // check_pascal * p;
    // int result;
    
    // try{
    //     if (argc == 1)
    //     {
    //         cout << "input the file name:";
    //         cin >> filename;
    //         p = new check_pascal(filename);
    //         result = p -> CheckBalance();
    //         delete p;
    //         cout << result << " errors in total." << endl;
    //         return 0;
    //     }
    //     while (--argc)
    //     {
    //         cout << "checking " << * ++argv << endl;
    //         p = new check_pascal(* argv);
    //         result = p -> CheckBalance();
    //         delete p;
    //         cout << result << " errors in total." << endl;
    //     }
    // }
    // catch (nopascalFile) {cout << "no such file" << endl;}


    return 0;
}
