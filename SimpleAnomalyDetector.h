#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
	Point center;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
protected:
	vector<correlatedFeatures> cf;
	float threshold;
	
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
    
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	const vector<correlatedFeatures> getNormalModel() const {
		return cf;
	}

	void setCorrelationThreshold(float threshold){
		this->threshold=threshold;
	}

protected:
	virtual void buildArrayPoints(Point** points, float* x, float* y, int size);
	virtual void deletePoints(Point** points, size_t size);
	virtual void buildCorrelatedFeatures(const TimeSeries& ts,float maxCorrelation, string f1, string f2, vector<float>& xVec, size_t valuesSize);
	virtual float findMaxThreshold(const vector<float>& xVec, const vector<float>& yVec, size_t size, const Line& line);
	virtual float findDev(Point p, const correlatedFeatures& features);

};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
