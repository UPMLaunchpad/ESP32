
int A = 23; 
int B = 22;
int C = 21;
int GS = 18;

int col= 0;
   
void setup() {
  // put your setup code here, to run once:
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(GS, INPUT);
Serial.begin(115200);
   delay(1000);
   
}

void loop() {
  
col = digitalRead(A)+(10*digitalRead(B))+(100*digitalRead(C));
Serial.println(col);
Serial.println(digitalRead(GS));

    
delay(100);
}
