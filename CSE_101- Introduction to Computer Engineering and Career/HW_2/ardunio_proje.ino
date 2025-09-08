const int greenpin = 11;
const int dus= 13;
int mission,s;
int counter=0;
long k;
int durum=0;



void setup() 
{
  pinMode(greenpin, OUTPUT);
  pinMode(dus, INPUT);
  Serial.begin(9600);
  Serial.setTimeout(15);
 
}

void loop() 
{
    
    while(Serial.available()==0);
    
    
    mission= Serial.parseInt();  
    
      if(mission==1){
    
      digitalWrite(greenpin, HIGH);
      
      }
      if(mission==2){
    
      digitalWrite(greenpin,LOW);
      
      }
      if(mission==3){
    
              int i=0;
              digitalWrite(greenpin,LOW);
              for(i=0; i<3; i++){
                   digitalWrite(greenpin, HIGH);
                   delay(700);
                   digitalWrite(greenpin, LOW);
                   delay(700);
               }
      }
      if (mission==4){
        while(Serial.available()==0);
        s=Serial.parseInt();
        k=(s*s);
        Serial.println(k);
      }
   
        if (mission==5){
        
        while(1){
        if(digitalRead(dus)==1)
        {

        while(digitalRead(dus)==0);
        while(digitalRead(dus)==1);
        
          
        
        
        counter++;
        if(Serial.available()) break;
        Serial.println(counter);
        
        }
        
        }
        
      
      }

}
