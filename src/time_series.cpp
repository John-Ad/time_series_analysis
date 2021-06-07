#include "time_series.h"

TimeSeries::TimeSeries(){
    cout<<"enter n: "<<endl;
    cin>>n;

    y=new double[(int)n];
    x=new double[(int)n];
    x2=new double[(int)n];
    xy=new double[(int)n];

    x4values=new double[(int)(n-3)];
    x2values=new double[(int)(n-4)];
    movingAvgs=new double[(int)(n-4)];
    seasonalRatios=new double[(int)(n-4)];
    medSeasonalIndices=new double[(int)4];
    adjustedSeasonalIndices=new double[(int)4];
    deSeasonalizedY=new double[(int)n];

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

void TimeSeries::calculateUncenteredCenteredValues(){
    // x4=13 offset=3 x2=12 offset=4

    // 4x moving avg
    cout<<endl<<"4x sums: "<<endl;
    for(int i=0;i<n-3;i++){
        x4values[i]=0;
        for(int e=i;e<i+4;e++){
            x4values[i]+=y[e];
        }
        cout<<x4values[i]<<endl;
    }

    cout<<endl<<endl;

    // 2x moving avg
    cout<<endl<<"2x sums: "<<endl;
    for(int i=0;i<n-4;i++){
        x2values[i]=0;
        for(int e=i;e<i+2;e++){
            x2values[i]+=x4values[e];
        }
        cout<<x2values[i]<<endl;
    }



}
void TimeSeries::calculateMovingAvgs(){
    // we are currently only working with n=16
    // the offset=4 // only 12 y values get seasonal indices
    cout<<endl<<"moving averages: "<<endl;

    for(int i=0;i<n-4;i++){
        movingAvgs[i]=x2values[i]/(2*4);   // 4 because there are 4 quarters

        cout<<movingAvgs[i]<<endl;
    }
}
void TimeSeries::calculateSeasonalRatios(){
    cout<<endl<<"seasonal ratios: "<<endl;

    for(int i=0;i<n-4;i++){
        seasonalRatios[i]=y[i+2]/movingAvgs[i]*100;    // +2 because 1st and last 2 dont have mving avg 

        cout<<seasonalRatios[i]<<endl;
    }
}

void TimeSeries::calculateMedIndices(){
    cout<<endl<<"median seasonal indices: "<<endl;

    vector<vector<double>>arr;
    Quicksort quicksort;

    for(int i=0;i<4;i++){
        arr.push_back(vector<double>());
        for(int e=i;e<n-4;e+=4){
            arr[i].push_back(seasonalRatios[e]);
        }

        quicksort.sort(arr[i],0,arr[i].size()-1);

        cout<<endl;
        for(int f=0;f<arr[i].size();f++){
            cout<<arr[i][f]<<", ";
        }
        cout<<endl;

        if(arr[i].size()%2==0){
            medSeasonalIndices[i]=(arr[i][arr[i].size()/2]+arr[i][(arr[i].size()/2)-1])/2;
        }else{
            medSeasonalIndices[i]=arr[i][arr[i].size()/2];
        }

        cout<<medSeasonalIndices[i]<<endl;
    }

}

void TimeSeries::calculateAdjustedSeasonalIndices(){
    cout<<endl<<"adjusted season indices: "<<endl;

    double sum=0;
    for(int i=0;i<4;i++){
        sum+=medSeasonalIndices[i];
    }

    for(int i=0;i<4;i++){
        adjustedSeasonalIndices[i]=(4*100)/sum*medSeasonalIndices[i];
        cout<<adjustedSeasonalIndices[i]<<endl;
    }
}

void TimeSeries::calculateDeSeasonalizedVals(){
    cout<<endl<<"deasonalized values: "<<endl;
    int counter=2;  // q1 value starts at position 2
    for(int i=0;i<n;i++){
        if(counter>3)
            counter=0;

        deSeasonalizedY[i]=y[i]/adjustedSeasonalIndices[counter]*100;
        cout<<deSeasonalizedY[i]<<endl;

        counter++;
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
