#include "time_series.h"

TimeSeries::TimeSeries(){
    cout<<"enter n: "<<endl;
    cin>>n;

    y=new double[(int)n];
    x=new double[(int)n];
    x2=new double[(int)n];
    xy=new double[(int)n];

    x4MovingAvgs=new double[(int)(n-3)];
    x2MovingAvgs=new double[(int)(n-4)];
    seasonalIndices=new double[(int)(n-4)];
    seasonalRatios=new double[(int)(n-4)];

    cout<<"enter data: "<<endl;

    for(int i=0;i<n;i++){
        cin>>y[i];

        x[i]=i+1;
        x2[i]=pow(i+1,2);
        xy[i]=y[i]*x[i];

        xTotal+=x[i];
        yTotal+=y[i];
        x2Total+=x2[i];
        xyTotal+=xy[i];
    }

    calculateGradient();
    calculateYIntercept();
}

void TimeSeries::calculateGradient(){
    gradient=((n*xyTotal)-(xTotal*yTotal))/((n*x2Total)-pow(xTotal,2));
}
void TimeSeries::calculateYIntercept(){
    yIntercept=(yTotal-(gradient*xTotal))/n;
}
void TimeSeries::showTrendEquation(){
    cout<<endl<<"trendline equation: "<<gradient<<"x + "<<yIntercept<<endl;
}
void TimeSeries::calculateTrend(){
    cout<<endl<<"calculate estimate for certain future quarter: "<<endl;
    double k;
    cout<<"enter k: "<<endl;
    cin>>k;

    cout<<(gradient*k)+yIntercept<<endl;
}

void TimeSeries::calculateMovingAvg(){
    // x4=13 offset=3 x2=12 offset=4

    // 4x moving avg
    cout<<endl<<"4x moving avg: "<<endl;
    for(int i=0;i<n-3;i++){
        x4MovingAvgs[i]=0;
        for(int e=i;e<i+4;e++){
            x4MovingAvgs[i]+=y[e];
        }
        cout<<x4MovingAvgs[i]<<endl;
    }

    cout<<endl<<endl;

    // 2x moving avg
    cout<<endl<<"2x moving avg: "<<endl;
    for(int i=0;i<n-4;i++){
        x2MovingAvgs[i]=0;
        for(int e=i;e<i+2;e++){
            x2MovingAvgs[i]+=x4MovingAvgs[e];
        }
        cout<<x2MovingAvgs[i]<<endl;
    }

}
void TimeSeries::calculateSeasonalIndices(){
    // we are currently only working with n=16
    // the offset=4 // only 12 y values get seasonal indices
    cout<<endl<<"seasonal indices: "<<endl;

    for(int i=0;i<n-4;i++){
        seasonalIndices[i]=x2MovingAvgs[i]/(2*4);   // 4 because there are 4 quarters

        cout<<seasonalIndices[i]<<endl;
    }
}
void TimeSeries::calculateSeasonalRatios(){
    cout<<endl<<"seasonal ratios: "<<endl;

    for(int i=0;i<n-4;i++){
        seasonalRatios[i]=y[i+2]/seasonalIndices[i]*100;    // +2 because 1st and last 2 dont have mving avg 

        cout<<seasonalRatios[i]<<endl;
    }
}

void TimeSeries::showMainTable(){
    cout<<"period\t"<<"y\t"<<"x\t"<<"x2\t"<<"xy"<<endl<<endl;

    for(int i=0;i<n;i++){
        cout<<(i+1)%4<<"\t"<<y[i]<<"\t"<<x[i]<<"\t"<<x2[i]<<"\t"<<xy[i]<<endl;

        if((i+1)%4==0)
            cout<<endl;
    }
    cout<<"totals"<<"\t"<<yTotal<<"\t"<<xTotal<<"\t"<<x2Total<<"\t"<<xyTotal<<endl;
}
