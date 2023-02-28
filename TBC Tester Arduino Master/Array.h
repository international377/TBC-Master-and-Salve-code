//Arrays below listed the closed circuit in different MODE selector and TBC
//In the second dimension of the 2D array {A,B}, A is the Output pin number and B is the Input pin number

//SD MODE

int SD_Close[14][2]= {
  {2,4},{18,19},{7,8},{20,22},{23,25},{37+50,38+50}, {34+50, 44+50}, {15,17}, {41,42},{9+50,29+50}, {9+50,30+50},{9+50,31+50},{9+50,32+50},{9+50,33+50}
};

int AUTO_Close[16][2]= {
  {1,3},{5,6},{5,21},{5,24},{34+50,44+50},{15,17}, {30, 31}, {7+50,45}, {7+50,47},{39+50,42+50}, {34+50,35+50},{9+50,28+50}, {9+50,29+50}, {9+50,30+50}, {9+50,31+50}, {9+50,32+50} 
};

int CM_Close[16][2]= {
  {1,3},{5,6},{5,21},{5,24},{34+50,44+50},{49+50,16}, {30, 31}, {7+50,45}, {7+50,46}, {34+50,35+50}, {39+50,41+50}, {9+50,28+50}, 
  {9+50,29+50}, {9+50,30+50}, {9+50,31+50}, {9+50,33+50} 
};

int FOR_Close[25][2]= {
  {1,3},{5,6},{5,21},{5,24},{27,28},{10,11}, {12, 13}, {49+50,16}, {30,31}, {32,33}, {34,35}, {36,37}, {38,39}, {7+50,45},{7+50,49} , 
  {34+50,35+50}, {39+50,40+50}, {39+50,41+50}, {46+50,50+50}, {9+50,28+50}, {9+50,29+50}, {9+50,30+50}, {11+50,8+50}, {9+50,32+50}, {9+50,33+50}
};

int SB_Close[15][2]= {
  {1,3},{5,6},{5,21},{5,24},{34+50,44+50},{15,17}, {34, 35}, {36,37}, {7+50,45}, {7+50,50}, {9+50,28+50}, 
  {9+50,29+50}, {9+50,31+50}, {9+50,32+50}, {9+50,33+50} 
};

int REV_Close[24][2]= {
  {1,3},{5,6},{5,21},{5,24},{27,28},{10,11}, {12, 13}, {49+50,16}, {30,31}, {32,33}, {34,35}, {36,37}, {38,39}, {7+50,45},{7+50,48} , 
  {34+50,36+50}, {39+50,40+50}, {39+50,41+50}, {46+50,47+50}, {9+50,28+50}, {9+50,30+50}, {9+50,31+50}, {9+50,32+50}, {9+50,33+50}
};


// TBC Selector

int Brake_Max_Close[4][2]= {
  {16+50,17+50}, {1+50,3+50}, {5+50,6+50}, {12+50,13+50}
};

int Brake_Min_Close[3][2]= {
  {1+50,3+50}, {5+50,6+50}, {12+50,13+50}
};

int Coasting_Close[3][2]= {
  {25+50,26+50}, {5+50,6+50}, {12+50,13+50}
};

int Motor_Min_Close[4][2]= {
  {25+50,26+50}, {1+50,2+50}, {5+50,6+50}, {12+50,13+50}
};

int Motor_Max_Close[4][2]= {
  {25+50,26+50}, {1+50,2+50}, {5+50,6+50}, {12+50,13+50}
};

int Em_Brake_Close[3][2]= {
  {16+50,17+50}, {14+50,15+50}, {9+50,4+50}
};