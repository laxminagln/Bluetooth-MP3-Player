float temp,light;
const int tempPin=A0;
const int lightPin=A1;
char toSend;
void setup()
{
  analogReference(INTERNAL);
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  for(int i=0;i<2;i++)
  {
   digitalWrite(13,HIGH);
   delay(500);
   digitalWrite(13,LOW);
   delay(500);   
  }
  digitalWrite(13,HIGH);
  delay(2000);
  digitalWrite(13,LOW);
}

void loop()
{

  temp = analogRead(tempPin)/9.31;
  //Serial.print("TEMPRATURE = ");
  //Serial.println(temp);
  //Serial.println("*C");
  delay(1000);
  light= analogRead(lightPin);
  light=map(light,0,1023,0,100);
  //Serial.print("LIGHT = ");
  //Serial.println(light);
  //Serial.println("%");
  decide(light,temp);

}
/*
Light Scaling    Temp Scaling
HIGH: 80%-100%      >=31'C  
MED: 40%-79%        <=30'C & >=24'C(room temperature)
LOW: 0%-39%         <=23'C
*/
void decide(float l_read, float t_read)
  {
    if((l_read>=80 && t_read>=31.0) || (l_read>=80 && (t_read<=30.0 && t_read>=24.0)) || ((l_read>=40&& l_read<=79) && t_read>=31.0))  
    //if  light and temp is high    or      light is high and temp is med             or         light is med and temp is high 
    Serial.write(3);    //means red, the raw data that needs another decision process in you android app
    else if((l_read>=80 && t_read<=23.0) || (l_read<=39 && t_read>=31.0) || ((l_read>=40&& l_read<=79) && (t_read<=30.0 && t_read>=24.0)))
 //if light is high and temp is low  or  if light is low and temp is high or      both med
    Serial.write(2);    //means GREEN
    else if(((l_read<=79 && l_read>=40.0) && t_read<=23.0) || (l_read<=39 && (t_read<=30.0 && t_read>=24.0)) || (l_read<=39 && t_read<=23.0))
    //if light is med and temp is low                or        light is low and temp is med                if both low
    Serial.write(1);  //means blue
  }
