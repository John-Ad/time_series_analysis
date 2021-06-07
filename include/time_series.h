#include "include.h"
#include "quicksort.h"

class TimeSeries{
    private:
        double n;
        double* x;
        double* x2;
        double xTotal;
        double x2Total;
        double* y;
        double yTotal;
        double* xy;
        double xyTotal;

        double* adjustmentFactors;
        double* x4values;
        double* x2values;

        double* movingAvgs;
        double* seasonalRatios;
        double* medSeasonalIndices;
        double* adjustedSeasonalIndices;
        double* deSeasonalizedY;

        double gradient;
        double yIntercept;

        void calculateGradient();
        void calculateYIntercept();

        void getMedian();

    public:
        TimeSeries();
        void showMainTable();
        void calculateTrend();
        void showTrendEquation();
        void calculateUncenteredCenteredValues();
        void calculateMovingAvgs();
        void calculateSeasonalRatios();
        void calculateMedIndices();
        void calculateAdjustedSeasonalIndices();
        void calculateDeSeasonalizedVals();
};
