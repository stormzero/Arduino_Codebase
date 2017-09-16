// Saved by Simulator for Arduino V0.98.C.3 refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98.C.1 refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98.C.1 refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98C refer to arduino.com.au

void setup(){
Serial.begin(9600);
Serial.println("a");
int unsorted[] = {3,2,8,6,-1,5,1,7,4};
//Serial.println("b");
 int sorted[] = bubbleSort(unsorted, 9);
Serial.println("c"); 
}

void loop(){

}


int[] bubbleSort(int numbers[], int array_size)
{
  int i, j, temp;
    Serial.println("bubble");
  for (i = (array_size - 1); i > 0; i--)
  {
    for (j = 1; j <= i; j++)
    {
      if (numbers[j-1] > numbers[j])
      {
        temp = numbers[j-1];
        numbers[j-1] = numbers[j];
        numbers[j] = temp;
      }
    }
  }
printArray(numbers,array_size);

}

void printArray(int[] a, int n){
Serial.println(" === array === ");
for(int i=0; i<n; i++)
   Serial.println(a[i])
}

