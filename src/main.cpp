#include "time_series.h"

int main(){
    TimeSeries tSeries;
    tSeries.showMainTable();        // a)
    tSeries.showTrendEquation();    // b)
    tSeries.calculateUncenteredCenteredValues();   // c)
    tSeries.calculateMovingAvgs();
    tSeries.calculateSeasonalRatios(); 
    tSeries.calculateMedIndices();
    tSeries.calculateAdjustedSeasonalIndices();    // end of c)
    tSeries.calculateDeSeasonalizedVals();
    tSeries.calculateTrend();
    
    return 0;
}
