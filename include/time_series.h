#include "include.h"

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
        double* x4MovingAvgs;
        double* x2MovingAvgs;

        double* seasonalIndices;
        double* seasonalRatios;
        double* medSeasonalIndices;

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
        void calculateMovingAvg();
        void calculateSeasonalIndices();
        void calculateSeasonalRatios();
};
