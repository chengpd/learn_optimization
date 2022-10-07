#include "iostream"
#include "math.h"
#include "ctime"

using namespace std;
float grad_x=0,grad_y=0;
float Rosenbrock(float x,float y);

void  get_grad(float x,float y);
float Armijo(float value,float x,float y,float grad_x,float grad_y,float steep);

int main(int argc,char ** argv){

clock_t start,end;
start = clock();
float x=2,y=5;
int nums =1000000;
float steep = 0.005;
float loss;
float value_current,value_last;
double time;

    for (int i = 0; i < nums; ++i) {
        float last_steep = steep;
        value_last = Rosenbrock(x,y);
        get_grad(x,y);
        if (grad_x>0&&grad_y>0){
            x = x - steep*grad_x;
            y = y - steep*grad_y;
            steep = Armijo(value_current,x,y,-grad_x,-grad_y,steep);
        }
        else if (grad_x>0&&grad_y<0){
            x = x - steep;
            y = y + steep;
            steep = Armijo(value_current,x,y,-grad_x,grad_y,steep);
        }
        else if (grad_x<0&&grad_y>0){
            x = x + steep;
            y = y - steep;
            steep = Armijo(value_current,x,y,grad_x,-grad_y,steep);
        }
        else{
            x = x + steep;
            y = y + steep;
            steep = Armijo(value_current,x,y,grad_x,grad_y,steep);
        }

        value_current = Rosenbrock(x,y);


        loss = value_last - value_last;

        cout<<i<<"    "<< value_last <<"    "<<value_current<<"    "<<grad_x<<"    " <<grad_y<<"    " <<x<<"    " <<y<<"    " <<endl;
        if(grad_x*grad_x+grad_y*grad_y<0.0001){ break;}
    }
end = clock();
    time = (double )(end-start)/CLOCKS_PER_SEC * 1000;
printf("所用时间： %f ms \n",time );

}

float Rosenbrock(float x,float y){
float f_value=0;
f_value = pow(1-x,2)+ 100*pow(y-x*x,2);
return f_value;
}

void get_grad(float x,float y) {
    grad_x = 400* pow(x,3) + (2-400*y)*x-2;
    grad_y = 200*(y-x*x);
}

float Armijo(float value,float x,float y,float grad_x,float grad_y,float steep){
float last_steep = steep;
float beta = 0.666;
float c = 0.3;
float fd = Rosenbrock(x+steep*grad_x, y + steep*grad_y);
float fk = value + steep * c * grad_x * grad_x * grad_y * grad_y;
if (fd > fk){
        steep = beta * steep;
        float fd = Rosenbrock(x+steep*grad_x, y + steep*grad_y);
        float fk = value + steep * c * grad_x * grad_x * grad_y * grad_y;

    }


return  steep;
}
