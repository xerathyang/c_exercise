#include <stdio.h>

int main(){
	int workhour= 0;
	float hourlyrate, salary= 0;
	
	printf("Enter # of hours worked(-1 to end): ");
	scanf("%d",&workhour);
	
	while(workhour != -1){
		printf("Enter # of hours worked(-1 to end): ");
		scanf("%d",&workhour);
	
		printf("Enter hourly rate of the worker($00.00): ");
		scanf("%f",&hourlyrate);
		if(workhour<=40){
			salary = workhour* hourlyrate;
		}else{
			salary = 40* hourlyrate + (workhour-40)* hourlyrate * 1.5;
		}
		printf("Salary is $%.2f", salary);
		puts("");
		puts("");
		
		printf("Enter # of hours worked(-1 to end): ");
		scanf("%d",&workhour);
	}
	
}