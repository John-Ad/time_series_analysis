#include "time_series.h"

int main(){
    TimeSeries tSeries;
    tSeries.showMainTable();        // a)
    tSeries.showTrendEquation();    // b)
    tSeries.calculateMovingAvg();   // c)
    tSeries.calculateSeasonalIndices();
    tSeries.calculateSeasonalRatios(); // end of c)
    tSeries.calculateTrend();
    
    return 0;
}
