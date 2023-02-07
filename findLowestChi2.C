/**********************************************************************************
Comments
***********************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
//#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

int findLowestChi2 (/*const char* dir,*/ int ndf /*, const char* dataset*/)
{
    //double NDF = 9; 
    double sum=0.0;
    double average=0.0;
    double Eshift = 0; 
    double SNF = 0; 

    float xNumber=0; float yNumber=0; float zNumber=0;
    int numbers=0;
    double lowest = 5000;
    double highest = 5002;
    
    ifstream randomFile;
    randomFile.open("OutDirChi2_2p2To2p7_fs/chi2_energyshift_run6_overlay.txt" );

    //randomFile.open(Form("%s/chi2_energyshift_%s.txt", dir, dataset) );
    
    if (randomFile.fail())
        cout << "File cannot be opened.";
   
	else
    {
    
        while (randomFile >> xNumber >> yNumber >> zNumber){
       //cout<<xNumber <<" "<< yNumber<<" "<< zNumber<<endl;  
                if (zNumber > highest ) 
			{
			highest = zNumber ;
			}
			
		else if(zNumber < lowest ) 
			{
			lowest = zNumber;
			Eshift = xNumber;
			   SNF = yNumber;
			}
        {
            numbers++;
            sum+=zNumber;
        }
        
        if (numbers>0)
            {
			average = sum/numbers;
			}
        else
            average=0.0;
    }	
       // cout << "The number of numbers is: " << numbers << endl;
      //  cout << "The sum of the numbers is: " << sum << endl;
      //  cout << "The average of the numbers is: " << average << endl;
                cout << "NDF: " << ndf << endl;
      	        cout << "Lowest Chi2 : " << lowest << endl;
		cout << "Lowest Chi2/NDF : " << lowest/ndf << endl;
		cout << "Energy shift: "<<Eshift<<" %"<<endl; 
		cout << "Spectrum Norm Factor: "<<SNF<<endl; 

		cout << "Summary: "<<setprecision(3) << ndf<<"\t"<<lowest<<"\t"<<lowest/ndf<<"\t"<<Eshift<<" %\t"<<SNF<<"\t"<< endl;
                cout << "Summary: "<<setprecision(3) << ndf<<"\t"<<lowest<<"\t"<<lowest/ndf<<"\t"<<Eshift<<" "<<SNF<<"\t"<< endl;

    }//<-- else
	cin.ignore().get();
    return 0;
}
