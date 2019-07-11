/*ANIL AKBULUT 151044029 HW4*/

#include <stdio.h>			/*used libraries*/
#include <string.h>			
#define LENGHT 1000			/*used global values*/
#define MAX_NUM 100

double calculate_pow(double x,int y);

double calculate_pow(double x,int y) /* calculated x^y*/
{
	int i;
	double result=1;
	for(i=0;i<y;i++)
	{
		result = result * x;
	}
	return result;
}
int main()
{
	FILE *fp1,*fp2,*fp3;					
	int i=0,j=0,k=0,space=0,sign,status;
	double d2,d5,result=0;
	char d3,d4;
	double values[MAX_NUM],values_x;
	char polynomical[LENGHT];
	char clean_poly[LENGHT];
	char b[LENGHT];
	char *p,arr[100];
	fp1 = fopen("values.txt", "r");			/*file open operations*/	
	fp2 = fopen("polynomial.txt", "r");		/* values and polynomial read operation*/
	fp3 = fopen("evaluations.txt", "w+");	/* evaluations file writed	*/
	while(fscanf(fp2 , "%c" , &polynomical[j]) != EOF) /* with fscanf function, numbers read from values.txt*/
	{ 	
		j++;
	}
	j=0;
	for(space=0;space<LENGHT;space++)	/*polynom.txt cleared from blanks  */
	{
		if(polynomical[space]!=' ')
		{
			clean_poly[j]=polynomical[space];
			j++;
		}
	}
	strcpy(b,clean_poly); 		/* clean_poly copy to b array*/
	k=0;j=0;
	while(clean_poly[k]!='\0') /* if clean_poly not end of file,continue*/
	{
		if(k==0 && clean_poly[k]!='-')
		{
			b[j]='+';
			j++;
		}
		else if(clean_poly[k]=='+' || clean_poly[k]=='-')
		{
			b[j]=clean_poly[k];
			j++;
		}
		k++;
	}
	b[j]='\0';  /* b array is hide index +- */
	i=0;
	while(fscanf(fp1,"%lf",&values[i])!=EOF)  
	{
		values_x=values[i];
		j=0;
		strcpy(clean_poly,polynomical);
		k=0;
		result=0;
		p=strtok(clean_poly,"+-");
		while(p!=NULL)
		{
			strcpy(arr,p);
			status=sscanf(arr,"%lf%c%c%lf",&d2,&d3,&d4,&d5);
			if (arr[0]=='x')
			{
				status=sscanf(arr,"%c%c%lf",&d3,&d4,&d5);
			}
			if (d3=='\n')
			{
				status=1;
			}
			if (d2==0 && d3=='x' && d4=='\n')
			{
				status=1;
			}
			if (d2!=0 && d3=='x' && d4=='\n')
			{
				status=2;
			}
			if (d2==0 && d3=='x' && d4=='^')
			{
				status=3;
			}
			if(status==4) 
			{
				if(b[j]=='-')
				{
					 sign=-1;	
				}
				else sign = 1;
				result = result + (sign)*(d2)*(calculate_pow(values_x,d5));
			}
			if(status==3)
			{
				if(b[j]=='-')
				{
					sign=-1;
					
				}
				else sign = 1;
				result = result + (sign)*(calculate_pow(values_x,d5));
			}
			if(status==2)
			{
				if(b[j]=='-')
				{
					sign=-1;
				}
				else sign = 1;
				result = result + (sign)*(d2)*(values_x);
			}
			if(status==1)
			{
				if(d2==0) 
				{
					if(b[j]=='-')
					{
						sign=-1;
					}
					else sign = 1;
					result = result + (sign)*(values_x);
				}
				else  
				{
					if(b[j]=='-')
					{
						sign=-1;
					}
					else sign = 1;
					result= result + (sign)* (d2);
				}
			}
			j++;	
			p=strtok(NULL,"+-");
		}
		i++;
		fprintf(fp3,"%.2lf\n",result);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}