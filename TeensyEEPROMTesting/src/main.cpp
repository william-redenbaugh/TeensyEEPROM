#include <Arduino.h>


int8_t addrPins[16] = {14,15,16,17,18,19,20,21,12,11,10,9,13,8,22};
int8_t dataPins[8] = {7,6,5,4,3,2,1,0};
int8_t writeE = 23;

class hexClass{
    public:
        String addr;
        String data;
        hexClass(String Addr, String Data){
            addr = Addr;
            data = Data;
        };
};

hexClass* instruction = new hexClass("f0ff","f0");

String HextoBin(String hex){
  
  String bin;
  for(unsigned i = 0;i < bin.length() - 1;i++){
    if(hex.charAt(i) == 'f'){
      bin.append("1111");
    }else if(hex.charAt(i) == 'e'){
      bin.append("1110");
    }else if(hex.charAt(i) == 'd'){
      bin.append("1101");
    }else if(hex.charAt(i) == 'c'){
      bin.append("1100");
    }else if(hex.charAt(i) == 'b'){
      bin.append("1011");
    }else if(hex.charAt(i) == 'a'){
      bin.append("1010");
    }else if(hex.charAt(i) =='9'){
      bin.append("1001");
    }else if(hex.charAt(i) =='8'){
      bin.append("1000");
    }else if(hex.charAt(i) =='7'){
      bin.append("0111");
    }else if(hex.charAt(i) =='6'){
      bin.append("0110");
    }else if(hex.charAt(i) =='5'){
      bin.append("0101");
    }else if(hex.charAt(i) =='4'){
      bin.append("0100");
    }else if(hex.charAt(i) =='3'){
      bin.append("0011");
    }else if(hex.charAt(i) =='2'){
      bin.append("0010");
    }else if(hex.charAt(i) =='1'){
      bin.append("0001");
    }else if(hex.charAt(i) =='0'){
      bin.append("0000");
    }
  }
  return bin;
}



void write(hexClass* data){

  

  for(unsigned i = 0; i < (sizeof(addrPins) / sizeof(addrPins[0]));i++){
    pinMode(addrPins[i],OUTPUT);
  }

  for(unsigned i = 0; i < (sizeof(dataPins) / sizeof(dataPins[0]));i++){
    pinMode(dataPins[i],OUTPUT);
  }


  String dataBin = HextoBin(data -> data); 
  String addrBin = HextoBin(data -> addr);
 
  //Serial.println(addrBin);
  //Serial.println(dataBin);

  

  for(int i = addrBin.length() - 2;i >= 0;i--){
    if(addrBin.charAt(i) == '1'){
      digitalWrite(addrPins[i],HIGH);
    }else{
      digitalWrite(addrPins[i],LOW);
    }
  }



  for(int i = dataBin.length() - 1;i >= 0;i--){
    
    if(dataBin.charAt(i) == '1'){
      digitalWrite(dataPins[i],HIGH);
    }else{
      digitalWrite(dataPins[i],LOW);
    }
  }

  digitalWrite(writeE,LOW);
  delayNanoseconds(100);
  digitalWrite(writeE,HIGH);
}

String read(hexClass* data){
  for(unsigned i = 0; i < (sizeof(addrPins) / sizeof(addrPins[0]));i++){
    pinMode(addrPins[i],OUTPUT);
  }

  for(unsigned i = 0; i < (sizeof(dataPins) / sizeof(dataPins[0]));i++){
    pinMode(dataPins[i],INPUT);
  }


  String addrBin = HextoBin(data -> addr);
 
  //Serial.println(addrBin);

  for(int i = addrBin.length() - 2;i >= 0;i--){
    if(addrBin.charAt(i) == '1'){
      digitalWrite(addrPins[i],HIGH);
    }else{
      digitalWrite(addrPins[i],LOW);
    }
    
  }

  String input;

  for(unsigned i = 0; i < (sizeof(dataPins) / sizeof(dataPins[0]));i++){
    input += digitalRead(dataPins[i]);
  }

  

  return input;

}


void setup() {
  // put your setup code here, to run once:
pinMode(writeE,OUTPUT);
//digitalWrite(writeE,HIGH);  

Serial.begin(9600);
while(!Serial){}
Serial.println("connected");
 
  //Serial.println(read(instruction));
  /*
  write(new hexClass("5555","aa"));
  delayNanoseconds(100);
  write(new hexClass("2aaa","55"));
  delayNanoseconds(100);
  write(new hexClass("5555","80"));
  delayNanoseconds(100);
  write(new hexClass("5555","aa"));
  delayNanoseconds(100);
  write(new hexClass("2aaa","55"));
  delayNanoseconds(100);
  write(new hexClass("5555","20"));
  delayNanoseconds(100);
  write(new hexClass("0000","ff"));
  delayNanoseconds(100);
  write(new hexClass("0000","fff"));
  delay(1);
  
write(instruction);
*/

  //pinMode(13,OUTPUT);
 // digitalWrite(13,HIGH);
}

void loop() {
  //Serial.println("Read or Write, w/r");
  // put your main code here, to run repeatedly:
 Serial.println(read(instruction));
 delay(100);
}



