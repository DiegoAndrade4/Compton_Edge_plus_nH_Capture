
//=====================================================
float Ratio(int&, int&);
float Ratio(int& num, int& den){

float ratio = (float) num / (float) den ;

return ratio ;
}



//====================================================

float RatioStatUnc(int&, int&);
float RatioStatUnc(int& num, int& den){

float ratio = (float) num / (float) den ;

double Enum = sqrt(num) ;
double Eden = sqrt(den) ;

double fracUnc = sqrt( ( (Enum/num)*(Enum/num) ) + ( (Eden/den)*(Eden/den) ) );

double Eratio = fracUnc * ratio ;

//cout<<"BKG RATE ± STAT UNC  =>  "<<rmichels<<" / "<<physicsevents<<" = "<<rate<<" ± "<<Erate<<endl;

return Eratio ;
}









//====================================================
//====================================================

float Ratio(int&, float&);
float Ratio(int& num, float& den){

float ratio = (float) num /  den ;

return ratio ;
}

//====================================================

float RatioStatUnc(int&, float&);
float RatioStatUnc(int& num, float& den){

float ratio = (float) num / den ;

double Enum = sqrt(num) ;
double Eden = sqrt(den) ;

double fracUnc = sqrt( ( (Enum/num)*(Enum/num) ) + ( (Eden/den)*(Eden/den) ) );

double Eratio = fracUnc * ratio ;

//cout<<"BKG RATE ± STAT UNC  =>  "<<rmichels<<" / "<<physicsevents<<" = "<<rate<<" ± "<<Erate<<endl;

return Eratio ;
}




