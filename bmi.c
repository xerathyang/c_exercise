#include <stdio.h>

int main(void){
	float WeightInKilograms, HeightInMeters, Bmi;
	int check =1;
	
	while(check !=0){
	
	printf("enter weight and height, divide by space\n");
	
	scanf("%f %f", &WeightInKilograms, &HeightInMeters);
	
	Bmi = WeightInKilograms / HeightInMeters / HeightInMeters;
	
	printf("%f\n",Bmi);
	
	if(Bmi< 18.5){
		puts("UnderWeight");
	}else if(Bmi< 24.9){
		puts("Normal");
	}else if(Bmi< 29.9){
		puts("Overweight");
	}else{
		puts("Obese");
	}
	
	scanf("%d",&check);
	}
}